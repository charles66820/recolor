# === Recolor via SDL ===

- This is the readme file about the game recolor.
It use SDL.

### Dependencies

On Linux :

- $ sudo apt-get install libsdl2-dev libsdl2-image-dev  libsdl2-ttf-dev

### Compilation

With CMake :

- $ cd build/ ; cmake .. ; make

Without CMake :

- $ gcc -std=c99 -03 -Wall -c -o main_sdl.o main_sdl.c

- $ gcc -std=c99 -03 -Wall -c -o recolor_sdl.o recolor_sdl.c

- $ gcc -rdynamic -lm -lSDL2_ttf -lSDL2_image recolor_sdl.o main_sdl.o -o recolor_sdl

### Run the game

- $ ./recolor_sdl

When the game is launch, choose a color to modify the game. Press r to restart or q to quit the game.

--

This version of the game was made by:

- Charles Gaudefroit

- Victor Andrault

- Arthur Blondeau
