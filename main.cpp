#include <QCoreApplication>
#include "simulation.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    simulation mys;
    vector<int> mv{2,2,2,2,2,2,5,6,9,4,12,8,8,7,7,7,7,9,8,7,7,7,7,8,8,-5,-6,-9,-8};

    cout <<  mys.my_simulation(mv) << '\n';

    return a.exec();
}
