// Tommy Lynch and Will Fritz
// NDID: Tlynch2 and Wfritz
//
// game of snake final project
#include<iostream>
#include"gfxnew.h"
#include<unistd.h>
#include<ctime>
#include<vector>
#include<array>
#include<cmath>
#include<cstdlib>
#include"snake.h"
#include<stdlib.h>

using namespace std;

array<int,2> newfood(int, int, snake);
void changedirection(char, bool &, snake &);

int main(){
    int xsize = 500, ysize = 520; //size of window 
    int score = 0; // stores the location of the food and initializes score
    bool holdLoop = true;
    int event, counter = 0;
    char c;
    char scoretext[6];
    array<int,2> food;
    gfx_open(xsize,ysize,"snake");
    gfx_clear();
    snake snake1;
    snake1.move();


    while(holdLoop){
        gfx_clear();
        //handles the food
        if (counter == 0){
            food = newfood(xsize,ysize, snake1);
            counter+=1;
        }
        gfx_color(255,0,0);
        gfx_rectangle(food[0], food[1], 10, 10);
        
        // Sets up the static parts of the board
        gfx_color(255,255,255);
        gfx_line(0,(ysize-20), xsize, (ysize-20)); //line as bottom border
        gfx_text(0,(ysize-5), "Score: ");
        sprintf(scoretext,"%d",score);
        gfx_text(40, (ysize-5), scoretext);
        gfx_text(200, (ysize-5), "q to quit, p to pause, s to resume");

        // Sets up the game
        if(snake1.check(food[0],food[1])){
            snake1.grow();
            score+=10;
            food = newfood(xsize,ysize,snake1);
            continue;
        } 
        snake1.move();

        if(snake1.checkSelf() || snake1.checkBorder(xsize,(ysize-20))){
            gfx_clear();
            gfx_color(255,255,255);
            gfx_text(225,225,"GAME OVER");
            gfx_text(190,400, "q to quit, r to restart");   
            gfx_text(0,(ysize-5), "Score: ");
            gfx_text(40, (ysize-5), scoretext);

            while (c != 'r' && c != 'q'){
                c = gfx_wait();
            }
            if (c == 'q') holdLoop = false;
            else if (c == 'r') {
                snake1.reset();
                score = 0;
            }
        }
        gfx_flush();
  
        if ((event = gfx_event_waiting())){
            c = gfx_wait();
            changedirection(c, holdLoop,  snake1);
        }
        // clear buffer using gfx_event_waiting and gfx_wait
        while(gfx_event_waiting()){
            gfx_wait();
        }
        usleep(80000);
    }

}

array<int,2> newfood(int xsize, int ysize, snake s){
    int xpos, ypos;
    srand(time(NULL));
    xpos = rand()%((xsize-9)/10)*10; // random multiples of 10  between 0 and 490
    ypos = rand()%((ysize-19)/10)*10;// random multiples of 10 between 0 and 490
    
    while(s.check(xpos, ypos)){
        xpos = rand()%((xsize-9)/10)*10; // random multiples of 10  between 0 and 490
        ypos = rand()%((ysize-19)/10)*10;// random multiples of 10 between 0 and 490
    }
    // makes the food on the screen
    gfx_color(255,0,0);
    gfx_rectangle(xpos, ypos, 10, 10);
    array<int,2> arr = {xpos, ypos};
    return arr;
}




void changedirection(char c, bool &loop, snake &s){
    int dx = s.getDx();
    int dy = s.getDy();

    switch(c){
        case 'R':                   // up arrow
            if (dy == 10) return;
            s.setChange(0,0);
            s.up();
            break;
        case 'Q':                   // left arrow
            if (dx == 10) return;
            s.setChange(0,0);
            s.left();
            break;
        case 'T':                   // down arrow
            if (dy == -10) return;
            s.setChange(0,0);
            s.down();
            break;
        case 'S':                   // right arrow
            if (dx == -10) return;
            s.setChange(0,0);
            s.right();
            break;
        case 'q':                   // quit the game
            loop = false;
            break;
        case 'p':                   // pause the game
            s.setChange(0,0);
            c = 'w';
            while(s.getDx() == 0 && s.getDy() == 0){ 
                if (c == 's') s.setChange(dx,dy);
                c = gfx_wait();
            }
            break;
        default:
            break;
    }
}


