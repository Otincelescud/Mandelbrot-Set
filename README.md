# Mandelbrot Set

## Overview

This program displays the mandelbrot set **fractal** and lets you zoom in on it.

## Usage

Controls:

* Panning - Use Left Mouse Button or the WASD keys to pan
* Zooming - Use Mouse Scrollwheel or the E and Q keys to zoom in and out

## Instalation

### Requirements

- [sdl 2.30.3](https://www.libsdl.org/)
- [glad](https://glad.dav1d.de/) for OpenGL of version at least 3.3

### Building and Running

In order to build the executable to run this programm run the following command:

#### On Windows
To install dependencies:
...

```
g++ src\main.cpp src\app.cpp src/graphics.cpp src/utils.cpp glad.c -O3 -o ".\build\run\Mandelbrot Set.exe" -I"dependencides" -L "[Path to SDL2 lib directory]" -lSDL2 -mwindows

".\build\run\Mandelbrot Set.exe"
```

#### On Linux
To install dependencies:
- Install SDL2 from your package manager or from the SDL2 GitHub
- Go to [https://glad.dav1d.de/](https://glad.dav1d.de/) and download glad for core OpenGL with a version of at least 3.3
- Unzip glad
- Create a directory named "dependencies" and copy the glad and KHM directories from the directory you just unziped
- Copy the glad.c file to the root directory of the project

After installing the dependencies run the following commands:

```
g++ src/main.cpp src/app.cpp src/graphics.cpp src/utils.cpp glad.c -O3 -o "./build/run/Mandelbrot Set" -I"dependencies" -lSDL2

"./build/run/Mandelbrot Set"
```

If you're having trouble building the program on Linux here are some flags that might help: -lGL -lX11 -lpthread -lXrandr -lXi -ldl

## License

Copyright (C) 2024 Otincelescu Darius Marian

This program is distributed under the GNU General Purpose License Version 3, or (at your option) any later version.
For more information read the LICENSE file.

## Acknowledgements

Huge thanks to [**Carl Birch**](https://github.com/carlbirch) from the Youtube Channel [**Let's Make Games**](https://www.youtube.com/@CarlBirch) :D! Without his tutorial series on how to make games in c++ with SDL2, making this game would have taken waaaay longer!

Thanks to the people behind [Simple DirectMedia Layer](https://www.libsdl.org/) and for creating the libraries I used in this project and for distributing them open-source!