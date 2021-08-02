echo wget "${CESIUM_FOR_UNREAL_BUILD}" -O $PWD/cesium-for-unreal.zip
echo "start"
wget "${CESIUM_FOR_UNREAL_BUILD}" -O $PWD/cesium-for-unreal.zip
echo "done"
if [[ $TRAVIS_OS_NAME == "windows" ]]
then
    mkdir -p "C:\Program Files\Epic Games\UE_4.26\Engine\Plugins\Marketplace"
    7z x $PWD/cesium-for-unreal.zip "-oC:\Program Files\Epic Games\UE_4.26\Engine\Plugins\Marketplace"
    rm cesium-for-unreal.zip
elif [[ $TRAVIS_OS_NAME == "osx" ]]
then
    mkdir -p $HOME/UE_4.26/Engine/Plugins/Marketplace
    unzip cesium-for-unreal.zip -d $HOME/UE_4.26/Engine/Plugins/Marketplace
    rm cesium-for-unreal.zip
elif [[ $TRAVIS_OS_NAME == "linux" ]]
then
    mkdir -p $HOME/UE_4.26/Engine/Plugins/Marketplace
    unzip cesium-for-unreal.zip -d $HOME/UE_4.26/Engine/Plugins/Marketplace
    rm cesium-for-unreal.zip
fi
