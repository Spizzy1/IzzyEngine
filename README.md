
# IzzyEngine

A tool used by me and possible contributors as a vector for learning how rendering and memory management on a lower level, hopefully resulting in a (somewhat) functioning game engine!

## What it currently implements

A basic rendering engine with structs for shaders, meshes and textures with a generalized "Character" struct to tie them all together for ease of use, written in OpenGL.

## What it plans to implement and why?

### A custom, downscaled "Standard library" for internal uses

To learn how internal functions such as vectors and string structures. Yes it would be more efficient to use the built in functions, but the project is primarily for intended for educational purposes.

### Lua language support

For convenience of use later down the line when working with actual game development within the engine, and fast protyping. While the engine is intended to be C and C++ centric, Lua is a good way for fast interation and prototyping. And you can always rewrite the code later for a great performance boost once you are finished with prototyping.

## Installation

You'll need to download and setup cmake for your desired OS, the dependancies are in git submodules or in pure headers included in the repo so they will be compiled by cmake upon first setup. If any issues arise, feel free to open an issue (Although this is not intended for commercial use and thus it is up to potential maintainers to fix).
