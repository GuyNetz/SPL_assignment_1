#include <iostream>
#include "../include/Settlement.h"      //added to check settlement class
#include "../include/Facility.h"        //added to check Facility class
#include "../include/SelectionPolicy.h" //added to check SelectionPolicy class
#include "../include/Plan.h"            //added to check Plan class
#include "../include/Simulation.h"      //added to check Simulation class
using namespace std;

// Simulation* backup = nullptr;

int main(int argc, char** argv){
    // if(argc!=2){
    //     cout << "usage: simulation <config_path>" << endl;
    //     return 0;
    // }
    // string configurationFile = argv[1];
    // Simulation simulation(configurationFile);
    // simulation.start();
    // if(backup!=nullptr){
    // 	delete backup;
    // 	backup = nullptr;
    // }

    //Settlement test
    // Settlement s("testName", SettlementType::METROPOLIS);
    // cout << s.toString();
    // return 0;

    // //Facility test
    // Facility f("Facility A", "KfarSPL", FacilityCategory::LIFE_QUALITY, 5, 90, 75, 85);    //constructor
    // cout << "Facility details (initial):\n" << f.toString();    //toString

    // f.setStatus(FacilityStatus::OPERATIONAL);
    // f.step();
    // f.step();
    // f.step();
    // f.step();
    // f.step();

    // cout << "Facility details (after updates):\n" << f.toString();

    // cout << "Settlement Name: " << f.getSettlementName();
    // cout << "Time Left: " << f.getTimeLeft();
    // cout << "Status: " << (f.getStatus() == FacilityStatus::OPERATIONAL ? "Operational" : "Under Construction");

    //Selection policy test
    // FacilityType Hospital = FacilityType("Hospital", FacilityCategory::LIFE_QUALITY, 5, 9, 8, 10);
    // FacilityType Kindergarten = FacilityType("Kindergarten", FacilityCategory::LIFE_QUALITY, 3, 3, 2, 1);
    // FacilityType desalinationPlant = FacilityType("Desalination Plant", FacilityCategory::ENVIRONMENT, 6, 2, 1, 3);
    // std::vector<FacilityType> v = {Hospital, Kindergarten, desalinationPlant};

    // NaiveSelection policy1 = NaiveSelection();
    // FacilityType FaType1 = policy1.selectFacility(v);
    // cout << FaType1.getName() << std::endl;

    // BalancedSelection balPolicy = BalancedSelection(1,2,0);
    // FacilityType firstFacility = balPolicy.selectFacility(v);
    // cout << firstFacility.getName() << std::endl;

    // EconomySelection policy2 = EconomySelection();
    // FacilityType FaType2 = policy2.selectFacility(v);
    // cout << FaType2.getName() << std::endl;
    // FacilityType FaType3 = policy2.selectFacility(v);
    // cout << FaType3.getName() << std::endl;
    // FacilityType FaType4 = policy2.selectFacility(v);
    // cout << FaType4.getName() << std::endl;
    // FacilityType FaType5 = policy2.selectFacility(v);
    // cout << FaType5.getName() << std::endl;

    // SustainabilitySelection policy3 = SustainabilitySelection();
    // FacilityType FaType3 = policy3.selectFacility(v);
    // cout << FaType3.getName() << std::endl;


    /////////////////////////////////////testing plan
        // Settlement settelment_Test("settelment_Test",SettlementType::CITY);
        // NaiveSelection naiveSelectionPolicy_test =  NaiveSelection();
        // EconomySelection economySelectionPolicy_test = EconomySelection();
        // FacilityType Hospital = FacilityType("Hospital", FacilityCategory::ECONOMY, 5, 9, 8, 10);
        // FacilityType Kindergarten = FacilityType("Kindergarten", FacilityCategory::LIFE_QUALITY, 2, 3, 2, 1);
        // FacilityType desalinationPlant = FacilityType("Desalination Plant", FacilityCategory::ENVIRONMENT, 3, 2, 1, 3);
        // std::vector<FacilityType> v = {Hospital, Kindergarten, desalinationPlant};
        // int planId = 1;
        // Plan myPlan(planId,settelment_Test, &naiveSelectionPolicy_test, v);
        // cout<<myPlan.toString();
        
        
        // myPlan.step();
        // cout<<myPlan.toString();
        
        
        // myPlan.step();
        // cout<<myPlan.toString();

        // myPlan.setSelectionPolicy(&economySelectionPolicy_test);

        // myPlan.step();
        // cout<<myPlan.toString();      
}