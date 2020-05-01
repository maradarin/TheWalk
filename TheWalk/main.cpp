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


int main()
{
    srand(time(NULL));
    harta *H;
    int type,ok,stop=0,n,m;
    cout<<"Introduceti latimea hartii: ";
    while(stop==0)
    {
        cin>>n;
        try
        {
            if(n<15) throw n;
            else stop=1;
        }
        catch(...)
        {
            cout<<"\nLatimea trebuie sa fie minim 15: ";
        }
    }
    stop=0;
    cout<<"\nIntroduceti lungimea hartii: ";
    while(stop==0)
    {
        cin>>m;
        try
        {
            if(m<15) throw m;
            else stop=1;
        }
        catch(...)
        {
            cout<<"\nLungimea trebuie sa fie minim 15: ";
        }
    }
    cout<<endl;
    H=new harta(n,m);
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
            p=new batman();
            break;
        }
        case 2:
        {
            p=new robin();
            break;
        }
        case 3:
        {
            p=new joker();
            break;
        }
        default:
            cout << "Alegeti o optiune valida (1/2/3) : ";
            ok=1;
        }
    }
    if(p!=NULL) H->Simulate(*p);
    delete H;
    delete p;
    return 0;
}
