#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <time.h>
#include "harta.h"
#include "robot.h"
#include "batman.h"
#include "robin.h"
#include "joker.h"
using namespace std;
int ok;


int main()
{
    srand(time(NULL));
    harta H;
    int type,ok;
    cin>>H;
    cout<<"Alege Robotul (Batman/Robin/Joker) : ";
    robot *p=NULL;
    while(ok)
    {
        cin>>type;
        ok=0;
        switch (type)
        {

        case 1:
        {
            batman A;
            p=&A;
            break;
        }
        case 2:
        {
            robin A;
            p=&A;
            break;
        }
        case 3:
        {
            joker A;
            p=&A;
            break;
        }
        default:
            cout << "Alegeti o optiune valida (1/2/3) : ";
            ok=1;
        }
    }
    if(p!=NULL) H.Simulate(*p);

    return 0;
}
