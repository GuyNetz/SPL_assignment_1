#include "../include/Plan.h"
#include <string> 
#include <sstream>

//constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
:plan_id(planId),
settlement(settlement),
selectionPolicy(selectionPolicy),
status(PlanStatus::AVALIABLE),
facilities(),
underConstruction(), 
facilityOptions(facilityOptions),
life_quality_score(0),
economy_score(0),
environment_score(0) {}

//copy constructor
Plan::Plan(const Plan& other)
    :plan_id(other.plan_id),
    settlement(std::move(other.settlement)),
    selectionPolicy(other.selectionPolicy ? other.selectionPolicy->clone() : nullptr),
    status(other.status),
    facilities(),
    underConstruction(),
    facilityOptions(other.facilityOptions),
    life_quality_score(other.life_quality_score),
    economy_score(other.economy_score),
    environment_score(other.environment_score) {

    // Deep copy for underConstruction
    for (Facility* facility : other.underConstruction) {
        underConstruction.push_back(new Facility(*facility)); // Create new Facility instance
    }
    // Deep copy for facilities
    for (Facility* facility : other.facilities) {
        facilities.push_back(new Facility(*facility)); // Create new Facility instance
    }
}

//destructor
Plan::~Plan() {

   // Free memory for each Facility in the facilities vector
   delete selectionPolicy;
   selectionPolicy=nullptr;
    for (Facility* facility : facilities) {
        delete facility;
        facility=nullptr;
    }

    // Free memory for each Facility in the underConstruction vector
    for (Facility* facility : underConstruction) {
        delete facility;
        facility=nullptr;
    }   
}

//getters
const int Plan::getlifeQualityScore() const{return life_quality_score;}
const int Plan::getEconomyScore() const{return economy_score;}
const int Plan::getEnvironmentScore() const{return environment_score;}
const vector<Facility*> &Plan::getFacilities() const{return facilities;}
const int Plan::getPlanId() const{return plan_id;}
const string Plan::getSettlementName() const{
    return settlement.getName();
}

//toString method
const string Plan::toString() const{        
    string planStatus = "AVAILABLE";        //getting PlanStatus as a string
    if(status == PlanStatus::BUSY){
        planStatus = "BUSY";
    }
    string under_construction_list = "";             //getting list of under construction facilities as a string
    for (Facility* facility : underConstruction) {  
        under_construction_list = under_construction_list + "FacilityName: " + facility->getName() + "\n" + 
                                                            "FacilityStatus: UNDER_CONSTRUCTIONS \n";
    }
    string operational_list = "";             //getting list of operational facilities as a string
    for (Facility* facility : facilities) {   
        operational_list = operational_list + "FacilityName: " + facility->getName() + "\n" + 
                                              "FacilityStatus: OPERATIONAL \n";
    }
    return "PlanID: " + std::to_string(plan_id) + "\n" +        //returning full plan string
            "SettlementName: " + settlement.getName() + "\n" +
            "PlanStatus: " + planStatus + "\n" +
            "SelectionPolicy: " + selectionPolicy->toString() + "\n" + 
            "LifeQualityScore: " + std::to_string(life_quality_score) + "\n" + 
            "EconomyScore: " + std::to_string(economy_score) + "\n" +
            "EnvironmentScore: " + std::to_string(environment_score) + "\n" +
            under_construction_list + operational_list;
}

//setters
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy) {
    if (this->selectionPolicy != nullptr) { 
        delete this->selectionPolicy; 
        this->selectionPolicy=nullptr;
    }
    this->selectionPolicy = selectionPolicy; 
}

//printStatus method
void Plan::printStatus(){
    string s = "AVAILABLE";
    if (status == PlanStatus::BUSY) {
        s = "BUSY";
    }
    std::cout << "Status: " << s << std::endl;
}

string Plan::policy_tostring(){
    if(selectionPolicy->toString()=="nve"){
        return "Naive";
    }else if (selectionPolicy->toString()=="bal"){
        return "Balanced";
    } else if (selectionPolicy->toString()=="eco"){
        return "Economy";
    } else if(selectionPolicy->toString()=="env"){
        return "Sustainability";
    }else
        return " ";//shouldnt get here.
    
    
}
void Plan::addFacility(Facility* facility){
    underConstruction.push_back(facility);
}

bool Plan::isStatusAvailable() const {
    return status == PlanStatus::AVALIABLE;
}

void Plan::updateStatus() {
    status = PlanStatus::BUSY;
    if((settlement.getType() == SettlementType::VILLAGE) && (underConstruction.size() < 1)){
        status = PlanStatus::AVALIABLE;
    }else if((settlement.getType() == SettlementType::CITY) && (underConstruction.size() < 2)){
        status = PlanStatus::AVALIABLE;
    }else if((settlement.getType() == SettlementType::METROPOLIS) && (underConstruction.size() < 3)){
        status = PlanStatus::AVALIABLE;
    }
}

void Plan::step(){
    while(isStatusAvailable()){
        const FacilityType& selected = selectionPolicy->selectFacility(facilityOptions);
        addFacility(new Facility(selected, settlement.getName()));
        updateStatus();
    }
    for (size_t i = 0; i < underConstruction.size();) {
        Facility* facility = underConstruction[i];  
        facility->step();

        if (facility->getTimeLeft() == 0) {
            facilities.push_back(facility);
            life_quality_score = life_quality_score + facility->getLifeQualityScore();
            economy_score = economy_score + facility->getEconomyScore();
            environment_score = environment_score + facility->getEnvironmentScore();
            underConstruction.erase(underConstruction.begin() + i);
            status = PlanStatus::AVALIABLE;  
        } else {
            ++i;  
        }
    }   
}


















