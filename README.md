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

In order to install SDL2 follow the link above and follow the instructions on the Official SDL2 Website.
In order to install glad generate the package on the [website](https://glad.dav1d.de/) then move the include/glad and include/KHM dirs to your include path and the move the src/glad.c file to the root of the project directory.

### Building and Running

In order to build the executable to run this programm run the following command:

#### On Windows
```
g++ src\main.cpp src\app.cpp src\complex.cpp src\mdb_set_math.cpp glad.c -O3 -o ".\build\Run\Mandelbrot Set.exe" -I "[Path to SDL2 include directory]" -L "[Path to SDL2 lib directory]" -lSDL2 -lGL -mwindows
".\build\Run\Mandelbrot Set.exe"
```

#### On Linux
```
g++ src/main.cpp src/app.cpp src/complex.cpp src/mdb_set_math.cpp glad.c -O3 -o "./build/Run/Mandelbrot Set.out" -lSDL2 -lGL
"./build/Run/Mandelbrot Set.out"
```

*If you're having trouble building the program on Linux here are some flags that might help:* -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl

## License

Copyright (C) 2024 Otincelescu Darius Marian

This program is distributed under the GNU General Purpose License Version 3, or (at your option) any later version.
For more information read the LICENSE file.

## Acknowledgements

Huge thanks to [**Carl Birch**](https://github.com/carlbirch) from the Youtube Channel [**Let's Make Games**](https://www.youtube.com/@CarlBirch) :D! Without his tutorial series on how to make games in c++ with SDL2, making this game would have taken waaaay longer!

Thanks to the people behind [Simple DirectMedia Layer](https://www.libsdl.org/) and for creating the libraries I used in this project and for distributing them open-source!