#include <iostream>
#include "../include/Settlement.h"      //added to check settlement class
#include "../include/Facility.h"        //added to check Facility class
#include "../include/SelectionPolicy.h" //added to check SelectionPolicy class
#include "../include/Plan.h"            //added to check Plan class
#include "../include/Simulation.h"      //added to check Simulation class
using namespace std;
Simulation * backup;


int main(int argc, char** argv){
    
    if(argc!=2){
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    Simulation simulation(configurationFile);
    simulation.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
}