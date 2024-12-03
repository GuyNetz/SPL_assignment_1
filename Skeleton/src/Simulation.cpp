#include "../include/Simulation.h"
#include "../include/Auxiliary.h"
#include <string> 
#include <sstream>
#include <fstream>
#include <iostream>



//constructor
Simulation::Simulation(const string &configFilePath):
isRunning(false),
planCounter(1),
actionsLog(),
plans(),
settlements(),
facilitiesOptions() {
    std::ifstream configFile(configFilePath);
    string line;

    if(!configFile.is_open()){
        std::cerr << "Error: cant open config file: " << configFilePath << std::endl;
    }else{
        while(std::getline(configFile, line)){
            vector<string> parsedAr = Auxiliary::parseArguments(line);
            if(parsedAr.empty()){
                continue;
            }
        }
    }  
}

void Simulation::start(){
    isRunning = true;
}

///give the plan an id based on the counter and advance the counter.
void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy)
{  
    plans.push_back(Plan(planCounter,settlement,selectionPolicy,facilitiesOptions));
    planCounter++; 
}

void Simulation::addAction(BaseAction *action) {
    actionsLog.push_back(action);
}


// checks if settlement exist. if not adds it. return true if added
bool Simulation::addSettlement(Settlement *settlement){
    if (!isSettlementExists(settlement->getName())){
       settlements.push_back(settlement);
       return true;
    }
    return false;
}

bool Simulation::addFacility(FacilityType facility) {
    for (const FacilityType &existing : facilitiesOptions) {
        if (existing.getName() == facility.getName()) {
            return false;
        }
    }
    facilitiesOptions.push_back(facility);
    return true;
}

bool Simulation::isSettlementExists(const string &settlementName){
    for (Settlement *settlement : settlements) {
        if (settlement->getName() == settlementName) {
            return true;
        }
    }
    return false;
}

// compare names untill it finds the wanted settlement name. if not exist returns nothing.
Settlement &Simulation::getSettlement(const string &settlementName) {
    for (Settlement *settlement : settlements) {
        if (settlement->getName() == settlementName) {
            return *settlement;
        }
    }
    return *settlements[0]; //shouldnt get here
}

// check if the id exist. becaus it start from 0 planid== to its place in the array
Plan&Simulation::getPlan(const int planID){
    if(planID <= planCounter){
        return plans[planID - 1];
    }
    return plans[0];    //shouldnt get here
}

void Simulation::step() {
    for (Plan &plan : plans) {
        plan.step();
    }
}

void Simulation::close() {
    isRunning = false;

    // Print results
    for (const Plan &plan : plans) {
        std::cout << plan.toString() << std::endl;
    }

    // Free memory
    for (Settlement *settlement : settlements) {
        delete settlement;
    }
    settlements.clear();

    for (BaseAction *action : actionsLog) {
        delete action;
    }
    actionsLog.clear();
}

void Simulation::open() {
    if (backup == nullptr) {
        std::cerr << "Error: No backup available to restore." << std::endl;
        return;
    }

    // Restore the backup into the current simulation
    *this = *backup; // Assuming the assignment operator for Simulation is implemented
    std::cout << "Simulation restored from backup." << std::endl;
}

void Simulation::print_action_log(){
    for (size_t i = 0; i < actionsLog.size(); i++)
    {
        std::cout << actionsLog[i]; << std::endl; 
    }
    
}