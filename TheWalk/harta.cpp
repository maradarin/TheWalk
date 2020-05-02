#include "harta.h"
#include <iostream>
#include "robot.h"
#include <algorithm>
#include <vector>
#include <queue>
#define breakline() cout << "_________________________________________________________________________\n"
using namespace std;

int harta::numberRound = 0;

harta::harta(int a = 0, int b = 0)
    : n(a)
    , m(b)
    , S(new strategy(a, b))
{
    matrix = new char*[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new char[m];

    int ok = 0;
    pair<int, int> aux(0, 0);
    while (ok == 0) {
        aux.first = rand() % n;
        aux.second = rand() % m;
        if (aux.first != 0 && aux.second != 0) //Generare random pt pozitia de final
        //trebuie sa fie diferita de pozitia de start
        {
            ok = 1;
            break;
        }
    }
    finish = make_pair(aux.first, aux.second);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = '_';
    numberItems = 2 * n;
    numberBombs = m + n;
    numberSensors = m;
    matrix[0][0] = 'S';
    matrix[finish.first][finish.second] = 'F';
    for (int i = 1; i <= numberBombs; i++) //Generare aleatoare a bombelor
    {
        int x = 0, y = 0, ok1 = 0;
        while (ok1 == 0) {
            x = rand() % n;
            y = rand() % m;
            if (matrix[x][y] == '_' && !(x == 1 && y == 0)) //Evit pozitia pe care s-ar realiza prima mutare
            //Pt a nu bloca robotul de la inceput
            {
                ok1 = 1;
                break;
            }
        }
        matrix[x][y] = 'X';
    }
    for (int i = 1; i <= numberSensors; i++) //Generare aleatoare a senzorilor
    {
        int x = 0, y = 0, ok1 = 0;
        while (ok1 == 0) {
            x = rand() % n;
            y = rand() % m;
            if (matrix[x][y] == '_' && !(x == 1 && y == 0)) //Evit pozitia pe care s-ar realiza prima mutare
            //Pt a nu bloca robotul de la inceput
            {
                ok1 = 1;
                break;
            }
        }
        matrix[x][y] = 'Z';
    }
    for (int i = 1; i <= numberItems; i++) //Generare aleatoare a itemurilor
    {
        int x = 0, y = 0, ok1 = 0, z = 0;
        while (ok1 == 0) {
            x = rand() % n;
            y = rand() % m;
            z = rand() % 3 + 1; //Itemuri de 3 tipuri (reprezentate cu 1,2,3 pe harta)
            if (matrix[x][y] == '_') {
                if ((z == 3 && !(x == 1 && y == 0)) || z == 1 || z == 2) //Pt itemul 3 evit prima pozitie pe care s-ar realiza mutarea
                {
                    ok1 = 1;
                    break;
                }
            }
        }
        matrix[x][y] = '0' + z; // Fiecare item corespunde unui tip de robot
    }
}

harta::~harta()
{
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;

    n = 0;
    m = 0;
    numberItems = 0;
    numberBombs = 0;
    numberSensors = 0;
    numberRound = 0;
    finish = make_pair(0, 0);
    delete A;
    delete S;
}

char harta::getCell(const int row, const int col) const
{
    return matrix[row][col];
}

pair<int, int> harta::getDim() const
{
    return make_pair(n, m);
}

ostream& operator<<(ostream& out, const harta& H)
{
    cout << "\n";
    for (int i = 0; i < H.n; i++) {
        for (int j = 0; j < H.m; j++)
            cout << H.matrix[i][j] << " ";
        cout << "\n";
    }
    return out;
}

void harta::Simulate(robot& A)
{
    char aut;
    cout << "Target point at coordinates: " << finish.first << " " << finish.second << endl;
    cout << "Do you wish to continue the game automatically? Choose (Y/y) for yes or (N/n) for no : ";
    cin >> aut;
    while (aut != 'Y' && aut != 'y' && aut != 'n' && aut != 'N') {
        cout << "\nInvalid option. Try again : ";
        cin >> aut;
    }
    if (aut == 'Y' || aut == 'y') {
        int ok = 0;
        while (!(A.getPos().first == finish.first && A.getPos().second == finish.second) && A.getVieti() > 0 && ok == 0) {
            cout << "Round: " << numberRound << " coordinates " << A.getPos().first << " " << A.getPos().second << endl;
            cout << "STATS: " << endl;
            A.stats();
            cout << *this << endl;
            A.Move(*this, *S); //mutam robotul pe harta
            breakline();
            numberRound++;
            if (A.getVieti() <= 0)
                ok = 1;
        }
        if (A.getVieti() == -100)
            cout << "You lost yourself in the labyrinth and starved to death" << endl;
        else {
            if (ok == 0) {
                cout << "You won at round: " << numberRound << " coordinates " << A.getPos().first << " " << A.getPos().second << endl;
            }
            else {
                cout << "You died at round: " << numberRound << " coordinates " << A.getPos().first << " " << A.getPos().second << endl;
            }
            A.stats();
            cout << *this << endl;
            breakline();
        }
    }
    else if (aut == 'N' || aut == 'n') {
        int ok = 0;
        while (!(A.getPos().first == finish.first && A.getPos().second == finish.second) && A.getVieti() > 0 && ok == 0) {
            cout << "Round: " << numberRound << " coordinates " << A.getPos().first << " " << A.getPos().second << endl;
            cout << "STATS: " << endl;
            A.stats();
            cout << *this << endl;
            A.Move(*this, *S); //mutam robotul pe harta
            breakline();
            numberRound++;
            if (A.getVieti() < 0) {
                cout << "You died";
                ok = 1;
            }
            if (ok == 0) {
                char ans;
                cout << "\nDo you wish to continue the game? Choose (Y/y) for yes or (N/n) for no : ";
                cin >> ans;
                while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
                    cout << "\nInvalid option. Try again : ";
                    cin >> ans;
                }
                if (ans == 'n' || ans == 'N') {
                    cout << "\nGame terminated";
                    ok = 1;
                    break;
                }
            }
        }
        if (A.getVieti() == -100)
            cout << "You lost yourself in the labyrinth and starved to death" << endl;
        else if (ok == 0) {
            cout << "You won at round: " << numberRound << " coordinates " << A.getPos().first << " " << A.getPos().second << endl;
            A.stats();
            cout << *this;
        }
    }
}
