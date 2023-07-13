// Copyright 2020-2023 CesiumGS, Inc. and Contributors

#include "RouteLineActor.h"
#include "CesiumForUnrealSamples.h"
#include "CesiumGeoreference.h"
#include "CesiumRuntime.h"
#include "Generators/SweepGenerator.h"
#include <CesiumAsync/IAssetAccessor.h>
#include <CesiumAsync/IAssetResponse.h>
#include <CesiumGeospatial/Cartographic.h>
#include <CesiumUtility/Math.h>
#include <GeometryScript/MeshPrimitiveFunctions.h>
#include <rapidjson/document.h>

using namespace CesiumAsync;
using namespace CesiumGeospatial;
using namespace CesiumUtility;

namespace {

std::vector<Cartographic>
parsePositionsFromJsonData(const gsl::span<const std::byte>& data) {
  rapidjson::Document document;
  document.Parse(reinterpret_cast<const char*>(data.data()), data.size());
  if (document.HasParseError()) {
    UE_LOG(
        LogCesiumSamples,
        Error,
        TEXT("Unable to parse response from routing service."));
    return {};
  }

  auto routesIt = document.FindMember("routes");
  if (routesIt == document.MemberEnd()) {
    UE_LOG(
        LogCesiumSamples,
        Error,
        TEXT("Routing service response is missing \"routes\" property."));
    return {};
  }

  auto featuresIt = routesIt->value.FindMember("features");
  if (featuresIt == document.MemberEnd()) {
    UE_LOG(
        LogCesiumSamples,
        Error,
        TEXT(
            "Routing service response is missing \"routes.features\" property."));
    return {};
  }

  if (!featuresIt->value.IsArray() || featuresIt->value.Empty()) {
    UE_LOG(
        LogCesiumSamples,
        Error,
        TEXT(
            "In routing service response, \"routes.features\" is not an array or it has no elements."));
    return {};
  }

  auto geometryIt = featuresIt->value[0].FindMember("geometry");
  if (geometryIt == document.MemberEnd()) {
    UE_LOG(
        LogCesiumSamples,
        Error,
        TEXT(
            "Routing service response is missing \"routes.features[0].geometry\" property."));
    return {};
  }

  auto pathsIt = geometryIt->value.FindMember("paths");
  if (pathsIt == document.MemberEnd()) {
    UE_LOG(
        LogCesiumSamples,
        Error,
        TEXT(
            "Routing service response is missing \"routes.features[0].geometry.paths\" property."));
    return {};
  }

  if (!pathsIt->value.IsArray() || pathsIt->value.Empty()) {
    UE_LOG(
        LogCesiumSamples,
        Error,
        TEXT(
            "In routing service response, \"routes.features[0].geometry.paths\" is not an array or it has no elements."));
    return {};
  }

  rapidjson::Value& positions = pathsIt->value[0];
  if (!positions.IsArray() || positions.Size() < 2) {
    UE_LOG(
        LogCesiumSamples,
        Error,
        TEXT(
            "In routing service response, \"routes.features[0].geometry.paths[0]\" is not an array or it has less than two elements."));
    return {};
  }

  std::vector<Cartographic> result;
  result.reserve(positions.Size());

  for (rapidjson::SizeType i = 0; i < positions.Size(); ++i) {
    rapidjson::Value& jsonPosition = positions[i];
    if (!jsonPosition.IsArray() || jsonPosition.Size() < 2)
      continue;
    result.push_back(Cartographic::fromDegrees(
        jsonPosition[0].GetDouble(),
        jsonPosition[1].GetDouble(),
        0.0));
  }

  return result;
}

} // namespace

void ARouteLineActor::OnConstruction(const FTransform& Transform) {
  Super::OnConstruction(Transform);
}

void ARouteLineActor::SetNextRoutePosition(const FVector& position) {
  this->GetDynamicMeshComponent()->GetDynamicMesh()->Reset();
  if (this->_settingDestination) {
    this->_destination = position;
    this->ComputeRoute(this->_start, this->_destination);
  } else {
    this->_start = position;
  }
  this->_settingDestination = !this->_settingDestination;
}

void ARouteLineActor::ComputeRoute(
    const FVector& start,
    const FVector& destination) {
  std::string url =
      "https://route-api.arcgis.com/arcgis/rest/services/World/Route/NAServer/Route_World/solve"
      "?f=json"
      "&token=AAPKf2463b1f5c0c42f6afab87767b967af8av9s9Dtevj-3MX-SW8bv9W9bmqJI3cWOkWREA3E9WAfuK8N5V1IriWlZjXwADZya"
      "&stops=" +
      std::to_string(start.X) + "," + std::to_string(start.Y) + ";" +
      std::to_string(destination.X) + "," + std::to_string(destination.Y);

  AsyncSystem& asyncSystem = getAsyncSystem();
  const std::shared_ptr<IAssetAccessor>& pAssetAccessor = getAssetAccessor();

  pAssetAccessor->get(asyncSystem, url)
      .thenInMainThread([this](std::shared_ptr<IAssetRequest>&& pRequest) {
        const IAssetResponse* pResponse = pRequest->response();
        if (!pResponse) {
          UE_LOG(
              LogCesiumSamples,
              Error,
              TEXT("No response from routing service."));
          return;
        }

        gsl::span<const std::byte> data = pResponse->data();
        std::vector<Cartographic> positions = parsePositionsFromJsonData(data);
        this->createRouteMesh(positions);
      });
}

void ARouteLineActor::createRouteMesh(
    const std::vector<CesiumGeospatial::Cartographic>& positions) {
  if (positions.size() < 2)
    return;

  UDynamicMesh* pMesh = this->GetDynamicMeshComponent()->GetDynamicMesh();

  TArray<FVector2D> polygonVertices = {
      FVector2D(0.0, 0.0),
      FVector2D(1000.0, 0.0),
      FVector2D(1000.0, 20000.0),
      FVector2D(0.0, 20000.0)};

  ACesiumGeoreference* pGeoreference =
      ACesiumGeoreference::GetDefaultGeoreference(this);

  UE::Geometry::FGeneralizedCylinderGenerator generator;

  generator.CrossSection.AppendVertex(FVector2D(0.0, 0.0));
  generator.CrossSection.AppendVertex(FVector2D(1000.0, 0.0));
  generator.CrossSection.AppendVertex(FVector2D(1000.0, 20000.0));
  generator.CrossSection.AppendVertex(FVector2D(0.0, 20000.0));

  generator.Path.Reserve(positions.size());
  for (size_t i = 0; i < positions.size(); ++i) {
    FVector position(
        Math::radiansToDegrees(positions[i].longitude),
        Math::radiansToDegrees(positions[i].latitude),
        0.0);

    generator.Path.Add(
        pGeoreference->TransformLongitudeLatitudeHeightToUnreal(position));
  }

  generator.bLoop = false;
  generator.bCapped = true;
  generator.bPolygroupPerQuad = false;
  generator.StartScale = 1.0;
  generator.EndScale = 1.0;

  glm::dvec3 firstPositionCartesian =
      Ellipsoid::WGS84.cartographicToCartesian(positions[0]);
  glm::dvec3 secondPositionCartesian =
      Ellipsoid::WGS84.cartographicToCartesian(positions[1]);

  glm::dvec3 toSecond = secondPositionCartesian - firstPositionCartesian;
  glm::dvec3 surfaceNormalEcef =
      Ellipsoid::WGS84.geodeticSurfaceNormal(firstPositionCartesian);

  // Y should be in the direction of the ellipsoid surface normal.
  // X should be orthogonal to the direction to the second point and the surface
  // normal direction. Z should be orthogonal to these (and roughly in the
  // direction of the second point)
  glm::dvec3 xAxisEcef = glm::cross(toSecond, surfaceNormalEcef);
  glm::dvec3 yAxisEcef = surfaceNormalEcef;
  glm::dvec3 zAxisEcef = glm::cross(yAxisEcef, xAxisEcef);

  glm::dmat4 ecefToUnreal =
      pGeoreference->GetGeoTransforms()
          .GetEllipsoidCenteredToAbsoluteUnrealWorldTransform();

  glm::dvec3 xAxis = glm::dvec3(ecefToUnreal * glm::dvec4(xAxisEcef, 0.0));
  glm::dvec3 yAxis = glm::dvec3(ecefToUnreal * glm::dvec4(yAxisEcef, 0.0));
  glm::dvec3 zAxis = glm::dvec3(ecefToUnreal * glm::dvec4(zAxisEcef, 0.0));

  FVector xAxisUE(xAxis.x, xAxis.y, xAxis.z);
  FVector yAxisUE(yAxis.x, yAxis.y, yAxis.z);
  FVector zAxisUE(zAxis.x, zAxis.y, zAxis.z);

  generator.InitialFrame =
      UE::Geometry::FFrame3d(generator.Path[0], xAxisUE, yAxisUE, zAxisUE);

  generator.Generate();

  pMesh->EditMesh(
      [&](FDynamicMesh3& editMesh) { editMesh.Copy(&generator); },
      EDynamicMeshChangeType::GeneralEdit,
      EDynamicMeshAttributeChangeFlags::Unknown,
      false);
}
