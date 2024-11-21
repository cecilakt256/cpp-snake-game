/**
 * Purpose: Create a snake game with the following rules:
 * 1. Don’t hit a wall and don’t bite your own tail.
 * 2. Crashing into a wall or your tail will end the game immediately.
 * 3. 10 points will be added to the player’s score for eating the fruit (#).
 * 4. The player’s total score is calculated based on the number of fruits the snake consumed.
 * 5. The length of the snake will be increased after eating the fruits.
 * 6. Use w, a, s, d to move the snake.
 */
// Standard I/O Library
#include <iostream>
// Windows API Library
#include <Windows.h>
// Console Command Library
#include <conio.h>

using namespace std;
/**
 * Global variables
 */
// Height and Width of Boundaries
const int width = 80;
const int height = 20;

// Snake head coordinates
int x, y;

// Food containers
int fruitCordX, fruitCordY;

// Player Score variable
int playerScore;

// Array storing Tail coordinates
int snakeTailX[100], snakeTailY[100];

// Snake Length
int snakeLen;

// Storing moving directions
//  enum = Enumerated type, which is a user-defined data type
enum snakesDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// snakesDirection variable
snakesDirection sDir;

// Game Status Checker
bool isGameOver;

/**
 * Game Initialization Function
 */
void GameInit()
{
    isGameOver = false;
    // not moving
    sDir = STOP;
    // starting the snake in the middle
    x = width / 2;
    y = height / 2;
    // Randomizing placement of fruit within boundaries
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    playerScore = 0;
}

/**
 * Game Board Rendering
 */
void GameRender()
{
    // Clear the console
    system("cls");

    // Creating top walls
    for (int i = 0; i < width + 2; i++)
    {
        cout << "-";
    }
    cout << endl;

    // Rendering "assets" included in height
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <= width; j++)
        {
            // Side walls, checking if we are before or after the middle rows
            if (j == 0 || j == width)
            {
                cout << "|";
            }
            // Snake head, checking if coordinates match snake position
            if (i == y && j == x)
            {
                cout << "O";
            }
            // Snake's Food
            else if (i == fruitCordY && j == fruitCordX)
            {
                cout << "#";
            }

            // Tail of snake
            else
            {
                bool prTail = false;
                for (int k = 0; k < snakeLen; k++)
                {
                    if (snakeTailX[k] == j && snakeTailY[k] == i)
                    {
                        cout << "o";
                        prTail = true;
                    }
                }
                // Prints empty spaces in board
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    // Bottom of Walls, same as top
    for (int i = 0; i < width + 2; i++)
    {
        cout << "-";
    }
    cout << endl;

    // Players Score
    cout << "Score: " << playerScore << endl;
}

/**
 * Updating Game State: Updates after each move
 */
void UpdateGame()
{
    // Set initial conditions for snake
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    //
    for (int i = 1; i < snakeLen; i++)
    {
        // Stores current tail value into temp var
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        // Updates new tail value
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        // Swaps prev temp var value back in
        prevX = prev2X;
        prevY = prev2Y;
    }
    // Change Direction from Keys Pressed
    switch (sDir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y++;
        break;
    case DOWN:
        y--;
        break;
    }
    // Checks for Snake WALL Collision
    if (x >= width || x < 0 || y >= height || y < 0)
    {
        // changes game status
        isGameOver = true;
    }

    // Checks for Snake TAIL Collision
    for (int i = 0; i < snakeLen; i++)
    {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
        {
            isGameOver = true;
        }
    }

    // Checks for Snake FOOD Collision
    if (x == fruitCordX && y == fruitCordY)
    {
        playerScore += 10;
        // rerolls fruit location
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        // adds length
        snakeLen++;
    }
}

/**
 * Setting Game Difficulty
 */

int setDifficulty()
{
    int diff, choice;
    cout << "\nSet Difficulty\n1. Easy\n2. Medium\n3. Hard"
            "\nNote: Difficulty will be automatically set to medium if N/A"
         << endl;

    cout << "Please Choose Difficulty: ";
    cin >> choice;
    switch (choice)
    {
    case '1':
        diff = 50;
        break;
    case '2':
        diff = 100;
        break;
    case '3':
        diff = 150;
        break;
    default:
        diff = 100;
    }
    return diff;
}

/**
 * User Input Handling
 */
void UserInput()
{
    // bhit checks to see if key is being pressed
    if (kbhit())
    {
        // getch returns the button that is being pressed
        switch (getch())
        {
        case 'a':
            sDir = LEFT;
            break;
        case 'd':
            sDir = RIGHT;
            break;
        case 's':
            sDir = UP;
            break;
        case 'w':
            sDir = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}

int main()
{
    int difficulty = setDifficulty();
    GameInit();
    while (!isGameOver)
    {
        GameRender();
        UserInput();
        UpdateGame();
        // Delay according to the chosen difficulty
        Sleep(difficulty);
    }
    return 0;
}