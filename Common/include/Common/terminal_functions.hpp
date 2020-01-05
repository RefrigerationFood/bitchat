#pragma once

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <ctime>
#include <ncurses.h>

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

/*void terminal_lnbuf(int yn) {
   struct termios oldt, newt;
   tcgetattr(0, &oldt);
   newt = oldt;
   if (!yn) newt.c_lflag &= ~ICANON;
   else newt.c_lflag |= ICANON;
   tcsetattr(0, TCSANOW, &newt);
}
 
void terminal_echo(int yn) {
   struct termios oldt, newt;
   tcgetattr(0, &oldt);
   newt = oldt;
   if (!yn) newt.c_lflag &= ~ECHO;
   else newt.c_lflag |= ECHO;
   tcsetattr(0, TCSANOW, &newt);
}
 
void SetChar(int x, int y , char sym ) { 
	printf("\x1B[%d;%df", y, x); 
	printf("%c", sym ); 
}

void gotoxy(int x,int y)
 {
 printf("%c[%d;%df",0x1B,y,x);
 }

void clrscr() { printf("\x1B[2J\x1B[0;0f"); }
 
int getch() {
   		 int ch;
   terminal_lnbuf(0);
   terminal_echo(0);
   ch = getchar();
   terminal_lnbuf(1);
   terminal_echo(1);
   return ch;
}
 
int getche() {
   register int ch;
   terminal_lnbuf(0);
   ch = getchar();
   terminal_lnbuf(1);
   return ch;
}
 
int kbhit() {
   register int ret;
   fd_set fds;
   terminal_lnbuf(0);
   terminal_echo(0);
   struct timeval tv;
   tv.tv_sec = 0;
   tv.tv_usec = 0;
   FD_ZERO(&fds);
   FD_SET(0, &fds);
   select(1, &fds, 0, 0, &tv);
   ret = FD_ISSET(0, &fds);
   terminal_lnbuf(1);
   terminal_echo(1);
   return ret;
}*/