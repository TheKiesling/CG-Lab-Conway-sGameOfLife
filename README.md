# CG-Lab-Conway-sGameOfLife

https://github.com/TheKiesling/CG-Lab-Conway-sGameOfLife/assets/84196494/f7c4f327-4d32-4e13-ab0d-561c94820304

Welcome to the Conway's Game of Life lab, where we'll be implementing Conway's cellular automaton using C++ and the SDL2 library for graphical visualization. The goal is to simulate the behavior of cells in a two-dimensional world, following simple rules that determine their life, death, and reproduction.

## Instructions

### Prerequisites

Before you start, ensure you have the SDL2 library installed on your system. You can find information on how to install SDL2 [here](https://wiki.libsdl.org/Installation).

### File Structure

The project is organized into three main files:

- `color.h`: Defines the `Color` structure used to represent colors in the game.
- `framebuffer.h`: Contains the `Framebuffer` structure that manages the drawing and simulation of the game.
- `main.cpp`: The entry point of the program, where the SDL window is created and managed.

### Usage

1. Clone this repository to your local system.
2. Make sure you have SDL2 installed on your system.
3. Compile the program using a C++ compatible compiler.
4. Run the compiled program.

### Features

The program includes the following features:

- Visual representation of live and dead cells in a graphical window.
- Implementation of Conway's algorithm with survival and reproduction rules.
- Different predefined initial patterns, such as blocks, beehives, gliders, and more.
- Continuous animation that simulates the game's turns.

### Customization

You can customize the window's resolution and animation speed by modifying the `WINDOW_WIDTH`, `WINDOW_HEIGHT`, and `SDL_Delay()` values.

### Initial Patterns

You can add initial patterns to the world using functions like `addBlock()`, `addBeeHive()`, `addGlider()`, and many more defined in `Framebuffer`.

## Credits

This lab was implemented by José Pablo Kiesling.

## Final Notes

Enjoy exploring and experimenting with the fascinating world of Conway's Game of Life! If you have any questions or issues, feel free to contact pkiesling@gmail.com.

---
