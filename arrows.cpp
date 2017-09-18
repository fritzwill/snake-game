int event;
if ((event = gfx_event_waiting()) == 1){
    c = gfx_wait();
    changedirection(c, holdLoop,  snake);
}


void changedirection(char c, bool &loop, Snake &snake){
    switch(c){
        case 'R':                   // up arrow
            snake.up();
            break;
        case 'Q':                   // left arrow
            snake.left();
            break;
        case 'T':                   // down arrow
            snake.down();
            break;
        case 'S':                   // right arrow
            snake.right();
            break;
        case 'q':                   // quit the game
            loop = false;
            break;
        case 'p':                   // pause the game
            c = gfx_wait();
            while ( c != 'p'){
                c = gfx_wait();
            }
            break;
        default:
            return;
    }
            
