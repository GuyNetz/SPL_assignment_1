// #include "Simulation.h"
#include <iostream>
#include "../include/Settlement.h"      //added to check settlement class
using namespace std;

// Simulation* backup = nullptr;

int main(int argc, char** argv){
    // if(argc!=2){
    //     cout << "usage: simulation <config_path>" << endl;
    //     return 0;
    // }
    // string configurationFile = argv[1];
    // Simulation simulation(configurationFile);
    // simulation.start();
    // if(backup!=nullptr){
    // 	delete backup;
    // 	backup = nullptr;
    // }

    Settlement s("testName", SettlementType::METROPOLIS);
    cout << s.toString();
    return 0;
}