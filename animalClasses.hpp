#ifndef ANIMAL_CLASSES_H
#define ANIMAL_CLASSES_H
#include <string>

struct Dogs {
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











#endif