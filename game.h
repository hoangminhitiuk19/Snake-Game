

//The main file handles the initialization and the main game loop, while the game.cpp file contains functions related to the game's mechanics. The game.h file provides function declarations for these functions.
#pragma once
#include <stdlib.h>
#include <Windows.h>
#include <GL/glut.h>
#include <time.h>
#include <iostream>
using namespace std;

extern float snakeSpeed;
extern int length;

extern int highestScore ;
extern int currentLevel ;

const float FPS = 10;

void initGrid(float x, float y);
void drawGrid();
void drawSnake();
void drawFood();
void checkPosFood();
void resetSnake();
void updateHighestScore();
void loadHighestScore();
