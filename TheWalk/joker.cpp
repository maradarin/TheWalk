#include "joker.h"
#include "robot.h"
#include "harta.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <algorithm>

int joker::leftCol=0;
int joker::rightCol=0;
int joker::upRow=0;
int joker::downRow=0;
int joker::mode = 0;


void joker::Move(harta &H)
{
    H.trigger(row,col,viz);

    if (abs(H.finish.first - row) <= viz && abs(H.finish.second - col) <= viz)
    {
        if (H.finish.first < row) row--;
        else if (H.finish.first > row) row++;
        else if (H.finish.second < col) col--;
        else if (H.finish.second > col) col++;
    }
    else
    {
        if (mode % 4 == 0)
        {
            if (col == H.m - 1 - rightCol)
            {
                row++;
                mode++;
                upRow++;
            }
            else col++;
        }
        else if (mode % 4 == 1)
        {
            if (row == H.n - 1 - downRow)
            {
                col--;
                mode++;
                rightCol++;
            }
            else row++;
        }
        else if (mode % 4 == 2)
        {
            if (col == 0 + leftCol)
            {
                row--;
                mode++;
                downRow++;
            }
            else col--;
        }
        else if (mode % 4 == 3)
        {
            if (row == 0 + upRow)
            {
                col++;
                mode++;
                leftCol++;
            }
            else row++;
        }
    }
    if(countItems3>0 || countItems1==0) {if(H.matrix[row][col]=='X') vieti--; else if(H.matrix[row][col]=='Z') vieti-=2; }
    else if(countItems2>0) {if(H.matrix[row][col]=='Z') vieti-=2;}
    H.matrix[row][col]='R';
    EffectItem(row,col,H);
}


void joker::EffectItem(const int x, const int y, harta &H)
{
    char *message =new char[1000];
    message[0]='\0';
    if(H.matrix[x][y]=='2')
    {
        strcpy(message, "You found a robin-item!\n");
        strcat(message,"You've lost your immunity to sensors, but gained one more visibility point.");
        countItems2=1;
        viz++;
    }
    else if(H.matrix[x][y]=='3')
    {
        strcpy(message, "You found a joker-item!\n");
        vieti+=3;
        if(countItems1>0)
        {
            countItems1=0;
            strcat(message,"You lost your immunity, but gained 3 more lives.\n");
        }
        else strcat(message,"You gained 3 more lives.\n");
    }
    else if(H.matrix[x][y]=='1')
    {
        strcpy(message, "You found a batman-item!\n");
        countItems1=1;
        strcat(message, "You gained immunity to all traps.\n");
    }
    cout<<message;
    delete[] message;
}



/*joker::~joker()
{
    //destructor
}
*/
