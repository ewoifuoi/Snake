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

typedef struct Food {
    point location;
    int type;
} food;

food f;
snake s;
int mark[30][15];
char in_put;
int dir;
int mode = 0;
int score;
int h_score;

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
void make_food();
void eat();

int main() {
    hello();
    init();
    while(1) {
        input();
        move();
        if(s.dead == 1) {
            die();
            if(s.dead == 3) {
                system("CLS");
                init();
                continue;
            }
            break;
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
    make_food();
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
        int xx = s.node[i].x; int yy = s.node[i].y;
        mark[s.node[i].x][s.node[i].y] = 0;
        s.node[i].x = s.node[i - 1].x; s.node[i].y = s.node[i - 1].y;
        mark[s.node[i].x][s.node[i].y] = 1;
        print(s.node[i].x, s.node[i].y, s.color, 1);
    }
    switch(dir) {
        case 1 : s.node[0].x++;break;
        case 2 : s.node[0].x--;break;
        case 3 : s.node[0].y--;break;
        case 4 : s.node[0].y++;break;
    }
    print(s.node[0].x, s.node[0].y, s.color, 1);
    if(s.node[0].x == f.location.x && s.node[0].y == f.location.y) {
        eat();
    }
    if(s.node[0].x == 0 || s.node[0].y == 0 || s.node[0].x == 29 || s.node[0].y == 14) {
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
    FILE *fp;
    if((fp = fopen("snake_h_score.txt", "r+")) == NULL) {
        fp = fopen("snake_h_score.txt", "w+");
    }
    fscanf(fp,"%d", &h_score);
    s.dead = 1;
    if(score > h_score) {
        fclose(fp);
        fp = fopen("snake_h_score.txt", "w+");
        fprintf(fp,"%d",score);
        h_score = score;

    }
    system("CLS");
    printf("\n\n\n\n\n\n\n\t\t\t\t\t    你死了...\n\n");
    printf("\n\n\t\t\t\t\t当前分数为 : %d\n\n",score);
    printf("\t\t\t\t\t历史最高分数为 : %d\n\n",h_score);
    printf("\n\t\t\t\t  按 r键重来 , 按其余键结束游戏\n\n\n\n\n\n\n\n\n");
    char c = getch();
    if(c == 'r') {
        s.dead = 3;
    }
    else {
        s.dead = 2;
    }
    fclose(fp);
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
    s.speed = 100;
    s.color = 7;
    s.node[0].x = 6;s.node[0].y = 6;
    mark[s.node[0].x][s.node[0].y] = 1;
    goto_xy(6,6);
    printf("O");
    s.node[1].x = 5;s.node[1].y = 6;
    mark[s.node[1].x][s.node[1].y] = 1;
    goto_xy(5,6);
    printf("O");
    s.node[2].x = 4;s.node[2].y = 6;
    mark[s.node[2].x][s.node[2].y] = 1;
    goto_xy(4,6);
    printf("O");
    s.node[3].x = 3;s.node[3].y =6;
    mark[s.node[3].x][s.node[3].y] = 1;
    goto_xy(3,6);
    printf("O");
    s.node[4].x = 2;s.node[4].y = 6;
    mark[s.node[4].x][s.node[4].y] = 1;
    goto_xy(2,6);
    printf("O");
    s.node[5].x = 1;s.node[5].y = 6;
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
        case 3 : {
            printf("♥");
            break;
        }
    }
    set_console_color(7);
    return ;
}
void make_food() {
    srand(time(0));
    f.location.x = rand() % 28 + 1;
    f.location.y = rand() % 13 + 1;
    f.type = rand() % 4 ;
    int COLOR[4]={7 ,5, 2, 11};
    print(f.location.x, f.location.y, COLOR[f.type], 3);
    return ;
}

void eat() {
    int TYPE_SCORE[4] = {10, 50, 10, 10};
    print(f.location.x, f.location.y, 7, 0);
    mode = f.type;
    score += TYPE_SCORE[f.type];
    if(f.type == 1) {
        s.length *= 2;
    }
    else {
        s.length++;
    }
    make_food();
    return ;
}