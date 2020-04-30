#include "robot.h"
#include "harta.h"
#include <cstring>

bool correct(char aux[], char c)
{
    if(strchr(aux,c)!=NULL) return true;
    return false;
}

bool robot::isBlocked(int row, int col, harta& H)
{
    char obs[]="R@?!*3S";
    if(row==0)
    {
        if(correct(obs,H.getCell(row,col-1))==true && correct(obs,H.getCell(row+1,col-1))==true &&
           correct(obs,H.getCell(row+1,col))==true && correct(obs,H.getCell(row+1,col+1))==true &&
           correct(obs,H.getCell(row,col+1))==true)
            return true;
    }
    else if(col==0)
    {
        if(correct(obs,H.getCell(row-1,col))==true && correct(obs,H.getCell(row-1,col+1))==true &&
           correct(obs,H.getCell(row,col+1))==true && correct(obs,H.getCell(row+1,col+1))==true &&
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
