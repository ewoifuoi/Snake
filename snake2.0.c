/*************************************************************************
 
    

            > File Name: 贪吃蛇qwq          demo 2.0        update : 彻底消除闪动, 不再采用数组标记位置


	    > Author: ewoifuoi      
 ************************************************************************/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<windows.h>
#include<conio.h>

typedef struct Point {
    int x, y;
} point;

typedef struct Snake {
    int length;
    int speed;
    int color;
    int dead;
    point node[101];
} snake;


snake s;
int mark[30][15];
char in_put;
int dir;

void HideCursor();
void goto_xy(int x, int y);
void set_console_color(unsigned short color_index);
void hello();
void init();
void input();
void move();
void die();
void make_boundary();
void init_snake();
void print(int x, int y, int color, int w);

int main() {
    hello();
    init();
    while(1) {
        input();
        move();
        if(s.dead == 1) {
            die();
        }
    }
    return 0;
}

void hello() {
    srand(time(0));
    printf("\n\n\n\n\n\t\t\t\t贪吃蛇");
    printf("qwq");
    set_console_color(8);
    printf("\tdemo 2.0");
    set_console_color(7);
    printf("\n\n\n\n\t\t\t\t  输入任意键开始游戏...\n\n\n\n\n\n\n\n\n");
    while(1) {
        if(_kbhit()) {
            system("CLS");
            return ;
        }
        HideCursor();
        int qwq = rand() % 7 + 1;
        goto_xy(38,5);
        printf("   ");
        goto_xy(38,5);
        set_console_color(qwq);
        printf("qwq");
        set_console_color(7);
        goto_xy(34,9);
        printf("输入任意键开始游戏...");
        Sleep(500);
        goto_xy(34,9);
        printf("                     ");
        Sleep(200);
    }
    return ;
}

void init() {
    make_boundary();
    dir = 1;
    init_snake();
    memset(mark, 0, sizeof(mark));
    return ;
}

void input() {
    if(_kbhit()){
        in_put = getch();
        switch(in_put) {
            case 'a' : if(dir == 3 || dir == 4)dir = 2;break;
            case 'd' : if(dir == 3 || dir == 4)dir = 1;break;
            case 'w' : if(dir == 1 || dir == 2)dir = 3;break;
            case 's' : if(dir == 1 || dir == 2)dir = 4;break;
        }
    }
    return ;
}

void move() {
    print(s.node[s.length].x, s.node[s.length].y, s.color, 0);
    for(int i = s.length; i >= 1; i--) {
        mark[s.node[i].x][s.node[i].y] = 0;
        s.node[i].x = s.node[i - 1].x; s.node[i].y = s.node[i - 1].y;
        mark[s.node[i].x][s.node[i].y] = 1;
    }
    print(s.node[0].x, s.node[0].y, s.color, 0);
    switch(dir) {
        case 1 : s.node[0].x++;break;
        case 2 : s.node[0].x--;break;
        case 3 : s.node[0].y--;break;
        case 4 : s.node[0].y++;break;
    }
    print(s.node[0].x, s.node[0].y, s.color, 1);
    if(s.node[0].x == 0 && s.node[0].y == 0 && s.node[0].x == 30 && s.node[0].y == 15) {
        s.dead = 1;
        return ;
    }
    if(mark[s.node[0].x][s.node[0].y] == 1) {
        s.dead = 1;
        return ;
    }
    Sleep(s.speed);
    return ;
}
void die() {
    return ;
}

void goto_xy(int x, int y)//定位光标位置到指定坐标
{   
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x,y };
    SetConsoleCursorPosition(hOut, pos);
}

void set_console_color(unsigned short color_index)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_index);
}
//定义隐藏光标函数
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;    
	cursor.bVisible = FALSE;    
	cursor.dwSize = sizeof(cursor);    
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorInfo(handle, &cursor);
}
void make_boundary() {
    for(int i = 0; i <= 30; i++) {
        goto_xy(i,0);
        printf("X");
        goto_xy(i,15);
        printf("X");
    }
    for(int i = 0; i <= 15; i++) {
        goto_xy(0,i);
        printf("X");
        goto_xy(30,i);
        printf("X");
    }
    return ;
}

void init_snake() {
    s.length = 5;
    s.dead = 0;
    s.speed = 70;
    s.color = 7;
    s.node[0].x = 6;s.node[0].y = 6;
    mark[s.node[0].x][s.node[0].y] = 1;
    goto_xy(6,6);
    printf("O");
    s.node[1].x = 6;s.node[1].y = 5;
    mark[s.node[1].x][s.node[1].y] = 1;
    goto_xy(5,6);
    printf("O");
    s.node[2].x = 6;s.node[2].y = 4;
    mark[s.node[2].x][s.node[2].y] = 1;
    goto_xy(4,6);
    printf("O");
    s.node[3].x = 6;s.node[3].y = 3;
    mark[s.node[3].x][s.node[3].y] = 1;
    goto_xy(3,6);
    printf("O");
    s.node[4].x = 6;s.node[4].y = 2;
    mark[s.node[4].x][s.node[4].y] = 1;
    goto_xy(2,6);
    printf("O");
    s.node[5].x = 6;s.node[5].y = 1;
    mark[s.node[5].x][s.node[5].y] = 1;
    goto_xy(1,6);
    printf("O");
    return ;
}

void print(int x, int y, int color, int w) {
    HideCursor();
    set_console_color(color);
    goto_xy(x, y);
    switch(w) {
        case 0 : {
            printf(" ");
            break;
        }
        case 1 : {
            printf("O");
            break;
        }
        case 2 : {
            printf("X");
            break;
        }
    }
    set_console_color(7);
    return ;
}