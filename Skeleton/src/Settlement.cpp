#include <iostream>
#include <string>
#include "../include/Settlement.h"

Settlement::Settlement(const string &name, SettlementType type)     //constructor
: name(name), type(type) {}

const string &Settlement::getName() const {return name;}            //name getter

SettlementType Settlement::getType() const {return type;}           //type getter

const string Settlement::toString() const {                         //toString method
if (type == SettlementType::VILLAGE) {
    return "Settlement Name: " + getName() + ", Settlement Type: Village";
} else if (type == SettlementType::CITY) {
    return "Settlement Name: " + getName() + ", Settlement Type: City";
} else if (type == SettlementType::METROPOLIS) {
    return "Settlement Name: " + getName() + ", Settlement Type: Metropolis";
} else {
    return "Settlement Name: " + getName() + ", Settlement Type: Unknown";
}
}    

