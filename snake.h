// Interface for snake class
#include <deque>
class snake {
    public:
        snake();
        snake(int, int);
        ~snake();  
        void left();
        void right();
        void down();
        void up();
        void move();
        void grow();
        bool check(int,int);
        bool checkSelf();
        bool checkBorder(int,int);
        void setChange(int,int);
        void reset();
        int getDx();
        int getDy();
    private:
        int xpos;
        int ypos;
        int dx;
        int dy;
        int length;
        
        // each individual sqaure that is part of the snake
        struct Square {
            int xi, yi, width, height;
        };
        //Square square; // member object of Square struct
        
        std::deque <Square> tail;
};

