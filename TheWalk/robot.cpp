#include "robot.h"
#include "harta.h"
#include <cstring>

int robot::vieti=4;
int robot::countItems1=0;
int robot::countItems2=0;
int robot::countItems3=0;


pair<int, int> robot::getPos() const
{
    return make_pair(row,col);
}

void robot::setPos(int a, int b)
{
    row=a;
    col=b;
}

int robot::getIT(int type) const
{
    if(type==1) return countItems1;
    else if(type==2) return countItems2;
    else if(type==3) return countItems3;
}

void robot::setIT(int type, int m)
{
    if(type==1)
    {
        if(m==1) countItems1++;
        else if(m==-1) countItems1--;
        else countItems1=0;
    }
    else if(type==2)
    {
        if(m==1) countItems2++;
        else if(m==-1) countItems2--;
        else countItems2=0;
    }
    else if(type==3)
    {
        if(m==1) countItems3++;
        else if(m==-1) countItems3--;
        else countItems3=0;
    }
}

void robot::setViz(int nr)
{
    if(nr==1) viz++;
    else viz--;
}

void robot::setLife(int nr)
{
    if(nr>0)
    {
        for(int i=1;i<=nr;i++) vieti++;
    }
    else
    {
        nr=-nr;
        for(int i=1;i<=nr;i++) vieti--;
    }
}

void robot::stats()
{
    cout<<"You have "<<vieti<<" lives left"<<endl;
    cout<<"You have "<<viz<<" points of visibility"<<endl;
    cout<<"You gathered "<<countItems1<< " batman items"<<endl;
    cout<<"You gathered "<<countItems2<< " robin items"<<endl;
    cout<<"You gathered "<<countItems3<< " joker items"<<endl;
}


bool correct(const char aux[], const char c)
{
    if(strchr(aux,c)!=NULL) return true;
    return false;
}

bool robot::isBlocked(const int row, const int col, harta& H) const
{
    const char obs[]="R@?!*S";
    if(row==0)
    {
        if(correct(obs,H.getCell(row,col-1))==true && correct(obs,H.getCell(row+1,col-1))==true &&
           correct(obs,H.getCell(row+1,col))==true)
           {
               if(col==H.getDim().second-1) return true;
               if(col<H.getDim().second-1)
               {
                   if(correct(obs,H.getCell(row+1,col+1))==true && correct(obs,H.getCell(row,col+1))==true)
                    return true;
               }
           }
    }
    else if(col==0)
    {
        if(correct(obs,H.getCell(row-1,col))==true && correct(obs,H.getCell(row-1,col+1))==true &&
           correct(obs,H.getCell(row,col+1))==true)
           {
               if(row==H.getDim().first-1) return true;
               if(row<H.getDim().first-1)
               {
                   if(correct(obs,H.getCell(row+1,col+1))==true && correct(obs,H.getCell(row+1,col))==true)
                    return true;
               }
           }
    }
    else if(row==H.getDim().first-1)
    {
        if(correct(obs,H.getCell(row,col-1))==true && correct(obs,H.getCell(row-1,col-1))==true &&
           correct(obs,H.getCell(row-1,col))==true)
           {
               if(col==H.getDim().second-1) return true;
               if(col<H.getDim().second-1)
               {
                   if(correct(obs,H.getCell(row-1,col+1))==true && correct(obs,H.getCell(row,col+1))==true)
                    return true;
               }
           }

    }
    else if(col==H.getDim().second-1)
    {
        if(correct(obs,H.getCell(row-1,col))==true && correct(obs,H.getCell(row-1,col-1))==true &&
           correct(obs,H.getCell(row,col-1))==true && correct(obs,H.getCell(row+1,col-1))==true &&
           correct(obs,H.getCell(row+1,col))==true)
            return true;
    }
    else
    {
        if(correct(obs,H.getCell(row,col-1))==true && correct(obs,H.getCell(row+1,col-1))==true &&
           correct(obs,H.getCell(row+1,col))==true && correct(obs,H.getCell(row+1,col+1))==true &&
           correct(obs,H.getCell(row,col+1))==true && correct(obs,H.getCell(row-1,col))==true &&
           correct(obs,H.getCell(row-1,col+1))==true && correct(obs,H.getCell(row-1,col-1))==true)
            return true;
    }
    return false;
}


/*robot::~robot() {
    // destructor
}*/
