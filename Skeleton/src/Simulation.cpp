#include "../include/Simulation.h"
#include "../include/Auxiliary.h"
#include <string> 
#include <sstream>
#include <fstream>


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
};

void Simulation::start(){
    isRunning = true;
}

///give the plan an id based on the counter and advance the counter.
void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy)
{  
    plans.push_back(Plan(planCounter,settlement,selectionPolicy,facilitiesOptions));
    planCounter++; 
}

void Simulation::addAction(BaseAction *action){
    
}

// checks if settlement exist. if not adds it. return true if added
bool Simulation::addSettlement(Settlement *settlement){
    if (!isSettlementExists(settlement->getName())){
       settlements.push_back(settlement);
       return true;
    }
    return false;
}

bool Simulation::addFacility(FacilityType facility){
    for (size_t i = 0; i < facilitiesOptions.size(); ++i) {
        if(facilitiesOptions[i].getName()==facility.getName()){
            return false;
        }
    }
    facilitiesOptions.push_back(facility);
    return true;

}

bool Simulation::isSettlementExists(const string &settlementName){
    for (size_t i = 0; i < settlements.size(); ++i) {
        if(settlements[i]->getName()==settlementName){
            return true;
        } 
    }
    return false ;//returns false if settlement doesn't exist
}

// compare names untill it finds the wanted settlement name. if not exist returns nothing.
Settlement& Simulation::getSettlement(const string &settlementName){
    for (size_t i = 0; i < settlements.size(); ++i) {
        if(settlements[i]->getName()==settlementName){
            return *settlements[i];
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