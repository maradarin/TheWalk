#include "robot.h"
#include "harta.h"
#include <cstring>

int robot::vieti=4;
int robot::countItems1=0;
int robot::countItems2=0;
int robot::countItems3=0;


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
