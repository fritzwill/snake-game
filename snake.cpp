// Implementaion for snake class

#include "gfxnew.h"
#include "snake.h"
#include <deque>
#include <iostream>

using namespace std;

snake::snake(){
    xpos = 250;
    ypos = 250;
    dx = 0; // it will always start moving right
    dy = 0;
    length = 1;
    
    Square square;
    square.xi = xpos;
    square.yi = ypos;
    square.width = 10;
    square.height = 10;

    tail.push_back(square);
}

snake::snake(int x, int y){
    xpos = x;
    ypos = y;
    dx = 0;
    dy = 0;
    length = 1;
    
    Square square;
    square.xi = xpos;
    square.yi = ypos;
    square.width = 10;
    square.height = 10;

    tail.push_back(square);
}

snake::~snake(){
}

// the next four member functions change the direction
void snake::left(){ 
    dy = 0;
    dx = -10;
}

void snake::right(){
    dy = 0;
    dx = 10;
}

void snake::down(){
    dx = 0;
    dy = 10;
}

void snake::up(){
    dx = 0;
    dy = -10; 
}

// moves square
void snake::move(){
    int temp1, temp2;
    temp1 = tail[0].xi + dx;
    temp2 = tail[0].yi + dy;
    Square newSquare;
    newSquare = {temp1, temp2, tail[0].width, tail[0].height};
    tail.push_front(newSquare);
    tail.pop_back();  
    for (int i = 0; i < length; i++)
        gfx_rectangle(tail[i].xi, tail[i].yi, tail[i].width , tail[i].height);
}


void snake::grow(){
    // the following will make the new square in the same position as the current last element
    Square newS;
    newS.xi = tail[length-1].xi;
    newS.yi = tail[length-1].yi;
    newS.width = tail[length-1].width;
    newS.height = tail[length-1].height;
    gfx_rectangle(newS.xi, newS.yi, newS.width , newS.height);
    // adds the new square to the vector
    tail.push_back(newS);
    length += 1;
    
}

// Check if given point is at the location of any of the squares
bool snake::check(int x, int y){
    for(int i = 0; i < length; i++){
        if(tail[i].xi == x && tail[i].yi == y){
            return true;
        }
    }
    return false;
}

bool snake::checkSelf(){
    for(int i = 1; i < length; i++){
        if (tail[0].xi == tail[i].xi && tail[0].yi == tail[i].yi) return true;
    }
    return false;
}

bool snake::checkBorder(int a, int b){
    return (tail[0].xi < 0 || tail[0].yi < 0 || tail[0].xi > (a - 10) || tail[0].yi > (b-10));
}

void snake::setChange(int x, int y){
    dx = x;
    dy = y;
}

void snake::reset(){
    tail.clear();
    xpos = 250;
    ypos = 250;
    dx = 0; // it will always start moving right
    dy = 0;
    length = 1;
    
    Square square;
    square.xi = xpos;
    square.yi = ypos;
    square.width = 10;
    square.height = 10;

    tail.push_back(square);

}

int snake::getDx(){
    return dx;
}

int snake::getDy(){
    return dy;
}

