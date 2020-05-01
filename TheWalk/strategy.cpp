#include "strategy.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

strategy::strategy(int a=0, int b=0):n(a), m(b)
{
    dist = new int*[n];
    for (int i = 0; i < n; i++)
        dist[i] = new int[m];
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            dist[i][j]=-1;
}

bool strategy::isValid(const int x, const int y, const char c, char **matrix) const
{
    if(c=='Z')
    {
        if (x < n && y < m && x >= 0 && y >= 0 && matrix[x][y]=='_') return true;
        return false;
    }
    else
    {
        if (x < n && y < m && x >= 0 && y >= 0)
        {
            if(matrix[x][y]=='1' || matrix[x][y]=='2' || matrix[x][y]=='_' || matrix[x][y]=='F') return true;
        }
        return false;
    }

}

bool strategy::findCoord(const int a, const int b) const
{
    pair<int, int> p=make_pair(a,b);
    if(find(ZCoord.begin(), ZCoord.end(), p) != ZCoord.end()) return false;
    return true;
}

void strategy::trigger(int row, int col, int viz, char **matrix)
{
    int rowNum[] = { -1, 0, 0, 1 };
    int colNum[] = { 0, -1, 1, 0 };
    for(int i=max(0,row-viz); i<min(1+row+viz,n); i++)                    //avand vizibilitatea de viz, verificam in avans posibilitatea
        for(int j=max(0,col-viz); j<min(col+viz+1,m); j++)                //declansarii senzorilor, ca sa-i putem evita
            if(matrix[i][j]=='Z' && findCoord(i,j)==true)                 //aceasta conditie ne impiedica sa marcam casutele adiacente
                //ale senzorilor declansati anterior
            {
                ZCoord.push_back(make_pair(i,j));
                for (int k = 0; k < 4; k++)
                    if (isValid(i + rowNum[k], j + colNum[k], 'Z', matrix))
                    {
                        matrix[i + rowNum[k]][j + colNum[k]] = 'Z';
                        ZCoord.push_back(make_pair(i+rowNum[k],j+colNum[k]));
                    }
            }
}

void strategy::check(pair<int,int> curr, int viz, char **matrix)
{

    for(int i=max(0,curr.first-viz); i<min(n,curr.first+viz+1); i++)
    {
        for(int j=max(0,curr.second-viz); j<min(m,curr.second+viz+1); j++)
            dist[i][j] = -1;
    }
    int rowNum[] = { -1, 0, 0, 1, -1, 1, -1,  1 };
    int colNum[] = { 0, -1, 1, 0, -1, 1,  1, -1 };
    queue<pair<int,int> > q;
    q.push(curr);
    dist[curr.first][curr.second] = 0;

    while(!q.empty())
    {
        pair<int,int> p = q.front();
        q.pop();
        int d = dist[p.first][p.second];

        int x = p.first;
        int y = p.second;

        for (int k = 0; k < 8; k++)
        {
            int xp = x + rowNum[k];
            int yp = y + colNum[k];
            if(isValid(xp,yp,'m',matrix) && dist[xp][yp] == -1)
            {
                dist[xp][yp] = d+1;
                q.push(make_pair(xp,yp));
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

    n=0;
    m=0;

    ZCoord.clear();
}

