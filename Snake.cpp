#include "Snake.h"
#include <fstream>
#include <iostream>

Snake::Snake(COORD pos, int vel, int len ) //constroctor
{
    this->pos = pos;
    this->vel = vel;

    dir = 'n';
    this->len = len;

    body.push_back(pos);
}

void Snake::direction(char dir) { this->dir = dir; }
void Snake::grow() { len++; }
COORD Snake::get_pos() { return pos; }

vector<COORD> Snake::get_body() { return body; }

void Snake::move_snake() // difaine move 
{
    switch(dir)
    {
        case 'u': pos.Y -= vel; break;
        case 'd': pos.Y += vel; break;
        case 'l': pos.X -= vel; break;
        case 'r': pos.X += vel; break;
    }

    body.push_back(pos);
    if(body.size() > len) body.erase(body.begin());
}

bool Snake::collided() // lose snake with collided to wall or owen
{
    if(pos.X < 1 || pos.X > WIDTH-2 || pos.Y < 1 || pos.Y > HEIGHT-2) return true;

    for(int i = 0; i < len-1; i++)
    {
        if(pos.X == body[i].X && pos.Y == body[i].Y) return true;
    }
    return false;
}

bool Snake::eaten(COORD food) // eat food 
{
    if(pos.X == food.X && pos.Y == food.Y) return true;
    return false;
}

void Snake::save( int score ){ // save score player on file

            ofstream outFile("player.txt"); // craet player file 
            if (outFile.is_open())
            {
                outFile << score << endl; // cout score in file
                outFile << vel << endl;
                outFile << len << endl;
                outFile.close();
                cout << endl << "Player data has been saved to file." << endl;
            }
            else
            {
                cerr << "Unable to open file for writing." << endl;
            }
}
