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
planCounter(0),
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
             addSettlement(new Settlement(name, static_cast<SettlementType>(type))); // this use simulation's function 
            

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

void Simulation::start() {
    std::cout<<"The simulation has started"<<std::endl;
    open(); // Start the simulation

    std::string command;
    while (isRunning) {
        std::getline(std::cin, command); // Read the user command

        // Parse the command into arguments
        std::vector<std::string> parsedCommand = Auxiliary::parseArguments(command);
        if (parsedCommand.empty()) {
            continue; // Ignore empty commands
            
        }

        const std::string &action = parsedCommand[0];
        BaseAction *actionObject = nullptr;

        if (action == "step") {
            if (parsedCommand.size() == 2) {
                int numOfSteps = std::stoi(parsedCommand[1]);
                actionObject = new SimulateStep(numOfSteps);
            }

        } else if (action == "plan") {
            if (parsedCommand.size() == 3) {
                const std::string &settlementName = parsedCommand[1];
                const std::string &selectionPolicy = parsedCommand[2];
                actionObject = new AddPlan(settlementName, selectionPolicy);
            }

        } else if (action == "log") {
            
            if (parsedCommand.size() == 1) {
                
                actionObject = new PrintActionsLog();
                
            }

        } else if (action == "close") {
            if (parsedCommand.size() == 1) {
                actionObject = new Close();
            }

        } else if (action == "backup") {
            if (parsedCommand.size() == 1) {
                actionObject = new BackupSimulation();
                
            }

        } else if (action == "restore") {
            if (parsedCommand.size() == 1) {
                actionObject = new RestoreSimulation();
                
            }

        } else if (action == "planStatus") {
            if (parsedCommand.size() == 2) {
                int planID = std::stoi(parsedCommand[1]);
                actionObject = new PrintPlanStatus(planID);
                
            }

        } else if (action == "changePolicy") {
            if (parsedCommand.size() == 3) {
                int planID = std::stoi(parsedCommand[1]);
                const std::string &newPolicy = parsedCommand[2];
                actionObject = new ChangePlanPolicy(planID, newPolicy);
                
            }
        } else if (action=="facility"){
            if(parsedCommand.size() == 7){
             string name = parsedCommand[1];
              int category = std::stoi(parsedCommand[2]);
              int price = std::stoi(parsedCommand[3]);
              int lifeQImpact = std::stoi(parsedCommand[4]);
              int ecoImpact = std::stoi(parsedCommand[5]);
              int envImpact = std::stoi(parsedCommand[6]);
              actionObject = new AddFacility(name,static_cast<FacilityCategory>(category),price,lifeQImpact,ecoImpact,envImpact);
             

            }

         } else if(action=="settlement"){
            if(parsedCommand.size() == 3){
                string name = parsedCommand[1];
                int type = std::stoi(parsedCommand[2]);
                actionObject = new AddSettlement(name,static_cast<SettlementType>(type));
                
            }
         }
        

        if (actionObject != nullptr) {
            actionObject->act(*this); // Execute the action
            delete actionObject;     // Free the memory for the action
            actionObject=nullptr;
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }

        
    }
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

bool Simulation::isFacilityExists(const string &facilityName){
    for (FacilityType facility : facilitiesOptions) {
        if (facility.getName() == facilityName) {
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
    if(isPlanExists(planID)){
        return plans[planID];
    }
    return plans[0];    //shouldnt get here
}
bool Simulation::isPlanExists(const int planID){
    if(0<=planID && planID<=planCounter-1) {
        return true;
    }
    else{ return false;}
    
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
        std::cout << "PlanID: " + std::to_string(plan.getPlanId()) + "\n";
        std::cout << "SettlementName: " + plan.getSettlementName() + "\n";
        std::cout << "LifeQuality_Score: " + std::to_string(plan.getlifeQualityScore()) + "\n";
        std::cout << "Economy_Score: " + std::to_string(plan.getEconomyScore()) + "\n";
        std::cout << "Environment_Score: " + std::to_string(plan.getEnvironmentScore()) + "\n";
    }

    // Free memory
    for (Settlement *settlement : settlements) {
        delete settlement;
    }
    settlements.clear();

    for (BaseAction *action : actionsLog) {
        delete action;
        action=nullptr;
    }
    actionsLog.clear();
}


void Simulation::open() {
    isRunning = true;
}


//prints actions log
void Simulation::print_action_log(){
    for (size_t i = 0; i < actionsLog.size(); i++) {
        std::cout << actionsLog[i]->toString() << std::endl; 
        

    } 
}
// rule of 5

Simulation::~Simulation() {
    for (auto settlement : settlements) {
        delete settlement;  
     }
    settlements.clear();

    for (auto action : actionsLog) {
        action=nullptr;
        delete action;  
     }

     actionsLog.clear();

    //  for (size_t i = 0; i < plans.size(); i++)
    //  {
    //    plans[i].~Plan();
    //  }
     
   }
    // actionsLog.clear();



Simulation::Simulation(const Simulation& other)
    : isRunning(other.isRunning),
      planCounter(other.planCounter),
      actionsLog(other.actionsLog),
      plans(),
      settlements(),
      facilitiesOptions(other.facilitiesOptions) {

    for (auto settlement : other.settlements) {
        settlements.push_back(new Settlement(*settlement)); 
    }
    plans.clear();
    for (auto& plan : other.plans) {
        plans.push_back( Plan(plan));
    }
}

Simulation& Simulation:: operator=(const Simulation& other) {
    if (this == &other) {
        return *this;  
    }

   
    for (auto settlement : settlements) {
        delete settlement;
    }
    settlements.clear();
    
    
    isRunning = other.isRunning;
    planCounter = other.planCounter;
   // actionsLog = other.actionsLog;///////////////////

    for (auto action : actionsLog) {
        action=nullptr;
        delete action;  
        actionsLog.push_back(action);
     }



    for (size_t i = 0; i < other.facilitiesOptions.size(); i++)
    {
        facilitiesOptions.push_back( FacilityType(other.facilitiesOptions[i].getName(),other.facilitiesOptions[i].getCategory(),other.facilitiesOptions[i].getCost(),
        other.facilitiesOptions[i].getLifeQualityScore(),other.facilitiesOptions[i].getEconomyScore(),other.facilitiesOptions[i].getEnvironmentScore()));
    }
    
    for (auto settlement : other.settlements) {
        settlements.push_back(new Settlement(*settlement));
    }

    plans.clear();

   for (auto& plan : other.plans) {
      plans.push_back( Plan(plan));
    }

    return *this;
}

Simulation::Simulation(Simulation&& other):
      isRunning(other.isRunning), 
      planCounter(other.planCounter),
      actionsLog(std::move(other.actionsLog)),
      plans(std::move(other.plans)),              
    settlements(std::move(other.settlements)),  
    facilitiesOptions(std::move(other.facilitiesOptions)) {
    other.isRunning = false;
    other.planCounter = 0;
}

Simulation& Simulation::operator=(Simulation&& other){
    if (this == &other) {
        return *this; 
    }
    for (auto settlement : settlements) {
        delete settlement;
    }
    settlements.clear();
    isRunning = other.isRunning;
    planCounter = other.planCounter;
    actionsLog = std::move(other.actionsLog);
    plans = std::move(other.plans);
    settlements = std::move(other.settlements);
    facilitiesOptions = std::move(other.facilitiesOptions);
    other.isRunning = false;
    other.planCounter = 0;

    return *this;
}