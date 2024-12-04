#include "../include/Action.h"
#include <string> 
#include <sstream>
extern Simulation* backup;
//****************************** BaseAction ******************************
//constructor
BaseAction::BaseAction()
:errorMsg(""), status(ActionStatus::COMPLETED) {}

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

const string BaseAction::statusToString() const{
    if (status == ActionStatus::COMPLETED){
        return "COMPLETED";
    } else {
        return "ERROR";
    }
}

//****************************** SimulateStep ******************************
SimulateStep::SimulateStep(const int numOfSteps) : numOfSteps(numOfSteps) {}

void SimulateStep::act(Simulation &simulation) {
    for (int i = 0; i < numOfSteps; ++i) {
        simulation.step();
    }
    complete();
}

const string SimulateStep::toString() const {
    return "step " + std::to_string(numOfSteps) + " " + statusToString();
}

SimulateStep *SimulateStep::clone() const {
    return new SimulateStep(*this);
}

// ****************************** AddPlan ******************************
//constructor
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy)
:settlementName(settlementName), selectionPolicy(selectionPolicy){}

//act function
void AddPlan::act(Simulation &simulation){
    if (!simulation.isSettlementExists(settlementName)){
       error("Cannot create this plan");
    }else if(selectionPolicy == "nve"){
        simulation.addPlan(simulation.getSettlement(settlementName), new NaiveSelection());
    }else if(selectionPolicy == "bal"){
        simulation.addPlan(simulation.getSettlement(settlementName), new BalancedSelection(0,0,0));
    }else if (selectionPolicy == "eco"){
        simulation.addPlan(simulation.getSettlement(settlementName), new EconomySelection());
    }else if (selectionPolicy == "env"){
        simulation.addPlan(simulation.getSettlement(settlementName), new SustainabilitySelection());
    } else {  error("Cannot create this plan");
    }  
}

 const string AddPlan::toString() const{
    return "plan " + settlementName + " " + selectionPolicy + " " + this->statusToString();
 }

 AddPlan* AddPlan::clone() const{
    return new AddPlan(*this);
}

// ****************************** AddSettlement ******************************

AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):
settlementName(settlementName), settlementType(settlementType) {}

void AddSettlement::act(Simulation &simulation){
   if (simulation.isSettlementExists(settlementName)){
        error("Settlement already exists");
   }else{
        simulation.addSettlement(new Settlement(settlementName, settlementType));
        complete();
   }
}

 const string AddSettlement::toString() const{
    switch (settlementType){
        case SettlementType::VILLAGE:
            return "settlement " + settlementName + " 0 "+ this->statusToString() ;
            break;
        case SettlementType::CITY:
            return "settlement " + settlementName + " 1 " + this->statusToString();
            break;
        case SettlementType::METROPOLIS:
            return "settlement " + settlementName + " 2 " + this->statusToString() ;
            break;
    }
    return "error"; // shouldnt get here
 }

 AddSettlement*AddSettlement::clone() const{
    return new AddSettlement(*this);
}

// ****************************** AddFacility ******************************
//constructor
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, 
const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
facilityName(facilityName),
facilityCategory(facilityCategory),
price(price),
lifeQualityScore(lifeQualityScore),
economyScore(economyScore),
environmentScore(environmentScore) {}

// act function
void AddFacility::act(Simulation &simulation){
    if (simulation.isFacilityExists(facilityName)){
        error("Facility already exists");
   }else{
        simulation.addFacility(FacilityType(facilityName,facilityCategory,price,lifeQualityScore,economyScore,environmentScore));
        complete();
   }
}

const string AddFacility::toString() const{
    string a;
    switch (facilityCategory){
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
    return "facility " + facilityName + " "  + a + " " +  std::to_string(price) + " " +
    std::to_string(lifeQualityScore) + " " +std::to_string(economyScore) + " " + 
    std::to_string(environmentScore)+ " " + this->statusToString() ;
}

AddFacility* AddFacility::clone() const{
    return new AddFacility(*this);
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
    return "planStatus  "+planId + this->statusToString() ;
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Change Plan Policy class

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy):
planId(planId),
newPolicy(newPolicy)
{}

const std::string ChangePlanPolicy::toString() const
{ 
    return "changePolicy "+std::to_string(planId) +" "+ newPolicy +this->statusToString();
}

ChangePlanPolicy *ChangePlanPolicy::clone() const{
    return new ChangePlanPolicy(planId,newPolicy);
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
    if(i!="")
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
    simulation.print_action_log();
}

PrintActionsLog *PrintActionsLog::clone() const{
    return new PrintActionsLog();
}

const string PrintActionsLog::toString() const{
    return "log" + this->statusToString() ;
}


////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////close class
Close::Close(){}

void Close::act(Simulation &simulation){
    simulation.close();
}

Close *Close::clone() const{ 
return new Close();
}

const string Close::toString() const{
    return " close" + this->statusToString();
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Backup simulation class BackupSimulation()

BackupSimulation::BackupSimulation(){}
/////// empty
void BackupSimulation::act(Simulation &simulation){
    if (backup != nullptr) {
        delete backup;  
        backup = nullptr; 
    }
    backup = new Simulation(simulation);
}

BackupSimulation *BackupSimulation::clone() const{ 
    return new BackupSimulation();
    }

const string BackupSimulation::toString() const{
    return "backup " + this->statusToString();
   }

    ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////Backup simulation class RestoreSimulation()

RestoreSimulation::RestoreSimulation(){}

void RestoreSimulation::act(Simulation &simulation) {
    if (backup != nullptr) {
        simulation = *backup;
    }
}

RestoreSimulation *RestoreSimulation::clone() const{
 return new RestoreSimulation();
}

const string RestoreSimulation::toString() const{
    return "restore " + this->statusToString();
   }