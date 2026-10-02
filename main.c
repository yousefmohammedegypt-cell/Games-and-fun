#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

int gameOver;
int x, y;
int fruitX, fruitY;
int score;

int tailX[100], tailY[100];
int tailLength;

enum Direction {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum Direction direction;

void Setup()
{
    gameOver = 0;
    direction = STOP;

    x = WIDTH / 2;
    y = HEIGHT / 2;

    srand(time(NULL));

    fruitX = rand() % (WIDTH - 2) + 1;
    fruitY = rand() % (HEIGHT - 2) + 1;

    score = 0;
    tailLength = 0;
}

void Draw()
{
    system("cls");

    // Top border
    for (int i = 0; i < WIDTH; i++)
        printf("#");

    printf("\n");

    for (int i = 0; i < HEIGHT - 2; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0 || j == WIDTH - 1)
            {
                printf("#");
            }
            else if (i + 1 == y && j == x)
            {
                printf("O");
            }
            else if (i + 1 == fruitY && j == fruitX)
            {
                printf("*");
            }
            else
            {
                int printed = 0;

                for (int k = 0; k < tailLength; k++)
                {
                    if (tailX[k] == j && tailY[k] == i + 1)
                    {
                        printf("o");
                        printed = 1;
                        break;
                    }
                }

                if (!printed)
                    printf(" ");
            }
        }

        printf("\n");
    }

    // Bottom border
    for (int i = 0; i < WIDTH; i++)
        printf("#");

    printf("\nScore: %d\n", score);
    printf("Use Arrow Keys to move | X to quit\n");
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 72: // Up arrow
                if (direction != DOWN)
                    direction = UP;
                break;

            case 80: // Down arrow
                if (direction != UP)
                    direction = DOWN;
                break;

            case 75: // Left arrow
                if (direction != RIGHT)
                    direction = LEFT;
                break;

            case 77: // Right arrow
                if (direction != LEFT)
                    direction = RIGHT;
                break;

            case 'x':
            case 'X':
                gameOver = 1;
                break;
        }
    }
}

void Logic()
{
    // Move the tail
    int previousX = tailX[0];
    int previousY = tailY[0];

    int previous2X;
    int previous2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++)
    {
        previous2X = tailX[i];
        previous2Y = tailY[i];

        tailX[i] = previousX;
        tailY[i] = previousY;

        previousX = previous2X;
        previousY = previous2Y;
    }

    // Move the head
    switch (direction)
    {
        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;

        case UP:
            y--;
            break;

        case DOWN:
            y++;
            break;

        default:
            break;
    }

    // Collision with walls
    if (x <= 0 || x >= WIDTH - 1 ||
        y <= 0 || y >= HEIGHT - 1)
    {
        gameOver = 1;
    }

    // Collision with tail
    for (int i = 0; i < tailLength; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = 1;
        }
    }

    // Eating the fruit
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        tailLength++;

        fruitX = rand() % (WIDTH - 2) + 1;
        fruitY = rand() % (HEIGHT - 2) + 1;
    }
}

int main()
{
    Setup();

    while (!gameOver)
    {
        Draw();
        Input();
        Logic();

        Sleep(100);
    }

    system("cls");

    printf("========================================\n");
    printf("              GAME OVER!\n");
    printf("========================================\n");
    printf("Final Score: %d\n", score);
    printf("\nPress any key to exit...");

    _getch();

    return 0;
}
