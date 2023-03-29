#ifndef ANIMAL_CLASSES_H
#define ANIMAL_CLASSES_H
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>

class Animals{
public:
    std::string animal;

};
class Dogs:public Animals {
public:
    std::string name;
    std::string breed;
    std::string size;
    float age;
    std::string goodWithSmallDogs;
    std::string goodWithLargeDogs;
    std::string goodWithAdults;
    std::string goodWithKids;
    std::string room;

    Dogs() {
        animal = "Dog";
        name = "default";
        breed = "default";
        size = "Small";
        age = 1.0f;
        goodWithSmallDogs = "Yes";
        goodWithLargeDogs = "Yes";
        goodWithAdults = "Yes";
        goodWithKids = "Yes";
        room = "FF";
    }
};

struct Room{
    std::string name;
    std::unordered_map<std::string, Dogs> roomList;
    void printDogList(){
        for(auto const& [name, dog] : roomList){
            std::cout << name << std::endl;
        } 
    }
    std::vector<std::string> dogNames;
    void fillVec(){
        for(auto const& [name, dog] : roomList){
            dogNames.push_back(name);
        } 
    }
};









#endif