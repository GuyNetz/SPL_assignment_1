#include "../include/Action.h"
#include <string> 
#include <sstream>

//constructor
BaseAction::BaseAction()
:errorMsg(), status() {}

//getters
ActionStatus BaseAction::getStatus() const{return status;}

//protected functions
void BaseAction::complete(){
    status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
}

const string &BaseAction::getErrorMsg() const{return errorMsg;}

//Add Plan class

//constructor
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy)
:settlementName(settlementName), selectionPolicy(selectionPolicy){}

void AddPlan::act(Simulation &simulation){
    Settlement *settlementPtr = &simulation.getSettlement(settlementName);
    if(selectionPolicy == "nve"){
        simulation.addPlan(*settlementPtr, &NaiveSelection());
    }else if(selectionPolicy == "bal"){
         simulation.addPlan(*settlementPtr, &BalancedSelection(settlementPtr) )
    }
    }
    simulation.addPlan(simulation.getSettlement(settlementName), selectionPolicy);
}