#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

class simulation
{
    int acc(const vector<pair<int,int>>&);
    void reduce(vector<pair<int,int>>&,vector<pair<int,int>>&);
public:
    simulation();
    int my_simulation(vector<int>&);
};

#endif // SIMULATION_H
