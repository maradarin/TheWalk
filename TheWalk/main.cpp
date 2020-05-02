#include <iostream>
#include <algorithm>
#include <time.h>
#include "game.h"
#include "robot.h"
using namespace std;


int main()
{
    int type,ok;
    srand(time(NULL));
    cout<<"Alege Robotul (Batman=1/Robin=2/Joker=3) : ";
    while(ok)
    {
        cin>>type;
        ok=0;
        switch (type)
        {

        case 1:
        {
            game::instance()->setRobot1();
            break;
        }
        case 2:
        {
            game::instance()->setRobot2();
            break;
        }
        case 3:
        {
            game::instance()->setRobot3();
            break;
        }
        default:
            cout << "Alegeti o optiune valida (1/2/3) : ";
            ok=1;
        }
    }

    game::instance()->play();

    return 0;
}
