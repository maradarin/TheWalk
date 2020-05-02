#include "game.h"
#include "harta.h"
#include "robot.h"
#include "batman.h"
#include "robin.h"
#include "joker.h"

game* game::route = new game();

game::game() :	pawn(NULL)
{ }

game::~game()
{
    delete pawn;
    delete plan;
}

void game::play()
{
    int stop=0,n,m;
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
    plan=new harta(n,m);
    plan->Simulate(*pawn);

}

void game::setRobot1()
{
    pawn = new batman();
}

void game::setRobot2()
{
    pawn = new robin();
}

void game::setRobot3()
{
    pawn = new joker();
}
