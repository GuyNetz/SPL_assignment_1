#include <string>
#include <iostream>
using std::string;

enum class FacilityStatus {
    UNDER_CONSTRUCTIONS,
    OPERATIONAL,
};

enum FacilityCategory {
    LIFE_QUALITY,
    ECONOMY,
    ENVIRONMENT
};

class FacilityType {
protected:
    const std::string name;
    const FacilityCategory category;
    const int price;
    const int lifeQuality_score;
    const int economy_score;
    const int environment_score;

public:
    // Constructor
    FacilityType(const std::string& name, int price, FacilityCategory category, 
                 int lifeQualityScore, int economyScore, int environmentScore)
        : name(name), price(price), category(category),
          lifeQuality_score(lifeQualityScore), economy_score(economyScore), environment_score(environmentScore) {}

    // Getter for name
    const std::string &getName() const {
        return name;
    }

        int getPrice() const {
        return price;
    }

        FacilityCategory getCategory() const {
        return category;
    }

       int getLifeQualityScore() const {
        return lifeQuality_score;
    }

        int getEconomyScore() const {
        return economy_score;
    }
    int getEnvironmentScore() const {
        return environment_score;
    }

    
};

class Facility: public FacilityType {
     private:
        const string settlementName;
        FacilityStatus status;
        int timeLeft;

    public:
  Facility(const string &name, const string &settlementName,
   const FacilityCategory category, const int price, const int lifeQuality_score, 
   const int economy_score, const int environment_score)
   :FacilityType(name,price,category,lifeQuality_score,economy_score,environment_score),
   settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS){
   }
       
};