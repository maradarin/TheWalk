#include "robot.h"
#include "harta.h"

bool robot::isBlocked(int row, int col, harta& H)
{
    if(row==0)
    {
        if(H.getCell(row,col-1)=='R' && H.getCell(row+1,col-1)=='R' && H.getCell(row+1,col)=='R' && H.getCell(row+1,col+1)=='R' && H.getCell(row,col+1)=='R')
            return true;
    }
    else if(col==0)
    {
        if(H.getCell(row-1,col)=='R' && H.getCell(row-1,col+1)=='R' && H.getCell(row,col+1)=='R' && H.getCell(row+1,col+1)=='R' && H.getCell(row+1,col)=='R')
            return true;
    }
    else
    {
        if(H.getCell(row,col-1)=='R' && H.getCell(row+1,col-1)=='R' && H.getCell(row+1,col)=='R' && H.getCell(row+1,col+1)=='R' && H.getCell(row,col+1)=='R'
           && H.getCell(row-1,col)=='R' && H.getCell(row-1,col+1)=='R' && H.getCell(row-1,col-1)=='R')
            return true;
    }
    return false;
}


/*robot::~robot() {
    // destructor
}*/
