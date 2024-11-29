// #include "Simulation.h"
#include <iostream>
#include "../include/Settlement.h"      //added to check settlement class
#include "../include/Facility.h"        //added to check Facility class
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

    //Settlement test
    Settlement s("testName", SettlementType::METROPOLIS);
    cout << s.toString();
    return 0;

    //Facility test
    Facility f("Facility A", "KfarSPL", FacilityCategory::LIFE_QUALITY, 5, 90, 75, 85);    //constructor
    cout << "Facility details (initial):\n" << f.toString();    //toString

    f.setStatus(FacilityStatus::OPERATIONAL);
    f.step();
    f.step();
    f.step();
    f.step();
    f.step();

    cout << "Facility details (after updates):\n" << f.toString();

    cout << "Settlement Name: " << f.getSettlementName();
    cout << "Time Left: " << f.getTimeLeft();
    cout << "Status: " << (f.getStatus() == FacilityStatus::OPERATIONAL ? "Operational" : "Under Construction");
}