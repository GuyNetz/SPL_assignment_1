#include "../include/Simulation.h"
#include "../include/Auxiliary.h"
#include "../include/Action.h"
#include "../include/SelectionPolicy.h"
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
    //open config file
    std::ifstream configFile(configFilePath);

    //check if config file is opened properly
    if (!configFile.is_open()) {
        throw std::runtime_error("Error: Cannot open config file: " + configFilePath);
    }

    //read config file
    string line;
    while (std::getline(configFile, line)) {
        vector<string> parsedAr = Auxiliary::parseArguments(line);
        if (parsedAr.empty()) { // Skip empty lines
            continue; 
        }

        const string &command = parsedAr[0];    //saving the first word(command)

        //adding new settlements
        if (command == "settlement") {
            string name = parsedAr[1];
            int type = std::stoi(parsedAr[2]);
            addSettlement(new Settlement(name, static_cast<SettlementType>(type)));

        //adding new facilities
        } else if (command == "facility") {
            string name = parsedAr[1];
            int category = std::stoi(parsedAr[2]);
            int price = std::stoi(parsedAr[3]);
            int lifeQImpact = std::stoi(parsedAr[4]);
            int ecoImpact = std::stoi(parsedAr[5]);
            int envImpact = std::stoi(parsedAr[6]);
            addFacility(FacilityType(name, static_cast<FacilityCategory>(category), price, lifeQImpact, ecoImpact, envImpact));

        //adding new plans
        } else if (command == "plan") {
            string settlementName = parsedAr[1];
            string policyType = parsedAr[2];

            Settlement &settlement = getSettlement(settlementName);

            SelectionPolicy *policy = nullptr;
            if (policyType == "nve") {
                policy = new NaiveSelection();
            } else if (policyType == "bal") {
                policy = new BalancedSelection(0,0,0);
            } else if (policyType == "eco") {
                policy = new EconomySelection();
            } else if (policyType == "env") {
                policy = new SustainabilitySelection();
            }

            addPlan(settlement, policy);
        }
    }
}

void Simulation::start(){
    isRunning = true;
}

//adds a new plan to plans vector using the ID counter
void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){  
    plans.push_back(Plan(planCounter,settlement,selectionPolicy,facilitiesOptions));
    planCounter++; 
}

//adds a new action to actionsLog vector
void Simulation::addAction(BaseAction *action) {
    actionsLog.push_back(action);
}


//checks if settlement exist. if not adds it. return true if added
bool Simulation::addSettlement(Settlement *settlement){
    if (!isSettlementExists(settlement->getName())){
       settlements.push_back(settlement);
       return true;
    }
    return false;
}

//adds a new facility to facilityOptions vector
bool Simulation::addFacility(FacilityType facility) {
    for (const FacilityType &existing : facilitiesOptions) {
        if (existing.getName() == facility.getName()) {
            return false;
        }
    }
    facilitiesOptions.push_back(facility);
    return true;
}

//checks if there's another settlement with the same name. helper fuction
bool Simulation::isSettlementExists(const string &settlementName){
    for (Settlement *settlement : settlements) {
        if (settlement->getName() == settlementName) {
            return true;
        }
    }
    return false;
}

//returns settlement object using a name. if not exist returns nothing.
Settlement &Simulation::getSettlement(const string &settlementName) {
    for (Settlement *settlement : settlements) {
        if (settlement->getName() == settlementName) {
            return *settlement;
        }
    }
    return *settlements[0]; //shouldnt get here
}

// check if the id exist. because it start from 0 planid== to its place in the array
Plan&Simulation::getPlan(const int planID){
    if(planID <= planCounter){
        return plans[planID - 1];
    }
    return plans[0];    //shouldnt get here
}

//advancing all plan by one step
void Simulation::step() {
    for (Plan &plan : plans) {
        plan.step();
    }
}

//ending simulation, printing results and free memory
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
    for (size_t i = 0; i < actionsLog.size(); i++) {
        std::cout << actionsLog[i]->toString() << std::endl;  // Directly use -> on actionsLog[i]
    } 
}