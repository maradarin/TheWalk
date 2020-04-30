
#include "harta.h"
#include <iostream>
#include <new>
#include <cstdlib>
#include "robot.h"
#include <utility>
#include <algorithm>
#include <vector>
#include <queue>
#define breakline() cout<<"_________________________________________________________________________\n"
using namespace std;

int harta::numberRound = 0;

harta::harta()
{
    n=0;
    m=0;
}

harta::~harta()
{
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;

    for (int i = 0; i < n; i++)
        delete[] dist[i];
    delete[] dist;

    n=0;
    m=0;
    numberItems=0;
    numberTraps=0;
    numberSensors=0;
    numberRound=0;
    finish=make_pair(0,0);
    ZCoord.clear();
}

char harta::getCellm(int row, int col)
{
    return matrix[row][col];
}

pair<int,int> harta::getDim()
{
    return make_pair(n,m);
}

istream & operator >> (istream & in, harta &H)
{
    cout<<"Introduceti latimea hartii: ";
    in>>H.n;
    int stop=0;
    while(stop==0)
    {
        if(H.n<15)
        {
            cout<<endl<<"Introduceti o valoare valida: ";
            in>>H.n;
        }
        else stop=1;
    }
    stop=0;
    cout<<endl;
    cout<<"Introduceti lungimea hartii: ";
    in>>H.m;
    while(stop==0)
    {
        if(H.m<15)
        {
            cout<<endl<<"Introduceti o valoare valida: ";
            in>>H.m;
        }
        else stop=1;
    }
    cout<<endl;
    try
    {
        H.matrix = new char*[H.n];
    }
    catch (bad_alloc)
    {
        cout << "Eroare la initializarea matricei";
    }
    for (int i = 0; i < H.n; i++)
    {
        try
        {
            H.matrix[i] = new char[H.m];
        }
        catch (bad_alloc)
        {
            cout << "Eroare la initializarea matricei";
        }
    }
    int ok=0;
    pair<int,int> aux(0,0);
    while(ok==0)
    {
        aux.first=rand()%H.n;
        aux.second=rand()%H.m;
        if(aux.first!=0 && aux.second!=0)                       //Generare random pt pozitia de final; trebuie sa fie diferita de pozitia de start
        {
            ok=1;
            break;
        }
    }
    H.finish=make_pair(aux.first,aux.second);

    for (int i = 0; i < H.n; i++)
        for (int j = 0; j < H.m; j++)
            H.matrix[i][j] = '_';
    H.numberItems=2*H.n;
    H.numberTraps=H.m+H.n;
    H.numberSensors=H.m;
    H.matrix[0][0]='S';
    H.matrix[H.finish.first][H.finish.second]='F';
    for(int i=1; i<=H.numberTraps; i++)                         //Generare aleatoare a capcanelor
    {
        int x=0,y=0,ok1=0;
        while(ok1==0)
        {
            x = rand() % H.n;
            y = rand() % H.m;
            if(H.matrix[x][y]=='_' && !(x==1 && y==0))
            {
                ok1=1;
                break;
            }
        }
        H.matrix[x][y]='X';
    }
    for(int i=1; i<=H.numberSensors; i++)                        //Generare aleatoare a capcanelor
    {
        int x=0,y=0,ok1=0;
        while(ok1==0)
        {
            x = rand() % H.n;
            y = rand() % H.m;
            if(H.matrix[x][y]=='_' && !(x==1 && y==0))
            {
                ok1=1;
                break;
            }
        }
        H.matrix[x][y]='Z';
    }
    for(int i=1; i<=H.numberItems; i++)                         //Generare aleatoare a itemurilor
    {
        int x=0,y=0,ok1=0,z=0;
        while(ok1==0)
        {
            x = rand() % H.n;
            y = rand() % H.m;
            z = rand() % 3 + 1;                                 //Itemuri de 3 tipuri (reprezentate cu 1,2,3 pe harta)
            if(H.matrix[x][y]=='_')
            {
                if(z==3 && !(x==1 && y==0))
                {
                    ok1=1;
                    break;
                }
            }
        }
        H.matrix[x][y]='0'+z;                                   // Fiecare item corespunde unui tip de robot
    }

    H.dist = new int*[H.n];
    for (int i = 0; i < H.n; i++) H.dist[i] = new int[H.m];

    return in;
}

ostream & operator <<(ostream & out,const harta &H)
{
    cout<<"\n";
    for(int i=0; i<H.n; i++)
    {
        for(int j=0; j<H.m; j++)
        //{
            //if(i>=max(0,row-viz) && i<min(n,row+viz+1) && j>=max(0,col-viz) && j<min(m,col+viz+1)) cout<<H.matrix[i][j]<<" ";
            //else cout<<char(178)<<" ";
        //}
        cout<<H.matrix[i][j]<<" ";
        cout<<"\n";
    }
    return out;
}

void harta::Simulate(robot &A)
{
    char aut;
    cout<<"Target point at coordinates: "<<finish.first<<" "<<finish.second<<endl;
    cout<<"Do you wish to continue the game automatically? Choose (Y/y) for yes or (N/n) for no : ";
    cin>>aut;
    while(aut!='Y' && aut!='y' && aut!='n' && aut!='N')
    {
        cout<<"\nInvalid option. Try again : ";
        cin>>aut;
    }
    if(aut=='Y' || aut=='y')
    {
        int ok=0;
        while(!(A.getRow()==finish.first && A.getCol()==finish.second) && A.getVieti()>0 && ok==0)
        {
            cout<<"Round: "<<numberRound<<" coordinates "<<A.getRow()<<" "<<A.getCol()<<endl;
            cout<<"STATS: "<<endl;
            A.stats();
            cout<<*this<<endl;
            A.Move(*this);                                                  //mutam robotul pe harta
            breakline();
            numberRound++;
            if(A.getVieti()<=0) ok=1;
        }
        if(A.getVieti()==-100) cout<<"You lost yourself in the labyrinth and starved to death"<<endl;
        else
        {
            if(ok==0)
            {
                cout<<"You won at round: "<<numberRound<<" coordinates "<<A.getRow()<<" "<<A.getCol()<<endl;
            }
            else
            {
                cout<<"You died at round: "<<numberRound<<" coordinates "<<A.getRow()<<" "<<A.getCol()<<endl;
            }
            A.stats();
            cout<<*this<<endl;
            breakline();
        }

    }
    else if(aut=='N' || aut=='n')
    {
        int ok=0;
        while(!(A.getRow()==finish.first && A.getCol()==finish.second) && A.getVieti()>0 && ok==0)
        {
            cout<<"Round: "<<numberRound<<" coordinates "<<A.getRow()<<" "<<A.getCol()<<endl;
            cout<<"STATS: "<<endl;
            A.stats();
            cout<<*this<<endl;
            A.Move(*this);                                                  //mutam robotul pe harta
            breakline();
            numberRound++;
            if(A.getVieti()<0)
            {
                cout<<"You died";
                ok=1;
            }
            if(ok==0)
            {
                char ans;
                cout<<"\nDo you wish to continue the game? Choose (Y/y) for yes or (N/n) for no : ";
                cin>>ans;
                while(ans!='Y' && ans!='y' && ans!='N' && ans!='n')
                {
                    cout<<"\nInvalid option. Try again : ";
                    cin>>ans;
                }
                if(ans=='n' || ans=='N')
                {
                    cout<<"\nGame terminated";
                    ok=1;
                    break;
                }
            }
        }
        if(ok==0)
        {
            cout<<"You won at round: "<<numberRound<<" coordinates "<<A.getRow()<<" "<<A.getCol()<<endl;
            A.stats();
        }
    }
}

bool harta::isValid(int x, int y, char c)
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

bool harta::findCoord(int a, int b)
{
    pair<int, int> p=make_pair(a,b);
    if(find(ZCoord.begin(), ZCoord.end(), p) != ZCoord.end()) return false;
    return true;
}

void harta::trigger(int row, int col, int viz)
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
                    if (isValid(i + rowNum[k], j + colNum[k], 'Z'))
                    {
                        matrix[i + rowNum[k]][j + colNum[k]] = 'Z';
                        ZCoord.push_back(make_pair(i+rowNum[k],j+colNum[k]));
                    }
            }
}

void harta::check(pair<int,int> curr, int viz)
{
    dist = new int*[n];
    for (int i = 0; i < n; i++)
        dist[i] = new int[m];

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
            if(isValid(xp,yp,'m') && dist[xp][yp] == -1)
            {
                dist[xp][yp] = d+1;
                q.push(make_pair(xp,yp));
            }
        }
    }
}
