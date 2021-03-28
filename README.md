[![Cesium for Unreal Logo](Images/Cesium-for-Unreal-Logo-WhiteBGH.jpg)](https://cesium.com/unreal-marketplace?utm_source=cesium-unreal&utm_medium=github&utm_campaign=unreal)

# Cesium for Unreal Samples

This [Cesium for Unreal Samples](https://cesium.com/unreal-samples-marketplace?utm_source=cesium-unreal-samples&utm_medium=github&utm_campaign=unreal) is a starter project to learn and explore the [Cesium for Unreal](https://cesium.com/unreal-marketplace?utm_source=cesium-unreal&utm_medium=github&utm_campaign=unreal) plugin.

The levels in this project walk you through the various aspects of enabling global-scale content, applications, and experiences in Unreal Engine

![Photogrammetry of Melbourne, Australia visualized in Unreal Engine using Cesium for Unreal.](Images/melbourne.jpg)
*<p align="center">Photogrammetry of Melbourne, Australia visualized in Unreal Engine using Cesium for Unreal.<br>Open the <b>Melbourne</b> level in Cesium for Unreal Samples to experience it yourself!</p>*

### :rocket: Get Started

**[Download Cesium for Unreal Samples from Unreal Engine Marketplace](https://cesium.com/unreal-samples-marketplace?utm_source=cesium-unreal-samples&utm_medium=github&utm_campaign=unreal)**

You will also need to **[download Cesium for Unreal plugin from Unreal Engine Marketplace](https://cesium.com/unreal-marketplace?utm_source=cesium-unreal&utm_medium=github&utm_campaign=unreal)**

Have questions? Ask them on the [community forum](https://community.cesium.com).

## :mountain: Level Descriptions

### :one: Level 1 - Cesium World

The first level of Cesium for Unreal Samples open with Cesium World Terrain and the camera near San Francisco. This level is designed to familiarize yourself with the core Cesium actors and components like Cesium World Terrain and Cesium Georeference.

Be sure to sign into your Cesium ion account using the Cesium button in the toolbar.

### :two: Level 2 - Melbourne Photogrammetry

Explore high-resolution photogrammetry data of Melbourne, streamed from Cesium ion as 3D Tiles, a spatial index for streaming massive 3D content over the web. 3D Tiles makes it possible to take hundreds of GB of data, and stream it over the web using hierarchical level of detail, spatial subdivision, and runtime optimizations.

Be sure to change the time of day to create beautiful lighting in your scenes.

### :three: Level 3 - Denver Photogrammetry with Unreal Character Controller

In this level, you get to explore even more high-resolution photogrammetry data of Denver using a third-person character controller. Whereas Melbourne allowed you to freely fly around and explore, in this level, you get to experience the real world data up close using the character controller and how physics and gravity continue to work as expected in Unreal Engine, even with streaming content.

Be sure to grab some cool screenshots to share with us as you explore and customize the scenes for yourself.

![Photogrammetry of Union Station in Denver, CO captured by [Aerometrex](https://aerometrex.com.au/) visualized in Unreal Engine using Cesium for Unreal.](Images/aerometrex-denver.jpg)
*<p align="center">Photogrammetry of Union Station in Denver, CO captured by [Aerometrex](https://aerometrex.com.au/).<br>Open level 3 in Cesium for Unreal Samples to experience it yourself using the character controller!</p>*

### :four: Level 4 - Using Sublevels to Explore the World

Cesium for Unreal uses sublevels to allow you to fly around the entire world within the same level. In this level, we've added a few locations around the world that you can explore in play mode by pressing the 1-5 keys to fly to different locations.

You can also add your own favorite locations around the world by adding the coordinates them to `CesiumGeoreference -> Details -> Cesium Sublevels` and add elements to the `Cesium Sublevels` array.

### :five: Level 5 - Post Processing

With Unreal Engine's amazing lighting, rendering, and post processing capabilities, you can create amazing visual experiences combined with Cesium's real world content. Whether you want to create sunsets at the beach, or experience Mt. Everest at sunrise, you can simulate those experiences with Cesium for Unreal and Unreal Engine.

This level has lighting, fog, volumetric clouds, and post processing volumes to create a beautiful scene at Mt. Fuji. You should try tweaking the setting to customize the scene and create different effects. We would love to see what you create!

### :hammer_and_wrench:Using Cesium for Unreal Samples for Development

Cesium for Unreal Samples can also be used for development and testing of the Cesium for Unreal plugin. To use this project for development, follow these steps.

1. Clone the repo with `git clone git@github.com:CesiumGS/cesium-unreal-samples.git`.
2. From the `cesium-unreal-samples/Plugins` directory, clone Cesium for Unreal using `git clone --recursive git@github.com:CesiumGS/cesium-unreal.git`.
3. Follow the instructions to [compile Cesium for Unreal](https://github.com/CesiumGS/cesium-unreal#computer-developing-with-unreal-engine).
4. Open `CesiumForUnrealSamples.uproject` in the Unreal Editor.
    * If prompted to rebuild modules, click "yes".
    * Optional: Generate Visual Studio project files manually by choosing `File -> [Refresh/Generate] Visual Studio Project` in the editor. You can also do this by right-clicking `CesiumForUnrealSamples.uproject` and clicking `Generate Visual Studio project files`.
    * Optional: You can open the project Visual Studio by opening the `CesiumForUnrealSamples.sln` solution file generated by Unreal Engine.
5. The Cesium for Unreal Samples project contains numbered levels that showcase the global scale and real-world content of Cesium for Unreal. Levels include terrain, imagery, 3D Buildings, and photogrammetry. Give them a spin and let the ideas flow!

### :green_book:License

[Apache 2.0](http://www.apache.org/licenses/LICENSE-2.0.html). Cesium for Unreal Samples is free to use as starter project for both commercial and non-commercial use.
