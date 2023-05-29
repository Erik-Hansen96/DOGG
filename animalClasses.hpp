#ifndef ANIMAL_CLASSES_H
#define ANIMAL_CLASSES_H
#include <string>
#include <iostream>


class Animals{
public:
    std::string name;
    float age;
    std::string animalType;
    Animals(std::string name, float age, std::string animalType) : name(name), age(age), animalType(animalType) {};
    

};
class Dogs : public Animals {
public:
    std::string breed;
    std::string size;
    std::string goodWithSmallDogs;
    std::string goodWithLargeDogs;
    std::string goodWithAdults;
    std::string goodWithKids;
    std::string room;

    Dogs() : Animals("default", 1.0f, "Dog") {
        breed = "default";
        size = "Small";
        goodWithSmallDogs = "Yes";
        goodWithLargeDogs = "Yes";
        goodWithAdults = "Yes";
        goodWithKids = "Yes";
        room = "FF";
    }
};











#endif