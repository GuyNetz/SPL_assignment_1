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
/////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Add Plan class

///constructor
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy)
:settlementName(settlementName), selectionPolicy(selectionPolicy){}

/////////////////////////////////// selection policy/settlement name inccorect need to return an error
void AddPlan::act(Simulation &simulation){
    if (!simulation.isSettlementExists(settlementName)){
       error("Cannot create this plan");
    }
    
    Settlement *settlementPtr = &simulation.getSettlement(settlementName);
    if(selectionPolicy == "nve"){
        simulation.addPlan(simulation.getSettlement(settlementName), &NaiveSelection());
    }else if(selectionPolicy == "bal"){
        simulation.addPlan(simulation.getSettlement(settlementName), &BalancedSelection(0,0,0) );
    }else if (selectionPolicy == "eco"){
        simulation.addPlan(simulation.getSettlement(settlementName), &EconomySelection());
    }else if (selectionPolicy == "env"){
        simulation.addPlan(simulation.getSettlement(settlementName), &SustainabilitySelection());
    } else{  error("Cannot create this plan");
    }
    
}
///////////////////// not sure of the syntax but something like this
 const string AddPlan::toString() const{
    return "settlement= "+ settlementName +" selection policiy= "+selectionPolicy;
 }
//////////////////////// this should be enough?
 AddPlan* AddPlan::clone() const{
return new AddPlan(settlementName,selectionPolicy);
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Add Settlement class
AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):
settlementName(settlementName),
settlementType(settlementType)
{}

AddSettlement*AddSettlement::clone() const{
    return new AddSettlement(settlementName,settlementType);
}

 const string AddSettlement::toString() const{
    switch (settlementType)
    {
    case SettlementType::CITY:
         return "settlementName= "+ settlementName +" settlement type= " + "CITY" ;
          break;
    case SettlementType::VILLAGE:
        return "settlementName= "+ settlementName +" settlement type= " + "VILLAGE" ;
        break;
    case SettlementType::METROPOLIS:
        return "settlementName= "+ settlementName +" settlement type= " + "METROPOLIS" ;
        break;
    }
 }