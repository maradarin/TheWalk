#include "robin.h"
#include "robot.h"
#include "harta.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>


void robin::Move(harta &H, strategy &S)
{
    int row=getPos().first, col=getPos().second, viz=getViz();
    int ok=0;
    S.trigger(row,col,viz,H.matrix);
    S.check(make_pair(row,col),viz,H.matrix);

    //retinem coordonatele itemurilor proprii din perimetrul vizibil
    for(int i=max(0,row-viz); i<min(H.n,row+viz+1); i++)
        for(int j=max(0,col-viz); j<min(H.m,col+viz+1); j++)
            if(S.getCell(i,j)!=-1 && S.findCoord(i,j,Coord2)==true && H.matrix[i][j]=='2')
                Coord2.push_back(make_pair(i,j));

    //daca destinatia finala e in raza lui de actiune, atunci robotul o sa se indrepte spre ea
    if (abs(H.finish.first - row) <= viz && abs(H.finish.second - col) <= viz)
    {
        if(getIT(2)>0 && H.finish.first>row && H.finish.second>col && row<H.n-1 && col<H.m-1)
        {
            //avand itemul 2, robotul se poate misca si pe diagonala
            //daca are si itemul 1, robotul devine imun la senzori
            if(S.getCell(row+1,col+1)!=-1 || (getIT(1)>0 && H.matrix[row+1][col+1]=='Z'))
            {
                row++;
                col++;
                ok=1;
            }
        }
        else if(getIT(2)>0 && H.finish.first>row && H.finish.second<col && col>=1)
        {
            if(S.getCell(row+1,col-1)!=-1 || (getIT(1)>0 && H.matrix[row+1][col-1]=='Z'))
            {
                row++;
                col--;
                ok=1;
            }
        }
        else if(getIT(2)>0 && H.finish.first<row && H.finish.second>col && row>=1)
        {
            if(S.getCell(row-1,col+1)!=-1 || (getIT(1)>0 && H.matrix[row-1][col+1]=='Z'))
            {
                row--;
                col++;
                ok=1;
            }
        }
        else if(getIT(2)>0 && H.finish.first<row && H.finish.second<col && row>=1 && col>=1)
        {
            if(S.getCell(row-1,col-1)!=-1 || (getIT(1)>0 && H.matrix[row-1][col-1]=='Z'))
            {
                row--;
                col--;
                ok=1;
            }
        }
        //altfel cautam o celula libera ca sa ne apropiem de finish
        else if (H.finish.first < row && row>=1 && S.getCell(row-1,col)!=-1)
        {
            row--;
            ok=1;
        }
        else if (H.finish.first > row && S.getCell(row+1,col)!=-1)
        {
            row++;
            ok=1;

        }
        else if (H.finish.second < col && col>=1 && S.getCell(row,col-1)!=-1)
        {
            col--;
            ok=1;
        }
        else if (H.finish.second > col && S.getCell(row,col+1)!=-1)
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
                if(getIT(2)>0 && it->first>row && it->second>col && row<H.n-1 && col<H.m-1)
                {
                    //avand itemul 2, robotul se poate misca si pe diagonala
                    //daca are si itemul 1, robotul devine imun la senzori
                    if(S.getCell(row+1,col+1)!=-1 || (getIT(1)>0 && H.matrix[row+1][col+1]=='Z'))
                    {
                        row++;
                        col++;
                        ok=1;
                    }
                }
                else if(getIT(2)>0 && it->first>row && it->second<col && col>=1)
                {
                    if(S.getCell(row+1,col-1)!=-1 || (getIT(1)>0 && H.matrix[row+1][col-1]=='Z'))
                    {
                        row++;
                        col--;
                        ok=1;
                    }
                }
                else if(getIT(2)>0 && it->first<row && it->second>col && row>=1)
                {
                    if(S.getCell(row-1,col+1)!=-1 || (getIT(1)>0 && H.matrix[row-1][col+1]=='Z'))
                    {
                        row--;
                        col++;
                        ok=1;
                    }
                }
                else if(getIT(2)>0 && it->first<row && it->second<col && row>=1 && col>=1)
                {
                    if(S.getCell(row-1,col-1)!=-1 || (getIT(1)>0 && H.matrix[row-1][col-1]=='Z'))
                    {
                        row--;
                        col--;
                        ok=1;
                    }
                }
                //altfel cautam o celula libera ca sa ne apropiem de finish
                else if (it->first < row && row>=1 && S.getCell(row-1,col)!=-1)
                {
                    row--;
                    ok=1;
                }
                else if (it->first > row && S.getCell(row+1,col)!=-1)
                {
                    row++;
                    ok=1;

                }
                else if (it->second < col && col>=1 && S.getCell(row,col-1)!=-1)
                {
                    col--;
                    ok=1;
                }
                else if (it->second > col && S.getCell(row,col+1)!=-1)
                {
                    col++;
                    ok=1;
                }
            }
    }
    else
    {
        if(getIT(2)>0 && row<H.n-1 && col<H.m-1 && S.getCell(row+1,col+1)!=-1)
        {
            row++;
            col++;
            ok=1;
        }
        else if(getIT(2)>0 && row<H.n-1 && col>=1 && S.getCell(row+1,col-1)!=-1)
        {
            row++;
            col--;
            ok=1;
        }
        else if(getIT(2)>0 && row>=1 && col<H.m-1 && S.getCell(row-1,col+1)!=-1)
        {
            row--;
            col++;
            ok=1;
        }
        else if(row<H.n-1 && S.getCell(row+1,col)!=-1)
        {
            row++;
            ok=1;
        }
        else if(col<H.n-1 && S.getCell(row,col+1)!=-1)
        {
            col++;
            ok=1;
        }
        else if(col>=1 && S.getCell(row,col-1)!=-1)
        {
            col--;
            ok=1;
        }
        else if(row>=1 && S.getCell(row-1,col)!=-1)
        {
            row--;
            ok=1;
        }
    }

    if(ok==0)
    {
        if(getIT(2)>0 && getIT(1)>0)    //item 1+2 = imunitate la senzori
        {
            //in plus, itemul 2 permite miscarea pe diagonala
            if(row<H.n-1 && col<H.m-1 && S.getCell(row+1,col+1)!=-1)
            {
                row++;
                col++;
                ok=1;
            }
            else if(row<H.n-1 && col>=1 && S.getCell(row+1,col-1)!=-1)
            {
                row++;
                col--;
                ok=1;
            }
            else if(row>=1 && col<H.m-1 && S.getCell(row-1,col+1)!=-1)
            {
                row--;
                col++;
                ok=1;
            }
            else if(row<H.n-1 && H.matrix[row+1][col]=='Z')
            {
                row++;
                ok=1;
            }
            else if(col<H.m-1 && H.matrix[row][col+1]=='Z')
            {
                col++;
                ok=1;
            }
            else if(row>=1 && H.matrix[row-1][col]=='Z')
            {
                row--;
                ok=1;
            }
            else if(col>=1 && H.matrix[row][col-1]=='Z')
            {
                col--;
                ok=1;
            }
            if(ok==1)
                H.matrix[row][col]='?'; // Semnul specific pt senzor evitat
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
        else if(col>=1 && H.matrix[row][col-1]=='X')
        {
            col--;
            ok=1;
        }
        else if(row>=1 && H.matrix[row-1][col]=='X')
        {
            row--;
            ok=1;
        }

        if(ok==1)
        {
            setVieti(getVieti()-1);
            if(getIT(3)>0)
                setVieti(getVieti()-1);
            H.matrix[row][col]='@'; //Semn specific pt capcana declansata (seamana cu o explozie)
        }
    }


    if(ok==0)       // al doilea compromis: senzorii
    {
        if(row<H.n-1 && H.matrix[row+1][col]=='Z')
        {
            row++;
            ok=1;
        }
        else if(col<H.m-1 && H.matrix[row][col+1]=='Z')
        {
            col++;
            ok=1;
        }
        else if(col>=1 && H.matrix[row][col-1]=='Z')
        {
            col--;
            ok=1;
        }
        else if(row>=1 && H.matrix[row-1][col]=='Z')
        {
            row--;
            ok=1;
        }

        if(ok==1)
        {
            if(getIT(2)*getIT(1)==0)
                setVieti(getVieti()-2);
            H.matrix[row][col]='*';  //Semn specific pt senzor alertat
        }
    }

    if(ok==0)
    {
        if(row<H.n-1 && H.matrix[row+1][col]=='3')
        {
            row++;
            ok=1;
        }
        else if(col<H.m-1 && H.matrix[row][col+1]=='3')
        {
            col++;
            ok=1;
        }
        else if(col>=1 && H.matrix[row][col-1]=='3')
        {
            col--;
            ok=1;
        }
        else if(row>=1 && H.matrix[row-1][col]=='3')
        {
            row--;
            ok=1;
        }
    }
    if(H.matrix[row][col]=='_')
        H.matrix[row][col]='R';
    if(isBlocked(row,col,H)==true || S.isBlocked(row,col,H)==true)
        setVieti(-100);
    setPos(row,col);
    EffectItem(row,col,H);
}


void robin::EffectItem(const int x, const int y, harta &H)
{
    char *message =new char[1000];
    message[0]='\0';
    if(H.matrix[x][y]=='2')
    {
        Coord2.erase(remove(Coord2.begin(), Coord2.end(), make_pair(x,y)), Coord2.end());
        strcpy(message, "You found a robin-item! This will increase your visibility with 1 point and help you move diagonally.\n");
        setIT(2,getIT(2)+1);
        setViz(getViz()+1);
        H.matrix[x][y]='R';
    }
    else if(H.matrix[x][y]=='3')
    {
        strcpy(message, "Oh no, you found a joker-item! In order to save yourself, exchange a robin item.\n");
        if(getIT(2)>0)
        {
            setIT(2,getIT(2)-1);
            setViz(getViz()-1);
            strcat(message,"You got lucky and managed to get rid of the joker-item!\n");
        }
        else
        {
            setIT(3,getIT(3)+1);
            strcat(message,"The joker-item stuck with you and each time you cross over a bomb, you shall lose 2 lives.\n");
        }
        H.matrix[x][y]='R';
    }
    else if(H.matrix[x][y]=='1')
    {
        setIT(1,1);
        strcpy(message, "You found a batman-item which will aid Robin in his quest!\n");
        if(getIT(2)>0)
            strcat(message, "You have gained immunity to all sensors.\n");
        H.matrix[x][y]='R';
    }
    cout<<message;
    delete[] message;
}


robin::~robin()
{
    Coord2.clear();
}
