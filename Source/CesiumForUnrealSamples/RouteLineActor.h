// Copyright 2020-2021 CesiumGS, Inc. and Contributors

#pragma once

#include "CoreMinimal.h"
#include "DynamicMeshActor.h"
#include "RouteLineActor.generated.h"

namespace CesiumGeospatial {
class Cartographic;
}

/**
 *
 */
UCLASS()
class CESIUMFORUNREALSAMPLES_API ARouteLineActor : public ADynamicMeshActor {
  GENERATED_BODY()

public:
  virtual void OnConstruction(const FTransform& Transform) override;

private:
  void
  createRouteMesh(const std::vector<CesiumGeospatial::Cartographic>& positions);
};
