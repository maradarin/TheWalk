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
    H.trigger(row,col,viz);
    H.check(make_pair(row,col),viz);

    //daca destinatia finala e in raza lui de actiune, atunci robotul o sa se indrepte spre ea
    if (abs(H.finish.first - row) <= viz && abs(H.finish.second - col) <= viz)
    {
        cout<<"finish in perimetru vizibil"<<endl;
        if (H.finish.first < row && row>=1)
        {
            if(H.dist[row-1][col]!=-1)
            {
                cout<<"f1"<<endl;
                row--;
                ok=1;
            }
        }
        else if (H.finish.first > row)
        {
            if(H.dist[row+1][col]!=-1)
            {
                cout<<"f2"<<endl;
                row++;
                ok=1;
            }
        }
        else if (H.finish.second < col && col>=1)
        {
            if(H.dist[row][col-1]!=-1)
            {
                cout<<"f3"<<endl;
                col--;
                ok=1;
            }
        }
        else if (H.finish.second > col)
        {
            if(H.dist[row][col+1]!=-1)
            {
                cout<<"f4"<<endl;
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
               (countItems1>0 && countItems2>0) || (countItems1>0 && H.matrix[0][col+1]=='X'))
            {
                cout<<"urm col"<<endl;
                row=0;
                col++;
                ok=1;
                if(countItems1>0 && countItems2>0 && H.matrix[row][col]=='Z') H.matrix[row][col]='?';
                if(countItems1>0 && H.matrix[row][col]=='X') H.matrix[row][col]='!';
            }
        }
        else if(col==H.m-1)
        {
            if((H.matrix[row+1][0]=='_' || H.matrix[row+1][0]=='1' || H.matrix[row+1][0]=='2') ||
               (countItems1>0 && countItems2>0) || (countItems1>0 && H.matrix[row+1][0]=='X'))
            {
                cout<<"urm linie"<<endl;
                row++;
                col=0;
                ok=1;
                if(countItems1>0 && countItems2>0 && H.matrix[row][col]=='Z') H.matrix[row][col]='?';
                if(countItems1>0 && H.matrix[row][col]=='X') H.matrix[row][col]='!';
            }
        }
        else
        {
            if(H.dist[row+1][col]!=-1)
            {
                cout<<"liber1"<<endl;
                row++;
                ok=1;
            }
            else if(H.dist[row][col+1]!=-1)
            {
                cout<<"liber2"<<endl;
                col++;
                ok=1;
            }
            else if(H.dist[row][col-1]!=-1 && col>=1)
            {
                cout<<"liber3"<<endl;
                col--;
                ok=1;
            }
            else if(H.dist[row-1][col]!=-1 && row>=1)
            {
                cout<<"liber4"<<endl;
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
        if(countItems2>1)
        {
            if(H.matrix[row+1][col]=='Z')
            {
                cout<<"z evitat1"<<endl;
                row++;
                ok=1;
            }
            else if(H.matrix[row][col+1]=='Z')
            {
                cout<<"z evitat2"<<endl;
                col++;
                ok=1;
            }
            if(ok==1)
            {
                countItems2--;
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
            cout<<"x1"<<endl;
            row++;
            ok=1;
        }
        else if(H.matrix[row][col+1]=='X')
        {
            cout<<"x2"<<endl;
            col++;
            ok=1;
        }
        else if(H.matrix[row][col-1]=='X' && col>=1)
        {
            cout<<"x3"<<endl;
            col--;
            ok=1;
        }
        else if(H.matrix[row-1][col]=='X' && row>=1)
        {
            cout<<"x4"<<endl;
            row--;
            ok=1;
        }

        if(ok==1)
        {
            if(countItems1>0 && countItems2>0) H.matrix[row][col]='!';
            else if(countItems1>1)
            {
                countItems1--;           //Are itemuri de tip batman, deci poate distruge capcanele
                H.matrix[row][col]='!';  //Semn specific pt capcana distrusa
            }
            else
            {
                vieti--;
                H.matrix[row][col]='@';  //Semn specific pt capcana declansata (seamana cu o explozie)
            }
        }
    }

    if(ok==0)          // mergem doar pe doua directii; daca tot pierd itemuri, macar sa avansez
    {
        if(countItems1>0 && countItems2>0)
        {
            if(H.matrix[row+1][col]=='3')
            {
                cout<<"3 evitat 1"<<endl;
                row++;
                ok=1;
            }
            else if(H.matrix[row][col+1]=='3')
            {
                cout<<"3 evitat 2"<<endl;
                col++;
                ok=1;
            }
        }
    }

    if(ok==0)
    {
        if(H.matrix[row+1][col]=='Z')
        {
            cout<<"z1"<<endl;
            row++;
            ok=1;
        }
        else if(H.matrix[row][col+1]=='Z')
        {
            cout<<"z2"<<endl;
            col++;
            ok=1;
        }
        else if(H.matrix[row][col-1]=='Z' && col>=1)
        {
            cout<<"z3"<<endl;
            col--;
            ok=1;
        }
        else if(H.matrix[row-1][col]=='Z' && row>=1)
        {
            cout<<"z4"<<endl;
            row--;
            ok=1;
        }

        if(ok==1)
        {
            vieti-=2;
            H.matrix[row][col]='*';
        }                                         //Semn specific pt senzor alertat
    }

    if(ok==0)                                                            //Ultima solutie ramasa: itemul de tip joker (sau casuta deja vizitata???)
    {
        if(H.matrix[row+1][col]=='3')
        {
            cout<<"3.1"<<endl;
            row++;
            ok=1;
        }
        else if(H.matrix[row][col+1]=='3')
        {
            cout<<"3.2"<<endl;
            col++;
            ok=1;
        }
        else if(H.matrix[row][col-1]=='3' && col>=1)
        {
            cout<<"3.3"<<endl;
            col--;
            ok=1;
        }
        else if(H.matrix[row-1][col]=='3' && row>=1)
        {
            cout<<"3.4"<<endl;
            row--;
            ok=1;
        }
    }
    if(H.matrix[row][col]=='_') H.matrix[row][col]='R';
    cout<<"am ales "<<row<< " "<<col<<endl;
    EffectItem(row,col,H);
    if(isBlocked(row,col,H)==true) vieti=-100;
}


void batman::EffectItem(int x, int y, harta &H)
{
    char *message =new char[1000];
    message[0]='\0';
    if(H.matrix[x][y]=='2')
    {
        strcpy(message, "You found a robin-item which will aid Batman in his quest!\n");
        if(countItems3==1) strcat(message,"You can't pick it up though, because you have a joker-item");
        else
        {
            countItems2++;
            if(countItems2>0 && countItems1>0)
            {
                int ok=0;
                while(countItems1>1)
                {
                    vieti++;
                    countItems1--;
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
        if(countItems1>0 && countItems2>0)
        {
            countItems1--;
            countItems2--;
            strcat(message,"You got lucky and managed to get rid of the joker-item!\n");
        }
        else
        {
            countItems3=1;
            countItems1=0;
            countItems2=0;
            strcat(message,"The joker-item stuck with you and canceled all of your active boosts.\n");
        }
    }
    else if(H.matrix[x][y]=='1')
    {
        strcpy(message, "You found a batman-item!\n");
        if(countItems3==1) strcat(message, "You can't pick it up though, because you have a joker-item");
        else
        {
            countItems1++;
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

