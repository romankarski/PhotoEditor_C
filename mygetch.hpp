#ifndef __mygetch__
#define __mygetch__
//--------------------------------------------------------
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
int mygetch ( void ) 
{
    int ch;
    struct termios oldt, newt;

    tcgetattr ( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    if (ch == '\033') { // if the first value is esc
        getchar(); // skip the [
        ch = getchar();
    }
    tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

    return ch;
}
//--------------------------------------------------------
#endif // define __mygetch__