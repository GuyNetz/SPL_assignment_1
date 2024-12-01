#include "../include/Simulation.h"
#include <string> 
#include <sstream>


Simulation::Simulation(const string &configFilePath):
planCounter(0),
isRunning(false),
actionsLog(),
plans(),
settlements(),
facilitiesOptions()
{};



///give the plan an id based on the counter and advance the counter.
void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy)
{
    
    plans.push_back(Plan(planCounter,settlement,selectionPolicy,facilitiesOptions));
    planCounter++;
    
}
// checks if settlement exist. if not adds it.
bool Simulation::addSettlement(Settlement *settlement){
    if (!isSettlementExists)
    {
       settlements.push_back(settlement);
    }
}


bool Simulation::isSettlementExists(const string &settlementName){
    for (size_t i = 0; i < settlements.size(); ++i) {
        if(settlements[i]->getName()==settlementName)
        return true;
    }
    return false ;//returns false if settlement doesn't exist
}

bool Simulation::addFacility(FacilityType facility){
    facilitiesOptions.push_back(facility);
}

// compare names untill it finds the wanted settlement name. if not exist returns nothing.
Settlement& Simulation::getSettlement(const string &settlementName){
    for (size_t i = 0; i < settlements.size(); ++i) {
        if(settlements[i]->getName()==settlementName)
        return *settlements[i];
    }
}


// check if the id exist. becaus it start from 0 planid== to its place in the array
Plan&Simulation::getPlan(const int planID){
    if(planID<=planCounter){
    return plans[planID];
    }
}