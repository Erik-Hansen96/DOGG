#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include "animalClasses.hpp"
using namespace std;



void roomDisplay(char roomLetter, vector<vector<Room>>& roomVec){
    int count = 0;
    Room rooms[8];
    for (int i = 0; i < 8; i++) {
        rooms[i] = roomVec.at(roomLetter - 65).at(i);
        rooms[i].fillVec();
    }
    for(int i = 0; i < 7; i++){
        if (count == 0){
        cout << "\n\n\tROOM " << rooms[0].name << "\t      |\t" << "     ROOM " << rooms[1].name << "\t     |\t" << "     ROOM " << rooms[2].name << "\t    |\t" << "     ROOM " << rooms[3].name << "\t   |" << endl; 
        } else {
            int length;
            for (int j = 0; j < 4; j++){
                if(i <= rooms[j].dogNames.size()){
                    length = rooms[j].dogNames[i-1].length();
                    string spaces(22-length, ' ');
                    cout << rooms[j].dogNames[i-1] << spaces << "|";
                } else {
                    string spaces(22, ' ');
                    cout << spaces << "|";
                }
            }
                cout << endl;
            }count++;
        } 
    cout << "\n----------------------------------------------------------------------------------------------" << endl;
    int count2 = 0;
    for(int i = 0; i < 7; i++){
        if (count2 == 0){
        cout << "\n\n\tROOM " << rooms[4].name << "\t      |\t" << "     ROOM " << rooms[5].name << "\t     |\t" << "     ROOM " << rooms[6].name << "\t    |\t" << "     ROOM " << rooms[7].name << "\t   |" << endl; 
        } else {
            int length;
            for (int j = 4; j < 8; j++){
                if(i <= rooms[j].dogNames.size()){
                    length = rooms[j].dogNames[i-1].length();
                    string spaces(22-length, ' ');
                    cout << rooms[j].dogNames[i-1] << spaces << "|";
                } else {
                    string spaces(22, ' ');
                    cout << spaces << "|";
                }
            }
                cout << endl;
            }count2++;
        } 
    
    cout << "\nChoose a selection:\n1: Add a dog to the kennel\n2: Go back\n3: Remove a dog from the kennel" << endl;
}
void addingDogs(vector<vector<Room>>& roomVec, Room* emptyRoom, unordered_map<string, Dogs> &dogList, char roomLetter){
    while (true){
        roomDisplay(roomLetter, roomVec);
        int input;
        cin >> input;
        cin.ignore();
        if(input == 1){
            cout << "\nDog(s) currently not assigned rooms: " << endl;
                for(auto const& [name, dog] : dogList){
                    cout << name << endl;
                } 
                cout << "\nEnter a dog's name to put into a room" << endl;                    
                string doggoName;
                getline(cin, doggoName);  
                auto it = dogList.find(doggoName);
                if(it != dogList.end()){
                    bool found = false;
                    int kenNum = 0;
                    Dogs dog = it->second;
                    for(int i = 0; i < 8; i++){
                        for(int j = 0; j < 8; j++){
                            if(roomVec.at(i).at(j).roomList.empty()){
                                emptyRoom = &roomVec.at(i).at(j);
                                found = true;
                                goto exit_loops;
                            } 
                        }
                    }exit_loops:
                    if(found){
                        dog.room = emptyRoom->name;
                        emptyRoom->roomList.emplace(doggoName, dog);
                        dogList.erase(doggoName);
                        cout << "\nInserted " << doggoName << " into room " << emptyRoom->name << endl;
                    } else {
                        cout << "\nNo empty rooms\n1: Choose a room for " << doggoName << "\n2: Go back" << endl;
                        int choice;
                        cin >> choice;
                        if(choice == 1){
                            string s;
                            cout << "\nEnter which room you'd like to add " << doggoName << endl;
                            reset:
                            cin >> s;
                            for(char& c : s) c = toupper(c);
                            if(s == "2") continue;
                            bool found = false;
                            for(int i = 0; i < 8; i++){
                                for(int j = 0; j < 8; j++){
                                    if(roomVec.at(i).at(j).name == s){
                                        if(roomVec.at(i).at(j).roomList.size() >= 6){
                                            cout << "\nRoom " << roomVec.at(i).at(j).name << " is full" << endl;
                                            found = true;
                                            break;
                                        }
                                        found = true;
                                        roomVec.at(i).at(j).roomList.emplace(doggoName, dog);
                                        dog.room = roomVec.at(i).at(j).name;
                                        dogList.erase(doggoName);
                                        cout << "\nSuccessfully added " << doggoName << " to room " << roomVec.at(i).at(j).name << endl;
                                        roomVec.at(i).at(j).printDogList();
                                        break;
                                    } 
                                }
                            }
                            if(!found){
                                cout << "\nMisentered room name! Enter a room or Enter 2 to go back" << endl;
                                goto reset;
                            }
                        }
                    }
                } else { 
                    cout << "\nDog not found" << endl;             
                } 
            } else if(input == 2){
                break;
            }
            else if(input == 3){
                cout << "\nEnter a room to remove a dog from" << endl;
                bool found = false;
                string roomToRemove;
                cin >> roomToRemove;
                cin.ignore();
                roomToRemove[0] = toupper(roomToRemove[0]);
                for(int i = 0; i < 8; i++){
                    for(int j = 0; j < 8; j++){
                        if(roomVec.at(i).at(j).name == roomToRemove){
                            found = true;
                            cout << "\nDogs in room " << roomVec.at(i).at(j).name << ":" << endl;
                            roomVec.at(i).at(j).printDogList();
                            cout << "\nEnter which dog you would like to remove" << endl;
                            string dogToRemove;
                            getline(cin, dogToRemove);  
                            auto it = roomVec.at(i).at(j).roomList.find(dogToRemove);
                            if(it != roomVec.at(i).at(j).roomList.end()){
                                bool found = false;
                                Dogs dog = it->second;
                                dog.room = "FF";
                                dogList.emplace(dogToRemove, dog);
                                roomVec.at(i).at(j).roomList.erase(dogToRemove);
                                cout << "\nSuccessfully removed " << dogToRemove << " from room " << roomVec.at(i).at(j).name << endl;
                                return;
                            } 
                        }
                    } 
                }
            }

    }
}
void printKennelMap(){
cout << "\n A\t|\tB\t|\tC\t|\tD\n" << endl;
cout << "---------------------------------------------------\n" << endl;
cout << " E\t|\tF\t|\tG\t|\tH\n" << endl;
}
void printDogInfo(Dogs d){
    cout << "\n" << d.name << "'s info:\n" << endl;
    cout << "Name: " << d.name << endl;
    cout << "Breed: " << d.breed << endl;
    cout << "Size: " << d.size << endl;
    cout << "Age: " << d.age << endl;
    cout << "Good with small dogs: " << d.goodWithSmallDogs << endl;
    cout << "Good with large dogs: " << d.goodWithLargeDogs << endl;
    cout << "Good with people: " << d.goodWithAdults << endl;
    cout << "Good with kids: " << d.goodWithKids << endl;
}

void sizeFunc(Dogs &newDog){
    int choice = 0;
    cout << "\nSize:\n1: Small\n2: Medium\n3: Large" << endl;
    cin >> choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout << "\nInvalid input." << endl;
        sizeFunc(newDog);
        return;
    }
    switch(choice){
        case 1:
            newDog.size  = "Small"; break;
        case 2:
            newDog.size = "Medium"; break;
        case 3:
            newDog.size = "Large"; break;
        default:
            cout << "\nInvalid input." << endl;
            cin.clear();
            sizeFunc(newDog);
            return;
        }
}
void goodWithSmallDogsFunc(Dogs &newDog){
    int choice = 0;
    cout << "\nGood with small dogs?\n1: Yes\n2: No\n3: Not sure" << endl;
    cin >> choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout << "\nInvalid input." << endl;
        sizeFunc(newDog);
        return;
    }
    switch(choice){
        case 1:
            newDog.goodWithSmallDogs  = "Yes"; break;
        case 2:
            newDog.goodWithSmallDogs = "No"; break;
        case 3:
            newDog.goodWithSmallDogs = "Not sure"; break;
        default:
            cout << "Invalid input." << endl;
            goodWithSmallDogsFunc(newDog);
            return;
        }
}
void goodWithLargeDogsFunc(Dogs &newDog){
    int choice = 0;
    cout << "\nGood with large dogs?\n1: Yes\n2: No\n3: Not sure" << endl;
    cin >> choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout << "\nInvalid input." << endl;
        sizeFunc(newDog);
        return;
    }
    switch(choice){
        case 1:
            newDog.goodWithLargeDogs  = "Yes"; break;
        case 2:
            newDog.goodWithLargeDogs = "No"; break;
        case 3:
            newDog.goodWithLargeDogs = "Not sure"; break;
        default:
            cout << "Invalid input." << endl;
            goodWithLargeDogsFunc(newDog);
            return;
        }
}
void goodWithAdultsFunc(Dogs &newDog){
    int choice;
    cout << "\nGood with adults?\n1: Yes\n2: No\n3: Not sure" << endl;
    cin >> choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout << "\nInvalid input." << endl;
        sizeFunc(newDog);
        return;
    }
    switch(choice){
        case 1:
            newDog.goodWithAdults  = "Yes"; break;
        case 2:
            newDog.goodWithAdults = "No"; break;
        case 3:
            newDog.goodWithAdults = "Not sure"; break;
        default:
            cout << "Invalid input." << endl;
            goodWithAdultsFunc(newDog);
            return;
        }
}
void goodWithKidsFunc(Dogs &newDog){
    int choice;
    cout << "\nGood with Kids?\n1: Yes\n2: No\n3: Not sure" << endl;
    cin >> choice;
    if(cin.fail()){
        cin.clear();
        cin.ignore();
        cout << "\nInvalid input." << endl;
        sizeFunc(newDog);
        return;
    }
    switch(choice){
        case 1:
            newDog.goodWithKids  = "Yes"; break;
        case 2:
            newDog.goodWithKids = "No"; break;
        case 3:
            newDog.goodWithKids = "Not sure"; break;
        default:
            cout << "Invalid input." << endl;
            goodWithKidsFunc(newDog);
            return;
        }
}
int main(){
    unordered_map<string, Dogs> dogList;
    unordered_map<string, Room> roomList;
    Room* emptyRoom = nullptr;
    int input;
    vector<Room> firstVec(64);
    vector<vector<Room>> roomVec(8, vector<Room>(8));
    char c = 'A';
    int count = 1;
    for(int i = 0; i < 64; i++){
        if(i==0){}
        else if((count-1) % 8 == 0){
            c += 1;
            count = count/8;
        }firstVec.at(i).name = c + to_string(count);
        count++;
    }for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            roomVec.at(i).at(j) = firstVec.at(i*8+j);
        }
    }

    ifstream inFile("save.txt");
    string line;
    int m = 0, n = 0;
    while (getline(inFile, line)) {
        Dogs dog;
        Room room;
        dog.name = line;
        getline(inFile, line);
        dog.breed = line;
        getline(inFile, line);
        dog.size = line;
        getline(inFile, line);
        dog.age = stof(line);
        getline(inFile, line);
        dog.goodWithSmallDogs = line;
        getline(inFile, line);
        dog.goodWithLargeDogs = line;
        getline(inFile, line);
        dog.goodWithAdults = line;
        getline(inFile, line);
        dog.goodWithKids = line;
        getline(inFile, line);
        dog.room = line;

        for(int i = 0; i < roomVec.size(); i++){
            for(int j = 0; j < roomVec.at(i).size(); j++){
                if(roomVec.at(i).at(j).name == dog.room){
                    room.roomList.insert(make_pair(dog.name, dog));
                    room.name = dog.room;
                    roomVec.at(i).at(j) = room;
                } else if(dog.room == "FF"){
                    dogList.insert(make_pair(dog.name, dog));
                }
            }
        }
    }
    

    inFile.close();
    while(true){
        cout << "\nMake a selection\n1: Create a new dog\n2: See dogs not roomed\n3: See kennels\n(TESTING COMMAND: 4 to fill)\n5: Save data"  << endl;
        cin >> input;
        if(cin.fail()){
            cout << "\nInvalid input" << endl; 
            cin.clear(); 
            cin.ignore(); 
            continue;
        } 
        cin.ignore();
        vector<Dogs> test;
        if(input == 4){
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                Dogs testDogs;
                testDogs.name = "test" + to_string(i+10);
                roomVec.at(i).at(j).roomList.insert(make_pair(testDogs.name, testDogs));
                testDogs.name = "test" + to_string(i+200);
                roomVec.at(i).at(j).roomList.insert(make_pair(testDogs.name, testDogs));
                testDogs.name = "test" + to_string(i+3);
                roomVec.at(i).at(j).roomList.insert(make_pair(testDogs.name, testDogs));
                testDogs.name = "test" + to_string(i+4000);
                roomVec.at(i).at(j).roomList.insert(make_pair(testDogs.name, testDogs));
                testDogs.name = "test" + to_string(i+50000);
                roomVec.at(i).at(j).roomList.insert(make_pair(testDogs.name, testDogs));
                testDogs.name = "test" + to_string(i+6);
                roomVec.at(i).at(j).roomList.insert(make_pair(testDogs.name, testDogs));
                }
            }continue;
        }
        if(input == 1){
            Dogs newDog;
            cout << "\nEnter dog's name: " << endl;
            getline(cin, newDog.name);
            if(newDog.name.size() > 22){
                cout << "\nName is too long. Hit ENTER to continue" << endl;
                cin.ignore();
                continue;
            }
            cout << "\nBreed:" << endl;
            cin >> newDog.breed;
            cin.ignore();
            sizeFunc(newDog);
            cout << "\nAge: (use decimal 0.X for months)" << endl;
            cin >> newDog.age;
            if(cin.fail()){
                cout << "\nInvalid input" << endl; 
                cin.clear(); 
                cin.ignore(); 
                continue;
            } 
            cin.ignore();
            goodWithSmallDogsFunc(newDog);
            goodWithLargeDogsFunc(newDog);
            goodWithAdultsFunc(newDog);
            goodWithKidsFunc(newDog);
            dogList.insert(make_pair(newDog.name, newDog));
        } else if(input == 2){
            cout << "\nDog list:" << endl;
            for(auto const& [name, dog] : dogList){
                cout << name << endl;
            }
            cout << "\nEnter a dog's name to see it's info" << endl;
            string doggoName;
            getline(cin, doggoName);
            auto it = dogList.find(doggoName);

            if(it != dogList.end()){
                Dogs dog = it->second;
                printDogInfo(dog);
            } else {
                cout << "\nDog not found" << endl;
                }
            } else if(input == 3){
                char input1;
                while(true){
                    
                    printKennelMap();
                    cout << "Enter a kennel or enter 2 to go back" << endl; 
                    cin >> input1;
                    if(cin.fail() or ((!isalpha(input1) and input1 != '2')) and (input1 < 65 or input1 > 72) and (input1 < 97 or input1 > 104)){
                        cout << "\nInvalid input" << endl; 
                        cin.clear(); 
                        cin.ignore(); 
                        continue;
                    } 
                    if(input1 == '2') break;
                    addingDogs(roomVec, emptyRoom, dogList, toupper(input1));
                }
            } else if (input == 5){
                ofstream outFile("save.txt");
                if(outFile.is_open()){
                    for(const auto& dog : dogList){
                                outFile << dog.second.name << endl;
                                outFile << dog.second.breed << endl;
                                outFile << dog.second.size << endl;
                                outFile << dog.second.age << endl;
                                outFile << dog.second.goodWithSmallDogs << endl;
                                outFile << dog.second.goodWithLargeDogs << endl;
                                outFile << dog.second.goodWithAdults << endl;
                                outFile << dog.second.goodWithKids << endl; 
                                outFile << dog.second.room << endl;

                            }
                    for(int i = 0; i < roomVec.size(); i++){
                        for(int j = 0; j < roomVec.at(i).size(); j++){
                            for(const auto& dog : roomVec.at(i).at(j).roomList){
                                outFile << dog.second.name << endl;
                                outFile << dog.second.breed << endl;
                                outFile << dog.second.size << endl;
                                outFile << dog.second.age << endl;
                                outFile << dog.second.goodWithSmallDogs << endl;
                                outFile << dog.second.goodWithLargeDogs << endl;
                                outFile << dog.second.goodWithAdults << endl;
                                outFile << dog.second.goodWithKids << endl; 
                                outFile << dog.second.room << endl;

                            }
                        }
                    } outFile.close();
                }cout << "\nData saved" << endl;
            } else {
                cout << "Bad input" << endl;
            } 
        }
    }