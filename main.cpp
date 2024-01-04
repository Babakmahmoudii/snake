#include <iostream>
#include <conio.h>
#include <ctime>
#include <fstream>

#include "Snake.h"
#include "Food.h"

#define WIDTH 50
#define HEIGHT 25

using namespace std;

Snake snake({WIDTH / 2, HEIGHT / 2}, 1 ,1);
Food food;

int score;

void gotoxy(int x, int y)
{ // to print in any place you want
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void board()
{
    COORD snake_pos = snake.get_pos();
    COORD food_pos = food.get_pos();

    vector<COORD> snake_body = snake.get_body();

    cout << "SCORE : " << score << "\n\n";

    for (int i = 0; i < HEIGHT; i++)
    {
        cout << "\t\t#";
        for (int j = 0; j < WIDTH - 2; j++)
        {
            if (i == 0 || i == HEIGHT - 1)
                cout << '#';

            else if (i == snake_pos.Y && j + 1 == snake_pos.X) // symbol head snake
                cout << 'O';
            else if (i == food_pos.Y && j + 1 == food_pos.X) // symbol eat
                cout << '*';

            else
            {
                bool isBodyPart = false;
                for (int k = 0; k < snake_body.size() - 1; k++)
                {
                    if (i == snake_body[k].Y && j + 1 == snake_body[k].X) // symbol body snake
                    {
                        cout << 'o';
                        isBodyPart = true;
                        break;
                    }
                }

                if (!isBodyPart)
                    cout << ' ';
            }
        }
        cout << "#\n";
    }
}

int main()
{
    gotoxy(0, 2); // menu Snake Game
    cout << "*                 *";
    gotoxy(0, 3);
    cout << "*    Snake Game   *";
    gotoxy(0, 4);
    cout << "*                 *";
    gotoxy(0, 4);
    cout << "*                 *";
    gotoxy(0, 5);
    cout << "*                 *";
    gotoxy(0, 6);
    cout << "*                 *";
    gotoxy(0, 7);
    cout << "*                 *";
    gotoxy(0, 8);
    cout << "*                 *";
    gotoxy(0, 9);
    cout << "*                 *";
    gotoxy(0, 10);
    cout << "*                 *";
    gotoxy(0, 11);
    cout << "*                 *";
    gotoxy(0, 12);
    cout << "*    press   b    *";
    gotoxy(0, 13);
    cout << "*  Go Last Game   *";
    gotoxy(0, 14);
    cout << "*                 *";
    gotoxy(0, 15);
    cout << "*  Pess 'Space'   *";
    gotoxy(0, 16);
    cout << "*    To Start     *";
    gotoxy(0, 17);
    cout << "*                 *";

    int select = _getch();

    if (select == 32)
    {
        score = 0;
        srand(time(NULL));

        food.gen_food();

        bool game_over = false;

        while (!game_over)
        {
            board();

            if (kbhit())
            {
                switch (getch()) // Kontrol move snake
                {
                case 'w':
                    snake.direction('u');
                    break;
                case 'a':
                    snake.direction('l');
                    break;
                case 's':
                    snake.direction('d');
                    break;
                case 'd':
                    snake.direction('r');
                    break;
                case 'q':
                    snake.save(score);
                    exit(1);
                }
            }

            if (snake.collided()) // lose
                game_over = true;

            if (snake.eaten(food.get_pos())) // eat food and plus score
            {
                food.gen_food();
                snake.grow();
                score = score + 10;
            }

            snake.move_snake();
            Sleep(50); // delay in game
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
        }
    }
    else if (select == 'b')
    {
        ifstream inFile("player.txt"); // open file
        if (inFile.is_open())
        {
            inFile >> score; // cin score last game
        }
        else
        {
            cerr << "Unable to open file for reading." << endl;
        }
        srand(time(NULL));

        food.gen_food();

        bool game_over = false;

        while (!game_over)
        {
            board();

            if (kbhit())
            {
                switch (getch()) // cin kebord
                {
                case 'w':
                    snake.direction('u');
                    break;
                case 'a':
                    snake.direction('l');
                    break;
                case 's':
                    snake.direction('d');
                    break;
                case 'd':
                    snake.direction('r');
                    break;
                case 'q':
                    snake.save(score);
                    exit(1);
                }
            }

            if (snake.collided())
                game_over = true;

            if (snake.eaten(food.get_pos()))
            {
                food.gen_food();
                snake.grow();
                score = score + 10;
            }

            snake.move_snake();
            Sleep(50); // delae in game
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
        }
    }

    return 0;
}
