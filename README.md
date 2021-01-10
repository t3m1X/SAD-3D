# SAD 3D
This engine is a fork of [Aitor Simona's](https://github.com/AitorSimona) [CENTRAL 3D](https://github.com/AitorSimona/CENTRAL-3D) version [0.2](https://github.com/AitorSimona/CENTRAL-3D/tree/Assignment2).
All copyright for the base code is Aitor's.

All alterations to the above code for Delivery 3 are done by Sergi Parra
## TOOLS USED

- Microsoft Visual Studio 2017 (For base code)
- Microsoft Visual Studio 2019
- Visual Studio Code
- 3rd Party Libraries used:
- SDL 2.0.10
- Glew 2.1.0
- ImGui 1.72b (with beta docking)
- MathGeoLib 1.5 (commit 1994)
- OpenGL 3.1
- mmgr
- par_shapes at commit 281 
- DevIL 1.8.0
- JSON for Modern C++
- PhysFS 


## HOW TO USE

There is no formal installation process, just look around and play with it

- Navigation:

Mouse and Keyboard controls are enabled both on UI and Scene, working on focused window only.

- Mouse picking

Self-explainable, click on an object to select it, notice how inspector info changes, but if the object is hidden
in the hierarchy you won't notice it there, open parent to see how it is selected.

- Scene Camera:

- Right Mouse button enables Look Around
- Alt + Left Mouse button enables Camera Orbit
- Mouse Wheel click enables camera Pan
- Right Mouse button + WASD enables free movement
- Mouse Wheel movement enables zoom

Editor camera only works when in AppState EDITOR mode.

## ASSET IMPORT

Drop it inside window 2 times, first for importing, second for loading, you can also drag it from project window 
to hierarchy (on the window title).

All fbx in assets folder will be imported at startup.

## DEBUG

- Debug Features

Head to Scene window and click DebugDraw to see available features: 

- Wireframe
- Color Material
- OpenGL Lighting
- Display Octree
- Show AABBS

There are more options in Window - > Settings

## Features in beta

- Texture pre-visualization on Inspector
- Toolbar
- Edit Menu
- Load/Save cameras
- Resource manager (initial implementation)

## CHANGELOG

### CENTRAL 3D 0.2

- Initial Structure of Resource Manager
- Reference Counting for ResourceMesh and ResourceTexture
- Scene serialization to file and loading
- New import pipeline (creates own file format files in library)
- New Time Manager (Options to PLAY STOP STEP)
- Spatial partitioning using Octree
- Creation of cameras
- Frustum culling
- AABB's
- Project window
- Mouse picking 

### CENTRAL 3D 0.1

- Polished Game Object and Component Structure
- Initial Implementation on Inspector (properties for the different components)
- Modification of many Menus/Windows
- Possibility of primitives creation through GameObject Menu
- Unity-like Camera Controls 

### CENTRAL 3D 0.05

- Libraries Integration
- Basic Editor with Inspector/Hierarchy/Console/Menu
- Initial GameObject and Component structure
- Save & Load Editor Configuration
- Load 3D Models through assimp (fbx format)
- Load Textures through DevIL (dds and png format)
- Docking


## License:

MIT License

Copyright (c) 2019 Aitor Simona Bouzas
Copyright (c) 2021 Sergi Parra Ramírez
Copyright for portions of SAD 3D are held by Aitor Simona Bouzas, 2019 as part of project CENTRAL 3D (Version 2.0). 
All other copyright for project SAD 3D are held by Sergi Parra Ramírez, 2021.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.




