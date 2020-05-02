#include "strategy.h"
#include "robot.h"
#include "joker.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;

strategy::strategy(int a = 0, int b = 0)
    : n(a)
    , m(b)
{
    dist = new int*[n];
    for (int i = 0; i < n; i++)
        dist[i] = new int[m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dist[i][j] = -1;
}

bool strategy::isValid(const int x, const int y, const char c, char** matrix) const
{
    if (c == 'Z') {
        if (x < n && y < m && x >= 0 && y >= 0 && matrix[x][y] == '_')
            return true;
        return false;
    }
    else {
        if (x < n && y < m && x >= 0 && y >= 0) {
            const char ok[] = "_123F";
            if (robot::correct(ok, matrix[x][y]) == true)
                return true;
        }
        return false;
    }
}

bool strategy::findCoord(const int a, const int b, vector<pair<int, int> > V) const
{
    pair<int, int> p = make_pair(a, b);
    if (find(V.begin(), V.end(), p) != V.end())
        return false;
    return true;
}

bool strategy::isBlocked(const int row, const int col, harta& H) const //verificam mutarile pe diagonala
{
    const char obs[] = "R@?!*S";
    if (row == 0) {
        if (robot::correct(obs, H.getCell(row + 1, col - 1)) == true) {
            if (col == H.getDim().second - 1)
                return true;
            if (col < H.getDim().second - 1) {
                if (robot::correct(obs, H.getCell(row + 1, col + 1)) == true)
                    return true;
            }
        }
    }
    else if (col == 0) {
        if (robot::correct(obs, H.getCell(row - 1, col + 1)) == true) {
            if (row == H.getDim().first - 1)
                return true;
            if (row < H.getDim().first - 1) {
                if (robot::correct(obs, H.getCell(row + 1, col + 1)) == true)
                    return true;
            }
        }
    }
    else if (row == H.getDim().first - 1) {
        if (robot::correct(obs, H.getCell(row - 1, col - 1)) == true) {
            if (col == H.getDim().second - 1)
                return true;
            if (col < H.getDim().second - 1) {
                if (robot::correct(obs, H.getCell(row - 1, col + 1)) == true)
                    return true;
            }
        }
    }
    else if (col == H.getDim().second - 1) {
        if (robot::correct(obs, H.getCell(row - 1, col - 1)) == true && robot::correct(obs, H.getCell(row + 1, col - 1)) == true)
            return true;
    }
    else {
        if (robot::correct(obs, H.getCell(row + 1, col - 1)) == true && robot::correct(obs, H.getCell(row + 1, col + 1)) == true && robot::correct(obs, H.getCell(row - 1, col + 1)) == true && robot::correct(obs, H.getCell(row - 1, col - 1)) == true)
            return true;
    }
    return false;
}

bool strategy::threeCells(int& row, int& col, harta& H, const char ok[], joker& J) const
{
    int old_r = row, old_c = col;
    if (J.getMode() % 4 == 0 && col <= H.getDim().second - J.getRight() - 4) {
        if (robot::correct(ok, H.getCell(row, col + 3)) == true)
            col += 3;
        else if (robot::correct(ok, H.getCell(row, col + 2)) == true)
            col += 2;
    }
    else if (J.getMode() % 4 == 1 && row <= H.getDim().first - J.getDown() - 4) {
        if (robot::correct(ok, H.getCell(row + 3, col)) == true)
            row += 3;
        else if (robot::correct(ok, H.getCell(row + 2, col)) == true)
            row += 2;
    }
    else if (J.getMode() % 4 == 2 && col >= J.getLeft() - 3) {
        if (robot::correct(ok, H.getCell(row - 3, col)) == true)
            row -= 3;
        else if (robot::correct(ok, H.getCell(row - 2, col)) == true)
            row -= 2;
    }
    else if (J.getMode() % 4 == 3 && row >= J.getUp() - 3) {
        if (robot::correct(ok, H.getCell(row, col - 3)) == true)
            col -= 3;
        else if (robot::correct(ok, H.getCell(row, col - 2)) == true)
            col -= 2;
    }
    if (row - old_r == 0 && col - old_c == 0)
        return false;
    return true;
}

void strategy::trigger(int row, int col, int viz, char** matrix)
{
    int rowNum[] = { -1, 0, 0, 1 };
    int colNum[] = { 0, -1, 1, 0 };
    for (int i = max(0, row - viz); i < min(1 + row + viz, n); i++) //avand vizibilitatea de viz, verificam in avans posibilitatea
        for (int j = max(0, col - viz); j < min(col + viz + 1, m); j++) //declansarii senzorilor, ca sa-i putem evita
            if (matrix[i][j] == 'Z' && findCoord(i, j, ZCoord) == true) //aceasta conditie ne impiedica sa marcam casutele adiacente
            //ale senzorilor declansati anterior
            {
                ZCoord.push_back(make_pair(i, j));
                for (int k = 0; k < 4; k++)
                    if (isValid(i + rowNum[k], j + colNum[k], 'Z', matrix)) {
                        matrix[i + rowNum[k]][j + colNum[k]] = 'Z';
                        ZCoord.push_back(make_pair(i + rowNum[k], j + colNum[k]));
                    }
            }
}

void strategy::check(pair<int, int> curr, int viz, char** matrix)
{

    for (int i = max(0, curr.first - viz); i < min(n, curr.first + viz + 1); i++) {
        for (int j = max(0, curr.second - viz); j < min(m, curr.second + viz + 1); j++)
            dist[i][j] = -1;
    }
    int rowNum[] = { -1, 0, 0, 1, -1, 1, -1, 1 };
    int colNum[] = { 0, -1, 1, 0, -1, 1, 1, -1 };
    queue<pair<int, int> > q;
    q.push(curr);
    dist[curr.first][curr.second] = 0;

    while (!q.empty()) {
        pair<int, int> p = q.front();
        q.pop();
        int d = dist[p.first][p.second];

        int x = p.first;
        int y = p.second;

        for (int k = 0; k < 8; k++) {
            int xp = x + rowNum[k];
            int yp = y + colNum[k];
            if (isValid(xp, yp, 'm', matrix) && dist[xp][yp] == -1) {
                dist[xp][yp] = d + 1;
                q.push(make_pair(xp, yp));
            }
        }
    }
}

int strategy::getCell(const int row, const int col) const
{
    return dist[row][col];
}

strategy::~strategy()
{
    for (int i = 0; i < n; i++)
        delete[] dist[i];
    delete[] dist;

    n = 0;
    m = 0;

    ZCoord.clear();
}
