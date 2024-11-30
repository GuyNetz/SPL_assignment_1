#include <iostream>
#include "../include/Facility.h"
#include <sstream>

//Constructor for FacilityType
FacilityType::FacilityType(const string &name, const FacilityCategory category, const int price,
                            const int lifeQuality_score, const int economy_score, const int environment_score)
            :name(name), category(category), price(price), lifeQuality_score(lifeQuality_score),
            economy_score(economy_score), environment_score(environment_score) {}

//FaciltyType getters
const string &FacilityType::getName() const {return name;}
int FacilityType::getCost() const {return price;}
int FacilityType::getLifeQualityScore() const {return lifeQuality_score;}
int FacilityType::getEnvironmentScore() const {return environment_score;}
int FacilityType::getEconomyScore() const {return economy_score;}
FacilityCategory FacilityType::getCategory() const {return category;}

//step function
FacilityStatus Facility::step(){
  if(getTimeLeft() != 0){
    setTimeLeft(getTimeLeft() - 1);
  }  
  if(getTimeLeft() == 0){
    setStatus(FacilityStatus::OPERATIONAL);
  }
  return getStatus();
}

//Facility constructors
Facility::Facility(const string &name, const string &settlementName, const FacilityCategory category, 
                   const int price, const int lifeQuality_score, const int economy_score, 
                   const int environment_score)
    : FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score),
      settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price) {}


Facility::Facility(const FacilityType &type, const string &settlementName)
    : FacilityType(type),  
      settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(type.getCost()) {}

//Facility getters
const string &Facility::getSettlementName() const {return settlementName;}
const FacilityStatus &Facility::getStatus() const {return status;}
const int Facility::getTimeLeft() const {return timeLeft;}
const FacilityStatus& Facility::getStatus() const {return status;}

//Facility setters
void Facility::setStatus(FacilityStatus status) {this->status = status;}
void Facility::setTimeLeft(int timeLeft) {this->timeLeft = timeLeft;}

//toString
const string Facility::toString() const {
    std::stringstream ss;
    ss << "Facility Name: " << getName() << "\n";
    ss << "Settlement: " << getSettlementName() << "\n";
    ss << "Price: " << getCost() << "\n";
    ss << "Life Quality Score: " << getLifeQualityScore() << "\n";
    ss << "Economy Score: " << getEconomyScore() << "\n";
    ss << "Environment Score: " << getEnvironmentScore() << "\n";
    ss << "Status: " << (status == FacilityStatus::UNDER_CONSTRUCTIONS ? "Under Construction" : "Operational") << "\n";
    ss << "Time Left: " << getTimeLeft() << " days\n";
    
    return ss.str();
}


       
