#include "game.h"
#include <fstream>


// Global Variables
float snakeSpeed = 1.0f; // Initial speed
extern int snakeMove;
extern bool gameOver;
float gridX, gridY;
float foodX, foodY;
bool food = true;
float posX[40] = { 20,20,20,20,20 }, posY[40] = { 20,19,18,17,16 };

int foodType = 0; // Default to NORMAL food
int length = 0;
int highestScore = 0;

// Food Appearance Percentages
int normalFoodPercentage = 40;  // 40% chance
int speedUpPercentage = 20;     // 20% chance
int doubleLengthPercentage = 5; // 5% chance
int slowDownPercentage = 20;    // 20% chance
int decreaseLengthPercentage = 15; // 15% chance

// Function to initialize the grid with given dimensions
void initGrid(float x, float y) {
    gridX = x;
    gridY = y;
}

// Function to update the highest score and save it to a file
void updateHighestScore() {
    if (length > highestScore) {
        highestScore = length;

        // Save the highest score to a file
        std::ofstream file("highest_score.txt");
        if (file.is_open()) {
            file << highestScore;
            file.close();
        }
        else {
            std::cerr << "Error: Could not open the file for writing.\n";
        }
    }
}

// Function to load the highest score from a file
void loadHighestScore() {
    std::ifstream file("highest_score.txt");
    if (file.is_open()) {
        file >> highestScore;
        file.close();
    }
    else {
        std::cerr << "Error: Could not open the file for reading. Setting highest score to 0.\n";
        highestScore = 0;
    }
}

// Function to draw the grid lines
void drawGrid() {
    glLineWidth(1);
    glColor3f(1.0, 1.0, 1.0);
    for (float i = 0; i < gridX; i++) {
        glBegin(GL_LINES);
        glVertex2f(i, 0);
        glVertex2f(i, gridY);
        glVertex2f(0, i);
        glVertex2f(gridX, i);
        glEnd();
    }
}

// Function to draw the snake on the screen
void drawSnake() {
    if (snakeMove != 0) {
        for (int i = length + 5 - 1; i > 0; i--) {
            posX[i] = posX[i - 1];
            posY[i] = posY[i - 1];
        }
    }
    if (snakeMove == 1) posX[0]++;
    else if (snakeMove == -1) posX[0]--;
    else if (snakeMove == 2) posY[0]++;
    else if (snakeMove == -2) posY[0]--;

    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < length + 5; i++) {
        if (i == 0) glColor3f(1.0, 0.2, 0.8);
        else glColor3f(1.0, 0.6, 0.9);
        glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
    }
    for (int i = 1; i < length + 5; i++) {
        if (posX[0] == posX[i] && posY[0] == posY[i]) {
            gameOver = true;
            break;
        }
    }
    if (posX[0] == 0 || posX[0] == gridX || posY[0] == 0 || posY[0] == gridY) {
        gameOver = true;
    }
}

// Function to draw the food on the screen
void drawFood() {
    srand(time(NULL));
    checkPosFood();
    if (food) {
        foodX = rand() % (int)gridX;
        foodY = rand() % (int)gridY;
        int totalPercentage = normalFoodPercentage + speedUpPercentage + doubleLengthPercentage + slowDownPercentage + decreaseLengthPercentage;
        int randNum = rand() % totalPercentage;
        if (randNum < normalFoodPercentage) {
            foodType = 1;  // Normal Food
        }
        else if (randNum < normalFoodPercentage + speedUpPercentage) {
            foodType = 2;  // Speed Up
        }
        else if (randNum < normalFoodPercentage + speedUpPercentage + doubleLengthPercentage) {
            foodType = 3;  // Double Length
        }
        else if (randNum < normalFoodPercentage + speedUpPercentage + doubleLengthPercentage + slowDownPercentage) {
            foodType = 4;  // Slow Down
        }
        else {
            foodType = 5;  // Decrease Length
        }
        food = false;
    }
    if (foodType == 1) {
        glColor3f(0, 1.0, 0); // Normal food is green
    }
    else if (foodType == 2) {
        glColor3f(0, 0, 1.0); // Speed up is blue
    }
    else if (foodType == 3) {
        glColor3f(1.0, 0, 0); // Double length is red
    }
    else if (foodType == 4) {
        glColor3f(0, 1.0, 1.0); // Slow down is cyan
    }
    else {
        glColor3f(0.5, 0, 0.5); // Decrease length is purple
    }
    glRectd(foodX, foodY, foodX + 1, foodY + 1);
}

// Function to check if the snake has eaten the food and update accordingly
void checkPosFood() {
    for (int i = 0; i < length+5; i++) {
        if (foodX == posX[i] && foodY == posY[i]) {
            food = true;

            if (foodType == 1) {
                length++;
            }
            else if (foodType == 2) {
                snakeSpeed += 0.1f;
            }
            else if (foodType == 3) {
                length *= 2;
            }
            else if (foodType == 4) {
                snakeSpeed -= 0.1f;
                if (snakeSpeed < 0.1f) {
                    snakeSpeed = 0.1f;
                }
            }
            else {
                if (length+5 > 2) {
                    length--;
                }
                else {
                    length++;
                }
            }

            updateHighestScore();
        }
    }
}

// Function to reset the snake to initial positions
void resetSnake() {
    posX[0] = rand() % ((int)gridX-5);
    posY[0] = rand() % ((int)gridY-5);
    for (int i = 1; i < length+5; i++) {
        posX[i] = posX[0];
        posY[i] = posY[0] - i;
    }
}
