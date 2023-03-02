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
};
void roomDisplay(char);

void createRoom(Room& room, string name, int num, unordered_map<string, Dogs> roomMap){
    room.name = name + to_string(num);
    room.roomList   = roomMap;
}
Room returnRoom(char c, int n, vector<vector<Room>>& roomVec){
    roomDisplay('A');
}

void roomDisplay(char roomLetter){
    cout << "\n\n ROOM " << roomLetter << "1\t|\tROOM " << roomLetter << "2\t\t|\tROOM " << roomLetter << "3\t\t|\tROOM " << roomLetter << "4\n\n" << endl;
    cout << "--------------------------------------------------------------------------------------\n" << endl;
    cout << "\n ROOM " << roomLetter << "5\t|\tROOM " << roomLetter << "6\t\t|\tROOM " << roomLetter << "7\t\t|\tROOM " << roomLetter << "8\n\n" << endl;
    cout << "ENTER 1 TO ADD A DOG TO THE KENNEL or PRESS 2 TO GO BACK" << endl;
}
void addingDogs(vector<vector<Room>>& roomVec, Room* emptyRoom, unordered_map<string, Dogs> &dogList, char roomLetter){
    while (true){
        roomDisplay(roomLetter);
        int input;
        cin >> input;
        cin.ignore();
        if(input == 1){
            cout << "Dog(s) currently not assigned rooms: " << endl;
                for(auto const& [name, dog] : dogList){
                    cout << name << endl;
                } 
                cout << "Enter a dog's name to put into a room" << endl;                    
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
                        cout << "Inserted " << doggoName << " into room " << emptyRoom->name << endl;
                    } else {
                        cout << "No empty rooms. Enter 1 to add " << doggoName << " to a room anyways. Enter 2 to go back" << endl;
                        int choice;
                        cin >> choice;
                        if(choice == 1){
                            string s;
                            cout << "Enter which room you'd like to add " << doggoName << " to or Enter 2 to go back" << endl;
                            reset:
                            cin >> s;
                            for(char& c : s) c = toupper(c);
                            if(s == "2") continue;
                            for(int i = 0; i < 8; i++){
                                for(int j = 0; j < 8; j++){
                                    if(roomVec.at(i).at(j).name == s){
                                        roomVec.at(i).at(j).roomList.emplace(doggoName, dog);
                                        dogList.erase(doggoName);
                                        cout << "Successfully added " << doggoName << " to room " << roomVec.at(i).at(j).name << endl;
                                    }
                                }
                            }
                            cout << "Misentered room name! Enter a room or Enter 2 to go back" << endl;
                            goto reset;
                        }
                    }
                } else { 
                    cout << "Dog not found" << endl;             
                } 
            } else if(input == 2) break;
    }
}
                /*
                    cout << "Enter the # of which kennel this dog should go" << endl;
                    cin >> choice;
                    if(choice == 1){
                        emptyRoom = &kennel1;
                        emptyRoom->kennelMap.emplace(doggoName, dog);
                        dogList.erase(doggoName);
                    cout << "Inserted " << doggoName << " into kennel " << choice << endl;
                    } else if(choice == 2){
                        emptyRoom = &kennel2;
                        emptyRoom->kennelMap.emplace(doggoName, dog);
                        dogList.erase(doggoName);
                    cout << "Inserted " << doggoName << " into kennel " << choice << endl;
                    } else if(choice == 3){
                        emptyRoom = &kennel3;
                        emptyRoom->kennelMap.emplace(doggoName, dog);
                        dogList.erase(doggoName);
                    cout << "Inserted " << doggoName << " into kennel " << choice << endl;
                    } else if(choice == 4){
                        emptyRoom = &kennel4;
                        emptyRoom->kennelMap.emplace(doggoName, dog);
                        dogList.erase(doggoName);
                    cout << "Inserted " << doggoName << " into kennel " << choice << endl;
                    } else if(choice == 5){
                        emptyRoom = &kennel5;
                        emptyRoom->kennelMap.emplace(doggoName, dog);
                        dogList.erase(doggoName);
                    cout << "Inserted " << doggoName << " into kennel " << choice << endl;
                    } else if(choice == 6){
                        emptyRoom = &kennel6;
                        emptyRoom->kennelMap.emplace(doggoName, dog);
                        dogList.erase(doggoName);
                    cout << "Inserted " << doggoName << " into kennel " << choice << endl;
                    } else if(choice == 7){
                        emptyRoom = &kennel7;
                        emptyRoom->kennelMap.emplace(doggoName, dog);
                        dogList.erase(doggoName);
                    cout << "Inserted " << doggoName << " into kennel " << choice << endl;
                    } else if(choice == 8){
                        emptyRoom = &kennel8;
                        emptyRoom->kennelMap.emplace(doggoName, dog);
                        dogList.erase(doggoName);
                    cout << "Inserted " << doggoName << " into kennel " << choice << endl;
                    }
                */


void printDogsInRoom(Room room){
    cout << "Room " << room.name << ":" << endl;
    for(auto& key : room.roomList)
    cout << key.first << endl;
}


void printKennelMap(){
cout << "\n A\t|\tB\t|\tC\t|\tD\n" << endl;
cout << "---------------------------------------------------\n" << endl;
cout << " E\t|\tF\t|\tG\t|\tH\n" << endl;
}
void printDogInfo(Dogs d){
    cout << d.name << "'s info:\n" << endl;
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
    string sizeInput;
    cout << "Size: (small, medium, large)" << endl;
    getline(cin, sizeInput);
    if(sizeInput == "small"){
            newDog.size = sizeInput;
        } else if(sizeInput == "medium"){
            newDog.size = sizeInput;
        } else if(sizeInput == "large"){
            newDog.size = sizeInput;
        } else {
            cout << "Invalid input. Please enter small, medium, or large:" << endl;
            sizeFunc(newDog);
        }
}
void goodWithSmallDogsFunc(Dogs &newDog){
    string sizeInput;
    cout << "Good with small dogs? (yes, no, not sure)" << endl;
    getline(cin, sizeInput);
    if(sizeInput == "no"){
            newDog.goodWithSmallDogs = sizeInput;
        } else if(sizeInput == "yes"){
            newDog.goodWithSmallDogs = sizeInput;
        } else if(sizeInput == "not sure"){
            newDog.goodWithSmallDogs = sizeInput;
        } else {
            cout << "Invalid input. Please enter yes, no, or not sure:" << endl;
            goodWithSmallDogsFunc(newDog);
        }
}
void goodWithLargeDogsFunc(Dogs &newDog){
    string sizeInput;
    cout << "Good with large dogs? (yes, no, not sure)" << endl;
    getline(cin, sizeInput);
    if(sizeInput == "no"){
            newDog.goodWithLargeDogs = sizeInput;
        } else if(sizeInput == "yes"){
            newDog.goodWithLargeDogs = sizeInput;
        } else if(sizeInput == "not sure"){
            newDog.goodWithLargeDogs = sizeInput;
        } else {
            cout << "Invalid input. Please enter yes, no, or not sure:" << endl;
            goodWithLargeDogsFunc(newDog);
        }
}
void goodWithAdultsFunc(Dogs &newDog){
    string sizeInput;
    cout << "Good with people? (yes, no, not sure)" << endl;
    getline(cin, sizeInput);
    if(sizeInput == "no"){
            newDog.goodWithAdults = sizeInput;
        } else if(sizeInput == "yes"){
            newDog.goodWithAdults  = sizeInput;
        } else if(sizeInput == "not sure"){
            newDog.goodWithAdults = sizeInput;
        } else {
            cout << "Invalid input. Please enter yes, no, or not sure:" << endl;
            goodWithAdultsFunc(newDog);
        }
}
void goodWithKidsFunc(Dogs &newDog){
    string sizeInput;
    cout << "Good with Kids? (yes, no, not sure)" << endl;
    getline(cin, sizeInput);
    if(sizeInput == "no"){
            newDog.goodWithKids  = sizeInput;
        } else if(sizeInput == "yes"){
            newDog.goodWithKids = sizeInput;
        } else if(sizeInput == "not sure"){
            newDog.goodWithKids = sizeInput;
        } else {
            cout << "Invalid input. Please enter yes, no, or not sure:" << endl;
            goodWithKidsFunc(newDog);
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
        cout << "ENTER 1 TO ADD A DOG or PRESS 2 TO SEE DOGS or PRESS 3 TO SEE KENNELS (TESTING COMMAND: 4 to fill)"  << endl;
        cin >> input;
        cin.ignore();
        vector<Dogs> test;
        if(input == 4){
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                Dogs testDogs;
                testDogs.name = "test" + to_string(i);
                roomVec.at(i).at(j).roomList.insert(make_pair(testDogs.name, testDogs));
                }
            }
        }
    
        if(input == 1){
            Dogs newDog;
            cout << "Enter dog's name: " << endl;
            getline(cin, newDog.name);
/*            cout << "Breed:" << endl;
            cin >> newDog.breed;
            cin.ignore();
            sizeFunc(newDog);
            cout << "Age: (use decimal 0.X if < 1 year)" << endl;
            cin >> newDog.age;
            cin.ignore();
            goodWithSmallDogsFunc(newDog);
            goodWithLargeDogsFunc(newDog);
            goodWithAdultsFunc(newDog);
            goodWithKidsFunc(newDog);
            */
            dogList.insert(make_pair(newDog.name, newDog));

        } else if(input == 2){
            cout << "Dog list:" << endl;
            for(auto const& [name, dog] : dogList){
                cout << name << endl;
            }
            cout << "Enter a dog's name to see it's info" << endl;
            string doggoName;
            getline(cin, doggoName);
            auto it = dogList.find(doggoName);

            if(it != dogList.end()){
                Dogs dog = it->second;
                printDogInfo(dog);
            } else {
                cout << "Dog not found" << endl;
                }

            } else if(input == 3){
                char input1;
                while(true){
                    
                    printKennelMap();
                    cout << "ENTER WHICH KENNEL TO VIEW or ENTER 2 TO GO BACK" << endl; 
                    cin >> input1;
                    if(input1 == '2') break;
                    addingDogs(roomVec, emptyRoom, dogList, toupper(input1));
                }
            }
        }
    }

 