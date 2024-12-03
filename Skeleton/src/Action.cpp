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
const string BaseAction::status_string() const
{
    if (status==ActionStatus::COMPLETED)
    {
        return "COMPLETED";
    }
    else{return "ERROR";}
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
    
    
    if(selectionPolicy == "nve"){
        simulation.addPlan(simulation.getSettlement(settlementName), new NaiveSelection());
    }else if(selectionPolicy == "bal"){
        simulation.addPlan(simulation.getSettlement(settlementName), new BalancedSelection(0,0,0) );
    }else if (selectionPolicy == "eco"){
        simulation.addPlan(simulation.getSettlement(settlementName), new EconomySelection());
    }else if (selectionPolicy == "env"){
        simulation.addPlan(simulation.getSettlement(settlementName), new SustainabilitySelection());
    } else{  error("Cannot create this plan");
    }
    
}
///////////////////// not sure of the syntax but something like this
 const string AddPlan::toString() const{
    return "plan"+ settlementName +" selection policy= "+ selectionPolicy + this->status_string() ;
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

void AddSettlement::act(Simulation &simulation){
   if (!simulation.isSettlementExists(settlementName))
   {
    simulation.addSettlement(new Settlement(settlementName,settlementType));
   }
   else
   error("cannot create this settlement");
    
    
}

AddSettlement*AddSettlement::clone() const{
    return new AddSettlement(settlementName,settlementType);
}

 const string AddSettlement::toString() const{
    switch (settlementType)
    {
    case SettlementType::CITY:
         return "settlement "+ settlementName +"  " + "CITY " + this->status_string();
          break;
    case SettlementType::VILLAGE:
        return "settlement "+ settlementName +"  " + "VILLAGE "+ this->status_string() ;
        break;
    case SettlementType::METROPOLIS:
        return "settlement "+ settlementName +"  " + "METROPOLIS " + this->status_string() ;
        break;
    }
    return "error"; // shouldnt get here
 }

 ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Add Facility class

AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, 
const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
facilityName(facilityName),
facilityCategory(facilityCategory),
price(price),
lifeQualityScore(lifeQualityScore),
economyScore(economyScore),
environmentScore(environmentScore)
{}

// add facility but there is no case for error.
void AddFacility::act(Simulation &simulation){
    simulation.addFacility(FacilityType(facilityName,facilityCategory,price,
    lifeQualityScore,economyScore,environmentScore));
}

AddFacility* AddFacility::clone() const{
    return new AddFacility(facilityName,facilityCategory, 
price,lifeQualityScore, economyScore,  environmentScore);
}

const string AddFacility::toString() const{
    string a;
    switch (facilityCategory)
    {
    case  FacilityCategory::LIFE_QUALITY:
        a="0";
        break;
    case FacilityCategory::ECONOMY:
    a="1";
    break;
    case FacilityCategory::ENVIRONMENT:
    a="2";
    break;
    }
    return "facility "+ facilityName + " "  + a+" " +  std::to_string(price) + " "+
    std::to_string(lifeQualityScore) +
    " " +std::to_string(economyScore) + " " +std::to_string(environmentScore)+" "+this->status_string() ;
}


////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////print status class

PrintPlanStatus::PrintPlanStatus(int planId):
planId(planId)
{}
void PrintPlanStatus::act(Simulation &simulation){
    simulation.getPlan(planId).toString();
}

PrintPlanStatus *PrintPlanStatus::clone() const{
    return new PrintPlanStatus(planId);
}

const string PrintPlanStatus::toString() const
{
    return "planStatus  "+planId + this->status_string() ;
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Change Plan Policy class

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy):
planId(planId),
newPolicy(newPolicy)
{}

const std::string ChangePlanPolicy::toString() const
{ 
    return "changePolicy "+std::to_string(planId) +" "+ newPolicy +this->status_string();
}


void ChangePlanPolicy::act(Simulation &simulation)
{
    string i,a;
    a=simulation.getPlan(planId).policy_tostring();
    if(newPolicy == "nve"&&simulation.getPlan(planId).toString()!="nve" ){
        simulation.getPlan(planId).setSelectionPolicy(new NaiveSelection());
        i="Naive";
    }
    else if(newPolicy == "bal"&&simulation.getPlan(planId).toString()!="bal"){
        simulation.getPlan(planId).setSelectionPolicy(new BalancedSelection(0,0,0));
        i="Balanced";
    }
    else if (newPolicy == "eco"&&simulation.getPlan(planId).toString()!="eco"){
        simulation.getPlan(planId).setSelectionPolicy(new EconomySelection());
        i="Economy";
    }else if (newPolicy == "env"&&simulation.getPlan(planId).toString()!="env"){
        simulation.getPlan(planId).setSelectionPolicy(new SustainabilitySelection());
        i="Sustainability";
    } 
    else{  error("Cannot change selection policy");}
    
    if(&i!=nullptr)
    {
        std::cout << "planID: " << planId << std::endl;
        std::cout << "previousPolicy: " << a << std::endl;
        std::cout << "newPolicy: " << i << std::endl;

    }
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Change Plan Policy class
PrintActionsLog::PrintActionsLog(){}

void PrintActionsLog::act(Simulation &simulation){
}