
#include <iostream>
#include <string>


enum class SettlementType {
    VILLAGE,
    CITY,
    METROPOLIS,
};
//testjgkjsdlgslkd

class Settlement
{
private:
    const std::string _name;  
    SettlementType _type;

    std::string type_name(SettlementType type) const
    {
        if(type==SettlementType::VILLAGE)
        return "Village";
        if(type==SettlementType::CITY)
        return "CITY";
        if(type==SettlementType::METROPOLIS)
        return "METROPOLIS";
    }
  //  g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Settlement.o src/Settlement.cpp 
public:
    Settlement(const std::string &name, SettlementType type)
    : _name(name), _type(type) {}

    const std::string &getName() const {return _name;}

    SettlementType getType() const {return _type;}

     std::string toString() const {
        std::string name1= type_name(_type);
        return "Settlement Name: " + _name + ", Settlement Type: " + name1;
    }
    
};
