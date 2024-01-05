#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "game.h"
#include <ImageHlp.h>
#include <string>

// Global constants
const float COLUMN = 40;
const float ROW = 40;

// Global variables
int snakeMove = 0;
bool gameOver = false;

enum GameState {
    MENU,
    PLAY,
    GAME_OVER
};

GameState gameState = MENU;

// Function prototypes
void init();
void display_callback();
void special_callback(int key, int, int);
void timer_callback(int x);

void drawMenu();
void menuKeyboardCallback(unsigned char key, int x, int y);

void drawGameOver();
void gameOverKeyboardCallback(unsigned char key, int x, int y);

int main(int argv, char** argc);

// Main function
int main(int argv, char** argc) {
    glutInit(&argv, argc);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Snake Game");

    // Load the highest score from the file
    loadHighestScore();

    init();
    glutDisplayFunc(display_callback);
    glutSpecialFunc(special_callback);
    glutTimerFunc(0, timer_callback, 0);

    // Register the menu keyboard callback
    glutKeyboardFunc(menuKeyboardCallback);

    glutMainLoop();
    return 0;
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    initGrid(COLUMN, ROW);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, COLUMN, 0, ROW, -1, 1);
}

// Timer callback function
void timer_callback(int x) {
    glutPostRedisplay();
    glutTimerFunc(1000 / (FPS * snakeSpeed), timer_callback, 0);
}

// Special keyboard callback function
void special_callback(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_RIGHT:
        if (snakeMove == -1) break;
        snakeMove = 1;
        break;
    case GLUT_KEY_LEFT:
        if (snakeMove == 1) break;
        snakeMove = -1;
        break;
    case GLUT_KEY_UP:
        if (snakeMove == -2) break;
        snakeMove = 2;
        break;
    case GLUT_KEY_DOWN:
        if (snakeMove == 2) break;
        snakeMove = -2;
        break;
    default:
        break;
    }
}

// Display callback function
void display_callback() {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    switch (gameState) {
    case MENU:
        drawMenu();
        break;
    case PLAY:
        if (gameOver) {
            gameState = GAME_OVER;
            glutKeyboardFunc(gameOverKeyboardCallback);
        }
        else {
            // Draw score during the game
            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2i(static_cast<int>(COLUMN - 10), static_cast<int>(ROW - 1));
            string scoreText = "Score: " + to_string(length);
            for (char c : scoreText) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
            }

            drawSnake();
            drawFood();
        }
        break;
    case GAME_OVER:
        drawGameOver();
        break;
    }

    glutSwapBuffers();
}

// Menu keyboard callback function
void menuKeyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
    case 'p':
    case 'P':
        gameState = PLAY;
        break;
    case 'q':
    case 'Q':
        exit(0);
        break;
    }
}

// Game over keyboard callback function
void gameOverKeyboardCallback(unsigned char key, int x, int y) {
    switch (key) {
    case 'p':
    case 'P':
        gameState = PLAY;
        gameOver = false;
        initGrid(COLUMN, ROW);
        length = 0;
        snakeSpeed = 1.0f;
        snakeMove = 0;
        resetSnake();
        glutKeyboardFunc(nullptr);  // Unregister the game over keyboard callback
        break;
    case 'q':
    case 'Q':
        exit(0);
        break;
    }
}
void drawMenu() {
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(15, 30);
	for (const char* c = "Snake Game"; *c != '\0'; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
	glRasterPos2i(25, 29);
	for (const char* c = "by Hoang Minh"; *c != '\0'; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
	glRasterPos2i(15, 20);
	for (const char* c = "Press 'P' to play"; *c != '\0'; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
	glRasterPos2i(15, 15);
	for (const char* c = "Press 'Q' to quit"; *c != '\0'; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
	// Display the highest score
	glRasterPos2i(15, 5);
	string scoreText = "Highest Score: " + to_string(highestScore);
	for (char c : scoreText) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
}

void drawGameOver() {
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(15, 30);
	for (const char* c = "Game Over"; *c != '\0'; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
	glRasterPos2i(25, 29);
	for (const char* c = "by Hoang Minh"; *c != '\0'; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
	}
	glRasterPos2i(15,25);
	string scoreText = "Your score is: " + to_string(length);
	for (char c : scoreText) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
	}
	glRasterPos2i(15, 20);
	for (const char* c = "Press 'P' to play again"; *c != '\0'; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
	glRasterPos2i(15, 15);
	for (const char* c = "Press 'Q' to quit"; *c != '\0'; ++c) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}
}