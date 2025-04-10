#include "QuadTree.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

ifstream f("input1.in");
ofstream g("output1.out");

int main()
{
    int n, x1, x2, y1, y2, x, y;
    int energyLevel;
    char name[50];

    f >> n;
    f >> x1 >> y1 >> x2 >> y2;
    f >> x >> y >> name >> energyLevel;
    Node galaxy(Point(x, y), name, energyLevel);
    QuadTree* universe = new QuadTree(&galaxy, Point(x1, y1), Point(x2, y2));

    for (int i = 0; i < n - 1; i++)
    {
        f >> x >> y >> name >> energyLevel;
        Node* newGalaxy = new Node(Point(x, y), name, energyLevel);
        universe->insert(newGalaxy);
    }

    int crystals = 0;
    universe->inOrder(0);
    char ready[10];
    cout << "Are we ready to start the exploration?\n";
    cin >> ready;
    system("CLS");
    universe->tour(crystals);

    cout << "\nWe have reached the end of our galactic journey!\n";
    cout << "Total energy crystals collected: " << crystals << " pcs\n";
    g << "Total energy crystals collected: " << crystals << " pcs\n";

    if (crystals <= sqrt(n))
    {
        cout << "Alex's fate: Lost in the cosmos \n";
        g << "Alex's fate: Lost in the cosmos \n";
    }
    else
    {
        cout << "Alex's fate: Master of the Universe\n";
        g << "Alex's fate: Master of the Universe\n";
    }

    f.close();
    g.close();

    delete universe;

    return 0;
}
