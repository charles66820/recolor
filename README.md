# Recolor

## Table of Contents

- [Recolor](#recolor)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Compilation](#compilation)
    - [Prerequisite](#prerequisite)
    - [Dependencies](#dependencies)
    - [Compile](#compile)
  - [Installation](#installation)
  - [Features](#features)
  - [Team](#team)

## Overview

This is the readme file about the game recolor.
It use SDL.

## Compilation

### Prerequisite

- Install gcc, make and cmake :
  - On Ubuntu :

    ```bash
    sudo apt update
    sudo apt install gcc make cmake
    ```

  - On windows follow [this tutorial](https://docs.google.com/document/d/1J9hmYZqJWYl5cPZbsa-0SUxm3aK9p-revsMnifJJuv4/edit?usp=sharing)

### Dependencies

- Install all dependencies on Ubuntu :

    ```bash
    sudo apt install libsdl2-dev libsdl2-image-dev  libsdl2-ttf-dev
    ```

### Compile

> Replace `Release` by `Debug` for debug mode

- On linux :

    ```bsah
    mkdir build && cd build/
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    ```

- On Windows follow [this tutorial](https://docs.google.com/document/d/1J9hmYZqJWYl5cPZbsa-0SUxm3aK9p-revsMnifJJuv4/edit?usp=sharing) at the part "install SDL2, SDL2_IMG and SDL2_TTF".

    ```bsah
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" -DCMAKE_C_COMPILER=C:/TDM-GCC-32/bin/gcc.exe ..
    make
    ```

> The generated binary / executable is in `generated` folder

## Installation

```bash
make install
```

## Features

- Recolor text version (recolor_text or recolor_text.exe)
    Description of recolor version text

- Recolor graphic version (recolor_sdl or recolor_sdl.exe)
    When the game is launch, choose a color to modify the game. Press r to restart or q to quit the game.

## Team

This version of the game was made by:

- Charles Gaudefroit

- Victor Andrault

- Arthur Blondeau
