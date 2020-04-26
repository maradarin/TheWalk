#include "robin.h"
#include "robot.h"
#include "harta.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>


bool robin::findCoord(int a, int b)
{
    pair<int, int> p=make_pair(a,b);
    if(find(Coord2.begin(), Coord2.end(), p) != Coord2.end()) return false;
    return true;
}


void robin::Move(harta &H)
{
    int ok=0, dist[20][20];
    H.trigger(row,col,viz);
    H.check(make_pair(row,col),viz);

    //retinem coordonatele itemurilor proprii din perimetrul vizibil
    for(int i=max(0,row-viz); i<min(H.n,row+viz+1); i++)
        for(int j=max(0,col-viz); j<min(H.m,col+viz+1); j++)
            if(dist[i][j]!=-1 && findCoord(i,j)==true && H.matrix[i][j]=='2') Coord2.push_back(make_pair(i,j));

    //cout<<Coord2.size()<<endl;
    //daca destinatia finala e in raza lui de actiune, atunci robotul o sa se indrepte spre ea
    if (abs(H.finish.first - row) <= viz && abs(H.finish.second - col) <= viz)
    {
        if(countItems2>0 && H.finish.first>row && H.finish.second>col && dist[row+1][col+1]!=-1)
        {
            row++;
            col++;
            ok=1;
        }
        else if(countItems2>0 && H.finish.first>row && H.finish.second<col && dist[row+1][col-1]!=-1 && col>=1)
        {
            row++;
            col--;
            ok=1;
        }
        else if(countItems2>0 && H.finish.first<row && H.finish.second>col && dist[row-1][col+1]!=-1 && row>=1)
        {
            row--;
            col++;
            ok=1;
        }
        else if (H.finish.first < row && dist[row-1][col]!=-1 && row>=1)
        {
            row--;
            ok=1;
        }
        else if (H.finish.first > row && dist[row+1][col]!=-1)
        {
            row++;
            ok=1;

        }
        else if (H.finish.second < col && dist[row][col-1]!=-1 && col>=1)
        {
            col--;
            ok=1;

        }
        else if (H.finish.second > col && dist[row][col+1]!=-1)
        {
            col++;
            ok=1;

        }
    }
    // Strategia lui este de a aduna cat mai multe itemuri inainte de a ajunge la destinatie. Va prefera sa se indrepte spre un item
    // de tip 2 decat sa treaca pe o celula goala
    else if(Coord2.size()>0)                // dupa destinatia finala, itemul 2 urmeaza ca prioritate
    {
        for(vector<pair<int,int> >::iterator it=Coord2.begin(); it!=Coord2.end() && ok==0; it++)
            if (abs(it->first - row) <= viz && abs(it->second - col) <= viz)
            {
                if(countItems2>0 && it->first>row && it->second>col && dist[row+1][col+1]!=-1)
                {
                    row++;
                    col++;
                    ok=1;
                }
                else if(countItems2>0 && it->first>row && it->second<col && dist[row+1][col-1]!=-1 && col>=1)
                {
                    row++;
                    col--;
                    ok=1;
                }
                else if(countItems2>0 && it->first<row && it->second>col && dist[row-1][col+1]!=-1 && row>=1)
                {
                    row--;
                    col++;
                    ok=1;
                }
                else if (it->first < row && dist[row-1][col]!=-1 && row>=1)
                {
                    row--;
                    ok=1;
                }
                else if (it->first > row && dist[row+1][col]!=-1)
                {
                    row++;
                    ok=1;
                }
                else if (it->second < col && dist[row][col-1]!=-1 && col>=1)
                {
                    col--;
                    ok=1;
                }
                else if (it->second > col && dist[row][col+1]!=-1)
                {
                    col++;
                    ok=1;
                }

                // daca itemul este chiar inaccesibil, trecem printr-o capcana pt a-l obtine; facem exceptie la itemul de tip joker
                else if(dist[row][col+1]==-1 && dist[row+1][col]==-1 && H.matrix[row][col+1]!='3' && H.matrix[row+1][col]!='3')
                {
                    col++;
                    ok=1;
                    if(H.matrix[row][col]=='Z') vieti=vieti-2;
                    else if(H.matrix[row][col]=='X') vieti--;
                }
            }
    }
    else
    {
        if(row==H.n-1)
        {
            row=0;
            col++;
        }
        else if(col==H.m-1)
        {
            row++;
            col=0;
        }
        else
        {
            if(countItems2>0 && H.finish.first>row && H.finish.second>col && dist[row+1][col+1]!=-1)
            {
                row++;
                col++;
                ok=1;
            }
            else if(countItems2>0 && H.finish.first>row && H.finish.second<col && dist[row+1][col-1]!=-1 && col>=1)
            {
                row++;
                col--;
                ok=1;
            }
            else if(countItems2>0 && H.finish.first<row && H.finish.second>col && dist[row-1][col+1]!=-1 && row>=1)
            {
                row--;
                col++;
                ok=1;
            }
            else if(dist[row+1][col]!=-1)
            {
                row++;
                ok=1;
            }
            else if(dist[row][col+1]!=-1)
            {
                col++;
                ok=1;
            }
            else if(dist[row][col-1]!=-1 && col>=1)
            {
                col--;
                ok=1;
            }
            else if(dist[row-1][col]!=-1 && row>=1)
            {
                row--;
                ok=1;
            }
        }
    }

    if(ok==0)
    {
        if(countItems2>1 && countItems1>0)    // item 1+2 = imunitate la senzori
        {
            if(H.matrix[row+1][col]=='Z')
            {
                row++;
                ok=1;
            }
            else if(H.matrix[row][col+1]=='Z')
            {
                col++;
                ok=1;
            }
            else if(H.matrix[row-1][col]=='Z' && row>=1)
            {
                row--;
                ok=1;
            }
            else if(H.matrix[row][col-1]=='Z' && col>=1)
            {
                col--;
                ok=1;
            }
            if(ok==1) H.matrix[row][col]='?'; // Semnul specific pt senzor evitat
        }
    }


    if(ok==0)   //Nu putem sa ne mutam pe orizontala (alta coloana) si nici nu vrem sa revenim la pozitia anterioara
    {
        //Cel mai acceptabil compromis: trecem prin capcana
        if(H.matrix[row+1][col]=='X')
        {
            row++;
            ok=1;
        }
        else if(H.matrix[row][col+1]=='X')
        {
            col++;
            ok=1;
        }
        else if(H.matrix[row][col-1]=='X' && col>=1)
        {
            col--;
            ok=1;
        }
        else if(H.matrix[row-1][col]=='X' && row>=1)
        {
            row--;
            ok=1;
        }

        if(ok==1)
        {
            vieti--;
            if(countItems3>0) vieti--;
            H.matrix[row][col]='@'; //Semn specific pt capcana declansata (seamana cu o explozie)
        }
    }


    if(ok==0)       // al doilea compromis: senzorii
    {
        if(H.matrix[row+1][col]=='Z')
        {
            row++;
            ok=1;
        }
        else if(H.matrix[row][col+1]=='Z')
        {
            col++;
            ok=1;
        }
        else if(H.matrix[row][col-1]=='Z' && col>=1)
        {
            col--;
            ok=1;
        }
        else if(H.matrix[row-1][col]=='Z' && row>=1)
        {
            row--;
            ok=1;
        }

        if(ok==1)
        {
            vieti-=2;
            H.matrix[row][col]='*';                     //Semn specific pt senzor alertat
        }
    }

    if(ok==0)
    {
        if(H.matrix[row+1][col]=='3')
        {
            row++;
            ok=1;
        }
        else if(H.matrix[row][col+1]=='3')
        {
            col++;
            ok=1;
        }
        else if(H.matrix[row][col-1]=='3' && col>=1)
        {
            col--;
            ok=1;
        }
        else if(H.matrix[row-1][col]=='3' && row>=1)
        {
            row--;
            ok=1;
        }
    }
    if(H.matrix[row][col]=='_') H.matrix[row][col]='R';
    EffectItem(row,col,H);
    if(isBlocked(row,col,H)==true) vieti=-100;
}


void robin::EffectItem(int x, int y, harta &H)
{
    char *message =new char[1000];
    message[0]='\0';
    if(H.matrix[x][y]=='2')
    {
        Coord2.erase(remove(Coord2.begin(), Coord2.end(), make_pair(x,y)), Coord2.end());
        strcpy(message, "You found a robin-item! This will increase your visibility with 1 point and help you move diagonally.\n");
        countItems2++;
        viz++;
        H.matrix[x][y]='R';
    }
    else if(H.matrix[x][y]=='3')
    {
        strcpy(message, "Oh no, you found a joker-item! In order to save yourself, exchange a robin item.\n");
        if(countItems2>0)
        {
            countItems2--;
            viz--;
            strcat(message,"You got lucky and managed to get rid of the joker-item!\n");
        }
        else
        {
            countItems3++;
            strcat(message,"The joker-item stuck with you and each time you cross over a bomb, you shall lose 2 lives.\n");
        }
        H.matrix[x][y]='R';
    }
    else if(H.matrix[x][y]=='1')
    {
        countItems1++;
        strcpy(message, "You found a batman-item which will aid Robin in his quest!\n");
        if(countItems2>0) strcat(message, "You have gained immunity to all sensors.\n");
        H.matrix[x][y]='R';
    }
    cout<<message;
    delete[] message;
}


/*robin::~robin()
{
    Coord2.clear();
}
*/
