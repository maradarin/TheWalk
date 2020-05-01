#include "batman.h"
#include "robot.h"
#include "harta.h"
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <algorithm>


void batman::Move(harta &H)
{
    int ok=0;
    int row=getPos().first, col=getPos().second, viz=getViz();
    EffectItem(row,col,H);
    H.trigger(row,col,viz);
    H.check(make_pair(row,col),viz);

    //daca destinatia finala e in raza lui de actiune, atunci robotul o sa se indrepte spre ea
    if (abs(H.finish.first - row) <= viz && abs(H.finish.second - col) <= viz)
    {
        if (H.finish.first < row && row>=1)
        {
            {
                row--;
                ok=1;
            }
        }
        else if (H.finish.first > row)
        {
            if(H.dist[row+1][col]!=-1)
            {
                row++;
                ok=1;
            }
        }
        else if (H.finish.second < col && col>=1)
        {
            if(H.dist[row][col-1]!=-1)
            {
                col--;
                ok=1;
            }
        }
        else if (H.finish.second > col)
        {
            if(H.dist[row][col+1]!=-1)
            {
                col++;
                ok=1;
            }
        }
    }
    else
    {
        if(row==H.n-1)
        {
            if((H.matrix[0][col+1]=='_' || H.matrix[0][col+1]=='1' || H.matrix[0][col+1]=='2') ||
               (getIT(1)>0 && getIT(2)>0) || (getIT(1)>0 && H.matrix[0][col+1]=='X'))
            {
                row=0;
                col++;
                ok=1;
                if(getIT(1)>0 && getIT(2)>0 && H.matrix[row][col]=='Z') H.matrix[row][col]='?';
                if(getIT(1)>0 && H.matrix[row][col]=='X') H.matrix[row][col]='!';
            }
        }
        else if(col==H.m-1)
        {
            if((H.matrix[row+1][0]=='_' || H.matrix[row+1][0]=='1' || H.matrix[row+1][0]=='2') ||
               (getIT(1)>0 && getIT(2)>0) || (getIT(1)>0 && H.matrix[row+1][0]=='X'))
            {
                row++;
                col=0;
                ok=1;
                if(getIT(1)>0 && getIT(2)>0 && H.matrix[row][col]=='Z') H.matrix[row][col]='?';
                if(getIT(1)>0 && H.matrix[row][col]=='X') H.matrix[row][col]='!';
            }
        }
        else
        {
            if(H.dist[row+1][col]!=-1)
            {
                row++;
                ok=1;
            }
            else if(H.dist[row][col+1]!=-1)
            {
                col++;
                ok=1;
            }
            else if(col>=1 && H.dist[row][col-1]!=-1)
            {
                col--;
                ok=1;
            }
            else if(row>=1 && H.dist[row-1][col]!=-1)
            {
                row--;
                ok=1;
            }

        }
    }
    // Strategia lui este de a ajunge la destinatie cu orice pret, dar sa pastreze cat mai multe itemuri cu putinta
    // in eventualitatea in care este nevoit sa aleaga o ruta ce contine un item de tip joker ce-i reduce semnificativ nr de vieti
    // Bineinteles, itemul de tip batman e cel mai important pentru el, deci daca are itemuri de tip robin va prefera sa renunte la ele
    // pt a-si continua drumul

    if(ok==0)
        // Cu toate acestea, nu va renunta niciodata la toate itemurile de tip robin si nici la toate de tip batman
    {
        // ATENTIE!!! Senzorii sunt mai periculosi decat capcanele, iau 2 vieti
        if(getIT(2)>1)
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
            if(ok==1)
            {
                setIT(2,-1);
                H.matrix[row][col]='?';             // Semnul specific pt senzor evitat
            }
        }
    }


    if(ok==0)   //Nu putem sa ne mutam pe orizontala (alta coloana) si nici nu vrem sa revenim la pozitia anterioara
    {
        //Facem un compromis si alegem sa trecem prin capcana, daca exista
        //Evitam itemurile 3 si senzorii pe cat de mult putem

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
            if(getIT(1)>0 && getIT(2)>0) H.matrix[row][col]='!';
            else if(getIT(1)>1)
            {
                setIT(1,-1);           //Are itemuri de tip batman, deci poate distruge capcanele
                H.matrix[row][col]='!';  //Semn specific pt capcana distrusa
            }
            else
            {
                setLife(-1);
                H.matrix[row][col]='@';  //Semn specific pt capcana declansata (seamana cu o explozie)
            }
        }
    }

    if(ok==0)          // mergem doar pe doua directii; daca tot pierd itemuri, macar sa avansez
    {
        if(getIT(1)>0 && getIT(2)>0)
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
        }
    }

    if(ok==0)
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
            setLife(-2);
            H.matrix[row][col]='*';
        }                                         //Semn specific pt senzor alertat
    }

    if(ok==0)                                                            //Ultima solutie ramasa: itemul de tip joker (sau casuta deja vizitata???)
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
    if(H.matrix[row][col]=='_') H.matrix[row][col]='R';
    if(isBlocked(row,col,H)==true) setLife(-10);
    setPos(row,col);
}


void batman::EffectItem(const int x, const int y, harta &H)
{
    char *message =new char[1000];
    message[0]='\0';
    if(H.matrix[x][y]=='2')
    {
        strcpy(message, "You found a robin-item which will aid Batman in his quest!\n");
        if(getIT(3)==1) strcat(message,"You can't pick it up though, because you have a joker-item");
        else
        {
            setIT(2,1);
            if(getIT(2)>0 && getIT(1)>0)
            {
                int ok=0;
                while(getIT(1)>1)
                {
                    setLife(1);
                    setIT(1,-1);
                    ok=1;
                }
                if(ok==1) strcat(message, "You have converted all but one batman-item into bonus lives and gained immunity to all traps.\n");
                else strcat(message, "You gained immunity to all traps.\n");
            }
            H.matrix[x][y]='R';
        }
    }
    else if(H.matrix[x][y]=='3')
    {
        strcpy(message, "Oh no, you found a joker-item! In order to save yourself, exchange a robin and batman item.\n");
        if(getIT(1)>0 && getIT(2)>0)
        {
            setIT(1,-1);
            setIT(2,-1);
            strcat(message,"You got lucky and managed to get rid of the joker-item!\n");
        }
        else
        {
            setIT(3,1);
            setIT(1,0);
            setIT(2,0);
            strcat(message,"The joker-item stuck with you and canceled all of your active boosts.\n");
        }
    }
    else if(H.matrix[x][y]=='1')
    {
        strcpy(message, "You found a batman-item!\n");
        if(getIT(3)>=1) strcat(message, "You can't pick it up though, because you have a joker-item");
        else
        {
            setIT(1,1);
            strcat(message, "You will now be able to destroy all bombs.\n");
            H.matrix[x][y]='R';
        }
    }
    cout<<message;
    delete[] message;
}


/*batman::~batman()
{
    //destructor
}
*/

