#include "../include/SelectionPolicy.h"
#include <climits>
#include <algorithm>

//Naive Selection
NaiveSelection::NaiveSelection()    //constructor
: lastSelectedIndex(-1) {}

const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){  //select func
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    return facilitiesOptions[lastSelectedIndex];
}

const string NaiveSelection::toString() const{
    return "nve";
}

NaiveSelection *NaiveSelection::clone() const{
    return new NaiveSelection(*this);
}

//Balanced Selection
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore)  //constructor
: LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}

int BalancedSelection::maxDifference(int a, int b, int c){      //helper function
    int max_value = std::max({a, b, c});  // Find the maximum of the three
    int min_value = std::min({a, b, c});  // Find the minimum of the three
    return max_value - min_value;  // Return the difference   
}

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){   //select func
    int return_index = -1;
    int minDif = INT_MAX;
    int index = -1;
    for (const FacilityType& facility : facilitiesOptions) {
        index = index + 1;
        int currDif = maxDifference(LifeQualityScore+facility.getLifeQualityScore(),
                                    EconomyScore+facility.getEconomyScore(),
                                    EnvironmentScore+facility.getEnvironmentScore());
        if(currDif < minDif){
            minDif = currDif;
            return_index = index;
        }                            
    }
    return facilitiesOptions[return_index];   
}

const string BalancedSelection::toString() const{
    return "bal";
}

BalancedSelection *BalancedSelection::clone() const{
    return new BalancedSelection(*this);
}


//Economy Selection
EconomySelection::EconomySelection()    //constructor
:lastSelectedIndex(-1) {} 

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){    //select func
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    for (int i= lastSelectedIndex; i < static_cast<int>(facilitiesOptions.size()); i = (i + 1) % facilitiesOptions.size()){
        if(facilitiesOptions[i].getCategory()==FacilityCategory::ECONOMY){ 
            lastSelectedIndex = i;
            return facilitiesOptions[i];
        }
    }
    return facilitiesOptions[lastSelectedIndex]; //shouldnt get here
}

const string EconomySelection::toString() const{
    return "eco";
}

EconomySelection *EconomySelection::clone() const{
    return new EconomySelection(*this);
}

//Sustainability
SustainabilitySelection::SustainabilitySelection()    //constructor
:lastSelectedIndex(-1) {} 

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){ //select func
    lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    for (int i = lastSelectedIndex; i < static_cast<int>(facilitiesOptions.size()); i = (i + 1) % facilitiesOptions.size()) {
        if(facilitiesOptions[i].getCategory()==FacilityCategory::ENVIRONMENT){ 
            lastSelectedIndex = i;
            return facilitiesOptions[i];
        }
    }
    return facilitiesOptions[lastSelectedIndex]; //shouldnt get here
}

const string SustainabilitySelection::toString() const{
    return "env";
}

SustainabilitySelection *SustainabilitySelection::clone() const{
    return new SustainabilitySelection(*this);
}























