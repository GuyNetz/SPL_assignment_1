#include <iostream>
#include "../include/Settlement.h"

Settlement::Settlement(const string &name, SettlementType type)      //constructor
: name(name), type(type) {}

const string &Settlement::getName() const {                          //name getter
    return name;
    }           

SettlementType Settlement::getType() const {return type;}            //type getter

const string Settlement::toString() const {                          //toString method
if (type == SettlementType::VILLAGE) {
    return "Settlement Name: " + name + ", Settlement Type: Village\n";
} else if (type == SettlementType::CITY) {
    return "Settlement Name: " + name + ", Settlement Type: City\n";
} else if (type == SettlementType::METROPOLIS) {
    return "Settlement Name: " + name + ", Settlement Type: Metropolis\n";
}
return "Error: Unknown settlement type\n";
}    
