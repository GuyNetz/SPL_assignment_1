#include "../include/Plan.h"
#include <string> 
#include <sstream>

//constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
:   plan_id(planId),
    settlement(settlement),
    selectionPolicy(selectionPolicy),
    facilityOptions(facilityOptions),
    status(PlanStatus::AVALIABLE),
    facilities(),
    underConstruction(), 
    life_quality_score(0),
    economy_score(0),
    environment_score(0) {}

//getters
const int Plan::getlifeQualityScore() const{return life_quality_score;}
const int Plan::getEconomyScore() const{return economy_score;}
const int Plan::getEnvironmentScore() const{return environment_score;}
const vector<Facility*> &Plan::getFacilities() const{return facilities;}
  

//toString method
const string Plan::toString() const{        
    string planStatus = "AVAILABLE";        //getting PlanStatus as a string
    if(status == PlanStatus::BUSY){
        planStatus = "BUSY";
    }
    string facilitiesList = "";             //getting list of facilities as a string
    for (Facility* facility : facilities) {
        string facility_status = "UNDER_CONSTRUCTIONS";
        if(facility->getStatus() == FacilityStatus::OPERATIONAL){
           facility_status = "OPERATIONAL";
        }    
        facilitiesList = facilitiesList + "FacilityName: " + facility->getName() + "\n" + 
                                        "FacilityStatus: " + facility_status + "\n";
    }
    return "PlanID: " + std::to_string(plan_id) + "\n" +        //returning full plan string
            "SettlementName: " + settlement.getName() + "\n" +
            "PlanStatus: " + planStatus + "\n" +
            "SelectionPolicy: " + selectionPolicy->toString() + "\n" + 
            "LifeQualityScore: " + std::to_string(life_quality_score) + "\n" + 
            "EconomyScore: " + std::to_string(economy_score) + "\n" +
            "EnvironmentScore: " + std::to_string(environment_score) + "\n" +
            facilitiesList;
}

//setters
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){
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

void Plan::addFacility(Facility* facility){
    underConstruction.push_back(facility);
}

void Plan::step(){
    if(settlement.getType() == SettlementType::VILLAGE){
        if(underConstruction.size() == 0){
            Facility* facility = const_cast<Facility*>(&selectionPolicy->selectFacility(facilityOptions));
            addFacility(facility);
        }
    }
}


















