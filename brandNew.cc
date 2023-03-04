#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


struct Dogs {
    string name;
    string breed;
    string size;
    float age;
    string goodWithSmallDogs;
    string goodWithLargeDogs;
    string goodWithAdults;
    string goodWithKids;
    string room;
};
struct Kennel{
    string name;
   //TODO int occupants;
    Kennel(const string& kennelName) : name(kennelName) {}
    unordered_map<string, Dogs> kennelMap;
};
struct Room{
    string name;
    unordered_map<string, Dogs> roomList;
    void printDogList(){
        for(auto const& [name, dog] : roomList){
            cout << name << endl;
        } 
    }
    vector<string> dogNames;
    void fillVec(){
        for(auto const& [name, dog] : roomList){
            dogNames.push_back(name);
        } 
    }
};

void roomDisplay(char roomLetter, vector<vector<Room>>& roomVec){
    int count = 0;
    Room rooms[8];
    for (int i = 0; i < 8; i++) {
        rooms[i] = roomVec.at(roomLetter - 65).at(i);
        rooms[i].fillVec();
    }
    for(int i = 0; i < 7; i++){
        if (count == 0){
        cout << "\n\n\tROOM " << rooms[0].name << "\t      |\t" << "     ROOM " << rooms[1].name << "\t     |\t" << "     ROOM " << rooms[2].name << "\t    |\t" << "     ROOM " << rooms[3].name << endl; 
        } else {
            string spaces[4];
            int length;
            for (int j = 0; j < 4; j++){
                length = rooms[j].dogNames.at(i-1).length();
               // cout << length << endl;
                spaces[j].append(22-length, ' ');
            }
            cout << rooms[0].dogNames.at(i-1) << spaces[0] <<  "|" << rooms[1].dogNames.at(i-1) << spaces[1] << "|" << rooms[2].dogNames.at(i-1) << spaces[2] << "|" << rooms[3].dogNames.at(i-1) << endl;
        } count++;
    }
    
    cout << "\nENTER 1 TO ADD A DOG TO THE KENNEL or PRESS 2 TO GO BACK" << endl;
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
                                        found = true;
                                        roomVec.at(i).at(j).roomList.emplace(doggoName, dog);
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
            } else if(input == 2) break;
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
            newDog.goodWithSmallDogs  = "Small"; break;
        case 2:
            newDog.goodWithSmallDogs = "Medium"; break;
        case 3:
            newDog.goodWithSmallDogs = "Large"; break;
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
    cout << "\nGood with Kids?\n1: Yes\n2: No\n3: not sure" << endl;
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

    
    while(true){
        cout << "\nMake a selection\n1: Create a new dog\n2: See dogs not roomed\n3: See kennels\n(TESTING COMMAND: 4 to fill)"  << endl;
        cin >> input;
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
            }
        }
    
        if(input == 1){
            Dogs newDog;
            cout << "\nEnter dog's name: " << endl;
            getline(cin, newDog.name);
            cout << "\nBreed:" << endl;
            cin >> newDog.breed;
            cin.ignore();
            sizeFunc(newDog);
            cout << "\nAge: (use decimal 0.X for months)" << endl;
            cin >> newDog.age;
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
                    if(input1 == '2') break;
                    addingDogs(roomVec, emptyRoom, dogList, toupper(input1));
                }
            }
        }
    }

 