#include "joker.h"
#include "robot.h"
#include "harta.h"
#include <cstring>
#include <cmath>
#include <algorithm>

int joker::leftCol = 0;
int joker::rightCol = 0;
int joker::upRow = 0;
int joker::downRow = 0;
int joker::mode = 0;

void joker::Move(harta& H, strategy& S)
{
    int row = getPos().first, col = getPos().second, viz = getViz();
    S.trigger(row, col, viz, H.matrix);

    if (abs(H.finish.first - row) <= viz && abs(H.finish.second - col) <= viz) {
        const char ok[] = "F";
        bool flag = S.threeCells(row, col, H, ok, *this);
        if (flag == false) {
            if (H.finish.first < row)
                row--;
            else if (H.finish.first > row)
                row++;
            else if (H.finish.second < col)
                col--;
            else if (H.finish.second > col)
                col++;
        }
    }
    else {
        const char ok[] = "_123";
        bool flag = false;
        if (getIT(2) > 0)
            flag = S.threeCells(row, col, H, ok, *this);
        if (flag == false) {
            if (mode % 4 == 0) {
                if (col == H.m - 1 - rightCol) {
                    row++;
                    mode++;
                    upRow++;
                }
                else
                    col++;
            }
            else if (mode % 4 == 1) {
                if (row == H.n - 1 - downRow) {
                    col--;
                    mode++;
                    rightCol++;
                }
                else
                    row++;
            }
            else if (mode % 4 == 2) {
                if (col == leftCol) {
                    row--;
                    mode++;
                    downRow++;
                }
                else
                    col--;
            }
            else if (mode % 4 == 3) {
                if (row == upRow) {
                    col++;
                    mode++;
                    leftCol++;
                }
                else
                    row--;
            }
        }
    }
    if(H.matrix[row][col]=='_')
        H.matrix[row][col] = 'R';
    if (getIT(3) >= 0 || getIT(1) == 0) {
        if (H.matrix[row][col] == 'X') {
            setVieti(getVieti() - 1);
            H.matrix[row][col] = '@';
        }
        else if (H.matrix[row][col] == 'Z') {
            setVieti(getVieti() - 2);
            H.matrix[row][col] = '*';
        }
    }
    setPos(row, col);
    EffectItem(row, col, H);
}

void joker::EffectItem(const int x, const int y, harta& H)
{
    char* message = new char[1000];
    message[0] = '\0';
    if (H.matrix[x][y] == '2') {
        strcpy(message, "You found a robin-item!\n");
        strcat(message, "You can skip over three cells.");
        setIT(2, getIT(2) + 1);
    }
    else if (H.matrix[x][y] == '3') {
        strcpy(message, "You found a joker-item!\n");
        setVieti(getVieti() + 3);
        if (getIT(1) > 0) {
            setIT(1, 0);
            setIT(3, getIT(3) + 1);
            strcat(message, "You lost your immunity, but gained 3 more lives.\n");
        }
        else
            strcat(message, "You gained 3 more lives.\n");
    }
    else if (H.matrix[x][y] == '1') {
        strcpy(message, "You found a batman-item!\n");
        setIT(1, getIT(1) + 1);
        strcat(message, "You gained immunity to all traps.\n");
    }
    cout << message;
    delete[] message;
}

int joker::getLeft() const
{
    return leftCol;
}

int joker::getRight() const
{
    return rightCol;
}

int joker::getUp() const
{
    return upRow;
}

int joker::getDown() const
{
    return downRow;
}

int joker::getMode() const
{
    return mode;
}
