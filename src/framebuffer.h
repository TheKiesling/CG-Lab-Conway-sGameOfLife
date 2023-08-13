#pragma once
#include <vector>
#include "color.h"
#include <algorithm>
#include <SDL2/SDL.h>

const int FRAMEBUFFER_WIDTH = 93;
const int FRAMEBUFFER_HEIGHT = 93;
const int FRAMEBUFFER_SIZE = FRAMEBUFFER_WIDTH * FRAMEBUFFER_HEIGHT;
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

struct Framebuffer {
    Color framebuffer[FRAMEBUFFER_SIZE];
    Color clearColor;
    Color currentColor;

    Framebuffer()
    : clearColor(Color(0, 0, 0)),
        currentColor(Color(255, 255, 255)) {
            clear();
        }

    int x = 10;
    int y = 10;

    void clear() {
        for (int i = 0; i < FRAMEBUFFER_SIZE; i++) {
            framebuffer[i] = clearColor;
        }
    }

    void point(int x, int y) {
        if (x >= 0 && x < FRAMEBUFFER_WIDTH && y >= 0 && y < FRAMEBUFFER_HEIGHT) {
            framebuffer[y * FRAMEBUFFER_WIDTH + x] = currentColor;
        }
    }

    void renderBuffer(SDL_Renderer* renderer) {
        SDL_Texture* texture = SDL_CreateTexture(
            renderer, 
            SDL_PIXELFORMAT_RGB24,
            SDL_TEXTUREACCESS_STREAMING,
            FRAMEBUFFER_WIDTH, 
            FRAMEBUFFER_HEIGHT
        );

        SDL_UpdateTexture(
            texture, 
            NULL, 
            framebuffer, 
            FRAMEBUFFER_WIDTH * sizeof(Color)
        );

        SDL_RenderCopy(renderer, texture, NULL, NULL);

        SDL_DestroyTexture(texture);
    }

    void life() {
        Color newFramebuffer[FRAMEBUFFER_SIZE];

        for (int y = 0; y < FRAMEBUFFER_HEIGHT; y++) {
            for (int x = 0; x < FRAMEBUFFER_WIDTH; x++) {
                int neighbors = 0;

                for (int yOffset = -1; yOffset <= 1; yOffset++) {
                    for (int xOffset = -1; xOffset <= 1; xOffset++) {
                        if (xOffset == 0 && yOffset == 0) {
                            continue; // Skip the center cell
                        }

                        int neighborX = x + xOffset;
                        int neighborY = y + yOffset;

                        if (neighborX >= 0 && neighborX < FRAMEBUFFER_WIDTH &&
                            neighborY >= 0 && neighborY < FRAMEBUFFER_HEIGHT &&
                            framebuffer[neighborY * FRAMEBUFFER_WIDTH + neighborX].r == 255 &&
                            framebuffer[neighborY * FRAMEBUFFER_WIDTH + neighborX].g == 255 &&
                            framebuffer[neighborY * FRAMEBUFFER_WIDTH + neighborX].b == 255) {
                            neighbors++;
                        }
                    }
                }

                Color currentCellColor = framebuffer[y * FRAMEBUFFER_WIDTH + x];

                if (currentCellColor.r == 255 && currentCellColor.g == 255 && currentCellColor.b == 255) {
                    if (neighbors < 2 || neighbors > 3) {
                        newFramebuffer[y * FRAMEBUFFER_WIDTH + x] = Color(0, 0, 0); // Cell dies
                    } else {
                        newFramebuffer[y * FRAMEBUFFER_WIDTH + x] = Color(255, 255, 255); // Cell survives
                    }
                } else {
                    if (neighbors == 3) {
                        newFramebuffer[y * FRAMEBUFFER_WIDTH + x] = Color(255, 255, 255); // Cell reproduces
                    } else {
                        newFramebuffer[y * FRAMEBUFFER_WIDTH + x] = Color(0, 0, 0); // Cell remains dead
                    }
                }
            }
        }

        // Copy new framebuffer to the main framebuffer
        for (int i = 0; i < FRAMEBUFFER_SIZE; i++) {
            framebuffer[i] = newFramebuffer[i];
        }
    }

    // ----------------- Still lifes -----------------

    void addBlock(int x, int y) {
        point(x, y);
        point(x + 1, y);
        point(x, y + 1);
        point(x + 1, y + 1);
    }

    void addBeeHive(int x, int y) {
        point(x + 1, y);
        point(x + 2, y);
        point(x, y + 1);
        point(x + 3, y + 1);
        point(x + 1, y + 2);
        point(x + 2, y + 2);
    }

    void addLoaf(int x, int y) {
        point(x + 1, y);
        point(x + 2, y);
        point(x, y + 1);
        point(x + 3, y + 1);
        point(x + 1, y + 2);
        point(x + 3, y + 2);
        point(x + 2, y + 3);
    }

    void addBoat(int x, int y) {
        point(x, y);
        point(x + 1, y);
        point(x, y + 1);
        point(x + 2, y + 1);
        point(x + 1, y + 2);
    }

    void addTub(int x, int y) {
        point(x + 1, y);
        point(x, y + 1);
        point(x + 2, y + 1);
        point(x + 1, y + 2);
    }


    // ----------------- Oscillators -----------------
    
    void addBlinker(int x, int y) {
        point(x, y);
        point(x, y + 1);
        point(x, y + 2);
    }

    void addToad(int x, int y) {
        point(x + 1, y);
        point(x + 2, y);
        point(x + 3, y);
        point(x, y + 1);
        point(x + 1, y + 1);
        point(x + 2, y + 1);
    }
    
    void addBeacon(int x, int y) {
        point(x, y);
        point(x + 1, y);
        point(x, y + 1);
        point(x + 3, y + 2);
        point(x + 2, y + 3);
        point(x + 3, y + 3);
    }

    void addPulsar(int x, int y) {
        point(x + 2, y);
        point(x + 3, y);
        point(x + 4, y);
        point(x, y + 2);
        point(x + 5, y + 2);
        point(x, y + 3);
        point(x + 5, y + 3);
        point(x, y + 4);
        point(x + 5, y + 4);
        point(x + 2, y + 5);
        point(x + 3, y + 5);
        point(x + 4, y + 5);
    }

    void addPentaDecathlon(int x, int y) {
        point(x + 2, y + 1);
        point(x + 3, y + 1);
        point(x + 4, y + 1);
        point(x + 1, y + 2);
        point(x + 5, y + 2);
        point(x + 2, y + 3);
        point(x + 3, y + 3);
        point(x + 4, y + 3);
        point(x + 2, y + 5);
        point(x + 3, y + 5);
        point(x + 4, y + 5);
        point(x + 1, y + 6);
        point(x + 5, y + 6);
        point(x + 2, y + 7);
        point(x + 3, y + 7);
        point(x + 4, y + 7);
    }


    // ----------------- Spaceships -----------------

    void addGlider(int x, int y) {
        point(x + 1, y);
        point(x + 2, y + 1);
        point(x, y + 2);
        point(x + 1, y + 2);
        point(x + 2, y + 2);
    }

    void addLWSS(int x, int y) {
        point(x + 1, y);
        point(x + 4, y);
        point(x, y + 1);
        point(x, y + 2);
        point(x + 4, y + 2);
        point(x, y + 3);
        point(x + 3, y + 3);
        point(x + 1, y + 4);
        point(x + 3, y + 4);
    }

    void addMWSS(int x, int y) {
        point(x + 1, y);
        point(x + 4, y);
        point(x, y + 1);
        point(x, y + 2);
        point(x, y + 3);
        point(x + 4, y + 3);
        point(x + 1, y + 4);
        point(x + 2, y + 4);
        point(x + 3, y + 4);
    }

    void addHWSS(int x, int y) {
        point(x + 1, y);
        point(x + 5, y);
        point(x + 6, y + 1);
        point(x, y + 2);
        point(x, y + 3);
        point(x, y + 4);
        point(x, y + 5);
        point(x + 5, y + 5);
        point(x + 1, y + 6);
        point(x + 2, y + 6);
        point(x + 3, y + 6);
        point(x + 4, y + 6);
    }

    void initialRender(){
        clear();

        addBlock(40, 35);  

        addBeeHive(45, 40);

        addBlinker(44, 37);

        addToad(50, 37);

        addBeacon(55, 37);

        addGlider(46, 29);

        addPentaDecathlon(38, 62);
        addPentaDecathlon(43, 62);
        addPentaDecathlon(48, 62);

        addLWSS(11, 3);
        addLWSS(21, 3);
        addLWSS(31, 3);
        addLWSS(41, 3);
        addLWSS(51, 3);
        addLWSS(61, 3);
        addLWSS(71, 3);
        addLWSS(81, 3);
        addLWSS(11, 13);
        addLWSS(21, 13);
        addLWSS(31, 13);
        addLWSS(41, 13);
        addLWSS(51, 13);
        addLWSS(61, 13);
        addLWSS(71, 13);
        addLWSS(81, 13);
        addLWSS(11, 23);
        addLWSS(21, 23);
        addLWSS(31, 23);
        addLWSS(41, 23);
        addLWSS(51, 23);
        addLWSS(61, 23);
        addLWSS(71, 23);
        addLWSS(81, 23);
        addLWSS(11, 33);
        addLWSS(81, 33);
        addLWSS(11, 43);
        addLWSS(81, 43);
        addLWSS(11, 53);
        addLWSS(81, 53);
        addLWSS(11, 63);
        addLWSS(81, 63);
        addLWSS(31, 73);
        addLWSS(67, 73);
        addLWSS(11, 83);
        addLWSS(46, 83);
        addLWSS(81, 83);

        addMWSS(28, 73);
        addMWSS(34, 73);
        addMWSS(64, 73);
        addMWSS(70, 73);

        addHWSS(41, 73);
        addHWSS(47, 73);
    }

    void render(SDL_Renderer* renderer) {
        life();

        renderBuffer(renderer);
    }
};
