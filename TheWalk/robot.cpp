#include "robot.h"
#include "harta.h"
#include <cstring>

int robot::vieti = 4;
int robot::countItems1 = 0;
int robot::countItems2 = 0;
int robot::countItems3 = 0;

robot::robot()
    : row(0)
    , col(0)
    , viz(2)
{
}

pair<int, int> robot::getPos() const
{
    return make_pair(row, col);
}

void robot::setPos(int a, int b)
{
    row = a;
    col = b;
}

int robot::getIT(const int type) const
{
    if (type == 1)
        return countItems1;
    if (type == 2)
        return countItems2;
    if (type == 3)
        return countItems3;
    return 0;
}

void robot::setIT(int type, int m)
{
    if (type == 1)
        countItems1 = m;
    else if (type == 2)
        countItems2 = m;
    else if (type == 3)
        countItems3 = m;
}

void robot::setViz(int nr)
{
    viz = nr;
}

void robot::setVieti(int nr)
{
    vieti = nr;
}

void robot::stats()
{
    cout << "You have " << vieti << " lives left\n";
    cout << "You have " << viz << " points of visibility\n";
    cout << "You gathered " << countItems1 << " batman items\n";
    cout << "You gathered " << countItems2 << " robin items\n";
    cout << "You gathered " << countItems3 << " joker items\n";
}

int robot::getVieti() const
{
    return vieti;
}

int robot::getViz() const
{
    return viz;
}

bool robot::correct(const char aux[], const char c)
{
    if (strchr(aux, c) != NULL)
        return true;
    return false;
}

//metoda verifica doar mutarile pe cele 4 directii
bool robot::isBlocked(const int row, const int col, harta& H) const
{
    const char obs[] = "R@?!*S";
    if (row == 0) {
        if (correct(obs, H.getCell(row, col - 1)) == true && correct(obs, H.getCell(row + 1, col)) == true) {
            if (col == H.getDim().second - 1)
                return true;
            if (col < H.getDim().second - 1) {
                if (correct(obs, H.getCell(row, col + 1)) == true)
                    return true;
            }
        }
    }
    else if (col == 0) {
        if (correct(obs, H.getCell(row - 1, col)) == true && correct(obs, H.getCell(row, col + 1)) == true) {
            if (row == H.getDim().first - 1)
                return true;
            if (row < H.getDim().first - 1) {
                if (correct(obs, H.getCell(row + 1, col)) == true)
                    return true;
            }
        }
    }
    else if (row == H.getDim().first - 1) {
        if (correct(obs, H.getCell(row, col - 1)) == true && correct(obs, H.getCell(row - 1, col)) == true) {
            if (col == H.getDim().second - 1)
                return true;
            if (col < H.getDim().second - 1) {
                if (correct(obs, H.getCell(row, col + 1)) == true)
                    return true;
            }
        }
    }
    else if (col == H.getDim().second - 1) {
        if (correct(obs, H.getCell(row - 1, col)) == true &&
            correct(obs, H.getCell(row, col - 1)) == true &&
            correct(obs, H.getCell(row + 1, col)) == true)
            return true;
    }
    else {
        if (correct(obs, H.getCell(row, col - 1)) == true &&
            correct(obs, H.getCell(row + 1, col)) == true &&
            correct(obs, H.getCell(row, col + 1)) == true &&
            correct(obs, H.getCell(row - 1, col)) == true)
            return true;
    }
    return false;
}
