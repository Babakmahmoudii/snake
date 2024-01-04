#ifndef SNAKE_H
#define SNAKE_H

#include <windows.h>
#include <vector>

#define WIDTH 50 
#define HEIGHT 25

using namespace std;

class Snake // difine snake class
{
    private:
        COORD pos;
        int vel;
        char dir;
        int len;
        vector<COORD> body;

    public:
        Snake(COORD pos, int vel , int len ); // snake constroctor

        void grow();
        void move_snake();
        void direction(char dir);

        vector<COORD> get_body();

        bool collided();
        bool eaten(COORD food);

        COORD get_pos();

        void save(int score);

};

#endif // SNAKE_H
