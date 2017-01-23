/*****************************************************************************************************************
 *       Array and Linked List Implementations of a City Database
 *           Program Designed and Documented by Mathew Jackson
 *                  Project 1 for Data Structures
 *
 *        // ARRAY:
 *          // Functionality
 *            // Insert
 *            // Delete by name or coordinates
 *            // Search by name or coordinates
 *            // Function to print out the names of cities in a given distance
 *            // Print all listings
 *
 *        // LINKED LIST:
 *          // Functionality
 *            // Insert
 *            // Search by name or coordinates
 *            // Delete by name or coordinates
*             // Function to print out the names of cities in a given distance
 *            // Print all listings
 *
*******************************************************************************************************************/
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <sstream>
#include <fstream>
#include <math.h>
#include <cmath>
#include <time.h>
#include <string>
#include <algorithm>

using namespace std;

//Constants
const int MAX = 1000; // Change this value to 100 for larger set of data

const float radiusMiles = 3963.191;
//Main Function Prototypes
//-------------------- //
int printUserInterface();
void arrayDataBase();
void linkedlistDataBase();
float deg_to_radians(float);
float rad2deg(float);
//-------------------- //

//File variables //
//----------------------//
ifstream oldtestData;
ifstream linkedTestData;
ofstream newtestData;
//----------------------//

//Array Class//
class ArrayImplementation{
    public:
        ArrayImplementation(){
            sizeOfArray = 0;
            spacesLeft = MAX;
        }
        string cityName[MAX];
        float cityLongitude[MAX];
        float cityLatitude[MAX];

        int sizeOfArray;
        int spacesLeft; // how many more spots in the array are left
        int lastPos;
        int curPosition;
       //On Start up when choosing array-implementation
        void fillArray(string[]);// parameter takes an array of data from TestFile.txt
        // To rearrange array after deletions
        void arrangeArray();
        // Basic functionality
        void insertCity(); //COMPLETE -- error handling and duplicate detection

        int searchByName(bool, bool); // COMPLETE -- I made it so it is not case-sensitive
        int searchByCoord(bool);// COMPLETE -- Fixed comparison-of-floats problem with error-handling fabs() functions

        void deleteCityByName();// COMPLETE -- TODO::May need to check through for error-handling
        void deleteCityByCoordinates();// COMPLETE

        void printCitiesInDestination();
        void printAll();// COMPLETE -- TODO:: Need to get rid of the empty entries

};
// Node Structure
class Node{

private:
    string cityName;
    float cityLatitude;
    float cityLongitude;
    string fromFileStream;
public:
    friend class LinkedList;
    Node* nextN;

    Node(string name, float latitude, float longitude){
        cityName = name;
        cityLatitude = latitude;
        cityLongitude = longitude;
    }


};
// Linked List Class
class LinkedList{
    public:
        LinkedList(){
            root = NULL;
            head = NULL;
            filled = false;
        }
        ~LinkedList(){
            delete root;
            delete head;
        }

        bool filled; // Used for determining if the linked list has been filled from previous data

        //Pointers
        Node* root;
        Node* head;
        // Functions
        void insertCity(); // COMPLETE : TODO: Verify city does not already exist
        void insertCity(string); // COMPLETE -- Used for importing previous data

        void searchByName(); // COMPLETE
        void searchByCoord(); // COMPLETE

        void deleteCityByName(); // COMPLETE
        void deleteCityByCoordinates(); // COMPLETE

        void printCitiesInDestination(); // COMPLETE
        void printAll();// COMPLETE


};


int main(void)
{
    //Program Starter
    while(printUserInterface()!= 0);

    return 0;
}

int printUserInterface(){
    char usersChoiceChar; // Choosing array or linked list
    cout<<"*************************************\n"
        <<"Implementation Options:\n"
        <<"A.Use an array-based list implementation\n"
        <<"B.Use a linked-list implementation\n"
    <<endl;

    cout<<"Your Implementation: ";

    bool valid = false;
    while(!valid){
        cin>>usersChoiceChar;
        if(cin.fail()) //cin.fail() checks to see if the value in the cin
					//stream is the correct type, if not it returns true,
					//false otherwise.
            {
                cin.clear(); //This corrects the stream.
                cin.ignore(); //This skips the left over stream data.
                cout << "Please enter a A or B only only." << endl;
                valid = false;
		}else{

            valid = true;
		}
    }
    usersChoiceChar = toupper(usersChoiceChar);

    switch(usersChoiceChar){
        case 'A':
                arrayDataBase();
                return 0;
            break;
        case 'B':
                linkedlistDataBase();
                return 0;
            break;
        default:
            cout<<"Incorrect Choice. Please Select again"<<endl;
            return 1;
    }

}
/**********************************************ARRAY SECTION********************/
void arrayDataBase(){
    string line;
    // to arrange the file
    string lineArray[MAX];
    //actual db of cities and their coordinates *City/Latitude/Longitude
    string cityDB[MAX];

    ArrayImplementation citiesDB;

    //Open files
    oldtestData.open("TestData.txt");
    newtestData.open("newTestData.txt");

    int i = 0; //to count the index of cities in the string array
    if(oldtestData.is_open()){

        while(getline(oldtestData, line)){
              if(!line.empty()){
                lineArray[i++] = line;
              }
        }
    }else{
        cout<<"Cannot open file"<<endl;
    }

    //Pump the removed blank line data into a temp array
    for(int n = 1; n < 20; n++ ){
        newtestData << lineArray[n] << "\n";

    }
     //Filling the cityDB and removing header from datafile
    for(int j = 1; j <= 20; j++){
        cityDB[j-1] = lineArray[j];

    }
    //Initialize the current set of data
    citiesDB.fillArray(cityDB);

    int usersChoiceInt;
    cout<<"Operation Options:\n"
                <<"1. Insert a record\n"
                <<"2. Search for a record by name\n"
                <<"3. Search for a record by coordinate\n"
                <<"4. Delete a record by name\n"
                <<"5. Delete a record by coordinate\n"
                <<"6. Print records within a given distance of a specified location\n"
                <<"7. Print all records\n"
                <<"8. Exit"
    <<endl;

    while(usersChoiceInt != 8){
        cout<<"Your Operation: ";

        bool valid = false;
        while(!valid){
            cin>>usersChoiceInt;
            if(cin.fail()) //cin.fail() checks to see if the value in the cin
                            //stream is the correct type, if not it returns true,
                            //false otherwise.
                {
                    cin.clear(); //This corrects the stream.
                    cin.ignore(); //This skips the left over stream data.
                    cout << "Please enter a single number only" << endl;
                    valid = false;
            }else{

                valid = true;
            }
        }
        switch(usersChoiceInt){
            case 1:
                clock_t c1, c2;
                c1 = clock();
                citiesDB.insertCity();
                c2 = clock();
                long double diff;
                diff = (long double)c2 - (long double)c1;
                long double secs;
                secs = diff/CLOCKS_PER_SEC;
                cout<<"Execution time: "<<secs<<endl;
            break;
            case 2:

                c1 = clock();
                citiesDB.searchByName(false, false); // false because we don't want to delete the city
                c2 = clock();
                diff = 0;
                diff = (long double)c2 - (long double)c1;
                secs = 0;
                secs = diff/CLOCKS_PER_SEC;
                cout<<"Execution time: "<<secs<<endl;
            break;
            case 3:
                c1 = clock();
                citiesDB.searchByCoord(false);// false because we don't want to delete the city
                c2 = clock();
                diff = 0;
                diff = (long double)c2 - (long double)c1;
                secs = 0;
                secs = diff/CLOCKS_PER_SEC;
                cout<<"Execution time: "<<secs<<endl;
            break;
            case 4:
                c1 = clock();
                citiesDB.deleteCityByName();
                c2 = clock();
                diff = 0;
                diff = (long double)c2 - (long double)c1;
                secs = 0;
                secs = diff/CLOCKS_PER_SEC;
                cout<<"Execution time: "<<secs<<endl;
            break;
            case 5:
                c1 = clock();
                citiesDB.deleteCityByCoordinates();
                c2 = clock();
                diff = 0;
                diff = (long double)c2 - (long double)c1;
                secs = 0;
                secs = diff/CLOCKS_PER_SEC;
                cout<<"Execution time: "<<secs<<endl;
            break;
            case 6:
                c1 = clock();
                citiesDB.printCitiesInDestination();
                c2 = clock();
                diff = 0;
                diff = (long double)c2 - (long double)c1;
                secs = 0;
                secs = diff/CLOCKS_PER_SEC;
                cout<<"Execution time: "<<secs<<endl;
            break;
            case 7:
                c1 = clock();
                citiesDB.printAll();
                c2 = clock();
                diff = 0;
                diff = (long double)c2 - (long double)c1;
                secs = 0;
                secs = diff/CLOCKS_PER_SEC;
                cout<<"Execution time: "<<secs<<endl;
            break;
            case 8:
                cout<<"Bye Bye"<<endl;
                break;
            default:
                cout<<"Non-supported choice, try again"<<endl;
        }
    }

    /*/DEBUG AREA---------------------------------------------//
    for(int j = 0; j < MAX; j++){

        cout<<citiesDB.cityName[j]<<endl;;

    }
    for(int j = 0; j < MAX; j++){

        cout<<citiesDB.cityLatitude[j]<<endl;;

    }
    for(int k = 0; k < MAX; k++){

        cout<<citiesDB.cityLongitude[k]<<endl;

    }

    cout<<citiesDB.sizeOfArray<<endl;
    cout<<citiesDB.spacesLeft<<endl;
    //DEBUG END ----------------------------------------------/*/

    //close file
    newtestData.close();
    oldtestData.close();

}
/**********************************************END ARRAY SECTION********************/
/**********************************************LINKED LIST SECTION********************/
void linkedlistDataBase(){
    LinkedList* citiesDB = new LinkedList();

    string line;
    string lineArray[MAX];
    //Open files
    oldtestData.open("TestData.txt");
    newtestData.open("newTestData.txt");


   int i = 0; //to count the index of cities in the string array
    if(oldtestData.is_open()){

        while(getline(oldtestData, line)){
              if(!line.empty()){
                lineArray[i++] = line;
              }
        }
    }else{
        cout<<"Cannot open file"<<endl;
    }

    //Pump the removed blank line data into a temp array
    for(int n = 1; n < 20; n++ ){
        newtestData << lineArray[n] << "\n";

    }
    newtestData.close();
    linkedTestData.open("newTestData.txt");

    if(linkedTestData.is_open()){
        while(getline(linkedTestData, line)){
            if(!line.empty()){
                citiesDB->insertCity(line);
            }

        }
    }
    int usersChoiceInt;
    cout<<"Operation Options:\n"
                <<"1. Insert a record\n"
                <<"2. Search for a record by name\n"
                <<"3. Search for a record by coordinate\n"
                <<"4. Delete a record by name\n"
                <<"5. Delete a record by coordinate\n"
                <<"6. Print records within a given distance of a specified location\n"
                <<"7. Print all records\n"
                <<"8. Exit"
    <<endl;

    while(usersChoiceInt != 8){
        cout<<"Your Operation: ";

        bool valid = false;
        while(!valid){
            cin>>usersChoiceInt;
            if(cin.fail()) //cin.fail() checks to see if the value in the cin
                            //stream is the correct type, if not it returns true,
                            //false otherwise.
                {
                    cin.clear(); //This corrects the stream.
                    cin.ignore(); //This skips the left over stream data.
                    cout << "Please enter a single number only" << endl;
                    valid = false;
            }else{

                valid = true;
            }
        }
        switch(usersChoiceInt){
            case 1:
                citiesDB->insertCity();
            break;
            case 2:
                citiesDB->searchByName();
            break;
            case 3:
                citiesDB->searchByCoord();
            break;
            case 4:
                citiesDB->deleteCityByName();
            break;
            case 5:
                citiesDB->deleteCityByCoordinates();
            break;
            case 6:
                citiesDB->printCitiesInDestination();
            break;
            case 7:
                citiesDB->printAll();
            break;
            case 8:
                cout<<"Bye Bye"<<endl;
                break;
            default:
                cout<<"Non-supported choice, try again"<<endl;
        }
    }

    //close file

    oldtestData.close();

}
/***********************************************END LINKED LIST SECTION*****************/
/*LINK-LIST FUNCTIONS */
void LinkedList::insertCity(){
    string usersName;
    float usersLat;
    float usersLong;
    cout<<"Enter name of city: ";
    cin>>usersName;
    cout<<"Enter x-coordinate of "<<usersName<<": ";
    cin>>usersLat;
    cout<<"Enter y-coordinate of "<<usersName<<": ";
    cin>>usersLong;
    // If the linked list is empty
    if(this->root == NULL){
        root = new Node(usersName, usersLat, usersLong);
        root->nextN = NULL;

        head = root;
        head->cityName = usersName;
        head->cityLatitude = usersLat;
        head->cityLongitude = usersLong;
        return;
    }
    head = root;
    //traverse through the list until you get to a node with a NULL pointer for nextN
        if(head != NULL){
            while(head->nextN != NULL){

                   head = head->nextN;

            }
        }
    // add a new node to the list

    head->nextN = new Node(usersName, usersLat, usersLong);
    head = head->nextN;
    head->nextN = NULL;

    // point back to the beginning
    head = root;
    cout<<"Entry Successfully added to Linked-List DataBase"<<endl;
/*
    // Make sure the conductor is pointing to something
    if(head != 0){
        // Print the first node
        cout<<head->getData()<<endl;

        //print the linked list
        while(head->nextN != 0){

            head = head->nextN;
            cout<<head->getData()<<endl;

        }
    }
    delete conductor;
    delete root;
    */

}
void LinkedList::insertCity(string line){
// initialize the root node and the head...the head is the "pointer" to the current node

    string usersName;
    string debug;
    float usersLat;
    float usersLong;

    // Extract information
    std::string::size_type colonPos = line.find(":");
    std::string::size_type commaPos = line.find(",");

    usersName = line.substr(0, colonPos);
    usersLat = atof(line.substr(colonPos+1, 10).c_str());
    usersLong = atof(line.substr(commaPos + 1).c_str());
    // If the linked list is empty
    if(this->root == NULL){
        root = new Node(usersName, usersLat, usersLong);
        root->nextN = NULL;

        head = root;
        return;
    }
    //traverse through the list until you get to a node
        if(head != NULL){
            while(head->nextN != NULL){

                   head = head->nextN;

            }
        }
    // add a new node to the list

    head->nextN = new Node(usersName, usersLat, usersLong);
    head = head->nextN;
    head->nextN = NULL;

    // point back to the beginning
    head = root;

}
void LinkedList::searchByName(){
    string usersCityName;

    cout<<"Enter name of city: "<<endl;
    cin>>usersCityName;
    head = root;
    while(head->nextN != NULL){
        if(head->cityName == usersCityName){
            cout<<"Found City!\n"<<"x-coordinates: "<<head->cityLatitude<<"\n"<<"y-coordinates: "<<head->cityLongitude<<endl;
            return;
        }
        head = head->nextN;
    }
    cout<<"Could not find city. Try another name."<<endl;

}
void LinkedList::searchByCoord(){
    float usersCityLatitude;
    float usersCityLongitude;

    cout<<"Enter x-coordinate of city: "<<endl;
    cin>>usersCityLatitude;
    cout<<"Enter y-coordinate of city: "<<endl;
    cin>>usersCityLongitude;

    head = root;
    while(head->nextN != NULL){
        if(fabs(head->cityLatitude - usersCityLatitude) < 0.0001 && fabs(head->cityLongitude - usersCityLongitude) < 0.0001){
            cout<<"Found City! It is "<<head->cityName<<endl;
            return;
        }
        head = head->nextN;
    }
    cout<<"Could not find city. Check your coordinates!"<<endl;

}
void LinkedList::deleteCityByName(){
    string usersCityName;
    Node* tempNode; // to hold address of previous node of deletion
    Node* prevNode;
    cout<<"Enter name of city you want to delete: "<<endl;
    cin>>usersCityName;

    head = root;
    tempNode = NULL;
    prevNode = root;
    while(head != NULL && prevNode->nextN != NULL){

        if(head->cityName == usersCityName){
            while(prevNode->nextN != NULL && prevNode->nextN != head){
                    prevNode = prevNode->nextN;
            }

                tempNode = head;
                head = tempNode->nextN;
                prevNode->nextN = head;
                delete tempNode;
                cout<<"Deletion Successful!"<<endl;
                return;
        }

        head = head->nextN;

    }
    tempNode = NULL;
    prevNode = NULL;
    free(tempNode);
    free(prevNode);
    cout<<"Could not find city. Try another name."<<endl;

}
void LinkedList::deleteCityByCoordinates(){
    float usersCityLat;
    float usersCityLong;
    Node* tempNode;
    Node* prevNode;
    cout<<"Enter x-coordinate of city you want to delete: ";
    cin>>usersCityLat;

    cout<<"Enter y-coordinate of city you want to delete: ";
    cin>>usersCityLong;

    head = root;
    tempNode = NULL;
    prevNode = root;
    while(head != NULL && prevNode->nextN != NULL){
        //If deletion is at the top of the list
        if(fabs(usersCityLat - head->cityLatitude) < 0.0001 && fabs(usersCityLong - head->cityLongitude) < 0.0001){

            if(head == root){
                tempNode = root;
                root = root->nextN;

                delete tempNode;

                cout<<"Deletion Successful!"<<endl;
                return;

            }else
            {
                while(prevNode->nextN != NULL && prevNode->nextN != head){
                        prevNode = prevNode->nextN;
                }

                    tempNode = head;
                    head = tempNode->nextN;
                    prevNode->nextN = head;
                    cout<<tempNode->cityName<<endl;
                    delete tempNode;

                    cout<<"Deletion Successful!"<<endl;
                    return;
            }
        }

        head = head->nextN;
    }
    tempNode = NULL;
    prevNode = NULL;
    free(tempNode);
    free(prevNode);
    cout<<"Could not find city. Try another name."<<endl;
}
void LinkedList::printCitiesInDestination(){
    /// TODO: convert this to linked list...then you're done!
    string usersCity;
    bool foundCity = false;
    float usersLatitude;
    float usersLongitude;

    float usersDistance;
    cout<<"Enter the city you want to find cities around: ";
    cin>>usersCity;

    head = root;
    while(head != NULL){

        if(head->cityName == usersCity){
            cout<<"Found city!"<<endl;
            usersLongitude = head->cityLongitude;
            usersLatitude = head->cityLatitude;
            foundCity = true;
        }
        head = head->nextN;
    }
    if(!foundCity){
        cout<<"Could not find city"<<endl;
        return;
    }
    cout<<"What is the distance? ";
    cin>>usersDistance;

    if(usersDistance == 0){
            cout<<"That would be the city's location. Please try again."<<endl;
            return;
    }

    float distance = 0;
    float e;

    foundCity = false;
    head = root;
    // Formula to calculate cities in a given distance on Earth
    while(head != NULL){
        e = acos(sin(deg_to_radians(usersLatitude))*sin(deg_to_radians(head->cityLatitude)) + cos(deg_to_radians(usersLatitude))*cos(deg_to_radians(head->cityLatitude))*cos(deg_to_radians(head->cityLongitude) - deg_to_radians(usersLongitude)));

        distance = e*radiusMiles;

        if(distance <= usersDistance && usersDistance != 0 && distance > 0){
            cout<<"Name: "<<head->cityName<<" | Distance: "<<distance<<endl;
            foundCity = true;
        }
        head = head->nextN;
    }

    if(foundCity != true){
        cout<<"No cities found within that given distance"<<endl;
        cout<<"Distance: "<<distance<<" | "<<"Users chosen distance: "<<usersDistance<<endl;

    }
}
void LinkedList::printAll(){
    head = root;
    cout<<"City | "<<"Latitude | "<<"Longitude"<<endl;
    while(head->nextN != NULL){
        cout<<head->cityName<<": "<<head->cityLatitude<<", "<<head->cityLongitude<<endl;
        head = head->nextN;
    }
    cout<<head->cityName<<": "<<head->cityLatitude<<", "<<head->cityLongitude<<endl;

    head = root;
}

/* ARRAY CLASS FUNCTIONS */

void ArrayImplementation::fillArray(string dataArray[MAX]){

    for(int i = 0; i < MAX; i++){

        std::string::size_type colonPos = dataArray[i].find(":");
        std::string::size_type commaPos = dataArray[i].find(",");

        cityName[i] = dataArray[i].substr(0, colonPos);
        cityLatitude[i] = atof(dataArray[i].substr(colonPos+1, 10).c_str());
        cityLongitude[i] = atof(dataArray[i].substr(commaPos + 1).c_str());
    }
}
void ArrayImplementation::arrangeArray(){
    //TODO: shift an unbalanced array back to normal
    for(int i = 0; i < MAX - 1; i++){
        if(cityName[i] == "" && cityName[i+1] != ""){
            cityName[i] = cityName[i+1];
            cityLongitude[i] = cityLongitude[i+1];
            cityLatitude[i] = cityLatitude[i+1];
        }
    }
}
void ArrayImplementation::insertCity(){
    int counter = 0;
    int i = 0; //cursor for while loop below
    while(this->cityLatitude[i] != 0){
        counter++;
        this->sizeOfArray++;
        i++;
    }
    this->lastPos = counter;
    cout<<"Last position is: "<<lastPos<<endl;
    string usersCityName;
    float usersLat;
    float usersLong;

    //Enter city name
    cout<<"Enter name of the city: ";
    cin>>usersCityName;

    // Check if the city name already exists
    for(int i = 0; i < MAX; i++){
            if(usersCityName == this->cityName[i]){
                cout<<"City already exists in this Database. No need to enter it again."<<endl;
                return;
            }
    }

    this->cityName[this->lastPos] = usersCityName;

    //Enter city latitude
    cout<<"Enter x-coordinate of the city: ";
    bool valid = false;

    while(!valid){
        cin>>usersLat;
        if(cin.fail()) //cin.fail() checks to see if the value in the cin
					//stream is the correct type, if not it returns true,
					//false otherwise.
            {
                cin.clear(); //This corrects the stream.
                cin.ignore(); //This skips the left over stream data.
                cout << "Please enter a float/integer only." << endl;
                valid = false;
		}else{
            valid = true;
		}
    }


    this->cityLatitude[this->lastPos] = usersLat;


    //Enter city longitude
    cout<<"Enter y-coordinate of the city: ";

    valid = false;

    while(!valid){
        cin>>usersLong;
        if(cin.fail()) //cin.fail() checks to see if the value in the cin
					//stream is the correct type, if not it returns true,
					//false otherwise.
            {
                cin.clear(); //This corrects the stream.
                cin.ignore(); //This skips the left over stream data.
                cout << "Please enter a float/integer only." << endl;
                valid = false;
		}else{
            valid = true;
		}
    }

    // Make sure coordinates do not already exist
    for(int j = 0; j < MAX; j++){
            if(usersLong == this->cityLongitude[j] && usersLat == this->cityLongitude[j]){
                cout<<"City already exists in that location in the Database. Perhaps you have the wrong coordinates?"<<endl;
                return;
            }
    }
    this->cityLongitude[this->lastPos] = usersLong;

    cout<<"Successfully added entry."<<endl;
    // Update everything
    this->sizeOfArray++;
    this->spacesLeft = MAX - this->sizeOfArray;
    this->lastPos++;
}
int ArrayImplementation::searchByName(bool isDeleting, bool distanceSearch){

    string usersCity;
    string UPPERCASENAME[MAX];

    if(!isDeleting)
        cout<<"Enter name of the city to be Searched: ";
    else if(distanceSearch){
        cout<<"Enter name of the specified location: ";
        cin>>usersCity;
        }
    bool valid = false;

    while(!valid){
        cin>>usersCity;
        if(cin.fail()) //cin.fail() checks to see if the value in the cin
					//stream is the correct type, if not it returns true,
					//false otherwise.
            {
                cin.clear(); //This corrects the stream.
                cin.ignore(); //This skips the left over stream data.
                cout << "Please enter a city name only." << endl;
                valid = false;
		}else{

            valid = true;
		}
    }

    // convert all the letters in the string to upper case
    transform(usersCity.begin(), usersCity.end(),usersCity.begin(), ::toupper );

    // now set all of the characters in the strings of the cityName array to a temporary array for comparison
    for(int h = 0; h < MAX; h++){
            UPPERCASENAME[h]= cityName[h];
            transform(UPPERCASENAME[h].begin(), UPPERCASENAME[h].end(), UPPERCASENAME[h].begin(), ::toupper);
    }
    // Linear search
    bool found = false;
    for(int i = 0; i < MAX; i++){
            if(usersCity == UPPERCASENAME[i]){
                cout<<"Found the city!\nIt is at index: "<<i<<" of Data Array!"<<endl;
                cout<<"coordinates are: x = "<<cityLatitude[i]<<" | y = "<<cityLongitude[i]<<endl;
                return i;
            }
    }
    if(!found){
        cout<<"Could not retrieve city! Check your spelling!"<<endl;
        return 55;
    }
    return 56;
}
int ArrayImplementation::searchByCoord(bool deleteCity){

    // check which functionality the search will do
    if(deleteCity){
        cout<<"Enter the x-coordinate of the city you want to delete: ";
    }else{
        cout<<"Enter the x-coordinate of the city you want to find: ";
    }
    float usersCityX;
    bool valid = false;

    while(!valid){
        cin>>usersCityX;
        if(cin.fail()) //cin.fail() checks to see if the value in the cin
					//stream is the correct type, if not it returns true,
					//false otherwise.
            {
                cin.clear(); //This corrects the stream.
                cin.ignore(); //This skips the left over stream data.
                cout << "Please enter a float/int only." << endl;
                valid = false;
		}else{

            valid = true;
		}
    }

    bool xTrue = false;
    for(int i = 0; i < MAX; i++){
        if(fabs(cityLatitude[i] - usersCityX) < 0.0001){
            xTrue = true;
            cout<<"HIT!!!!"<<endl;
        }

    }

    if(deleteCity){
        cout<<"Enter the y-coordinate of the city you want to delete: ";
    }else{
        cout<<"Enter the y-coordinate of the city you want to find: ";
    }
    float usersCityY;
    valid = false;

    while(!valid){
        cin>>usersCityY;
        if(cin.fail()) //cin.fail() checks to see if the value in the cin
					//stream is the correct type, if not it returns true,
					//false otherwise.
            {
                cin.clear(); //This corrects the stream.
                cin.ignore(); //This skips the left over stream data.
                cout << "Please enter a float/int only." << endl;
                valid = false;
		}else{

            valid = true;
		}
    }

    bool yTrue = false;
    int index;
    for(int n = 0; n < MAX - 1; n++){
        if(fabs(usersCityY - cityLongitude[n]) < 0.0001){
            cout<<"HIT!!!!"<<endl;
            index = n;
            yTrue = true;
        }
    }
    if(xTrue && yTrue && deleteCity){
        cout<<"Deleting city at index "<<index<<" of the Data Array!"<<endl;
        return index;
    }
    else if(xTrue && yTrue && !deleteCity){
        cout<<"Found the city!\nIt is "<<cityName[index]<<"!"<<endl;

        return index;
    }
    else{
        cout<<"Could not find city. Check your coordinates!"<<endl;
            return 55;
    }
}
void ArrayImplementation::deleteCityByName(){

    cout<<"Enter the name of the city you wish to delete: ";
    this->curPosition = searchByName(true, false);
    if(this->curPosition != 55){
        cityName[curPosition] = "";
        cityLatitude[curPosition] = 0;
        cityLatitude[curPosition] = 0;
        arrangeArray();
        cout<<"Successfully deleted entry!"<<endl;
    }else{

        cout<<"Deletion attempt was unsuccessful. Try again"<<endl;
    }
}
void ArrayImplementation::deleteCityByCoordinates(){
    bool deleteCity = true;
    int deleteIndex = searchByCoord(deleteCity);
    if(deleteIndex != 55){
        cityName[deleteIndex] = "";
        cityLatitude[deleteIndex] = 0;
        cityLongitude[deleteIndex] = 0;
        arrangeArray();
        cout<<"Successfully deleted entry!"<<endl;
    }else{
        cout<<"Unsuccessful Deletion attempt. Try again."<<endl;
    }
}
void ArrayImplementation::printCitiesInDestination(){
// TODO:
    string foundCities[MAX - 1];
    int usersDistance;
    int indexOfUsersCity;
    if(usersDistance == 0){
            cout<<"That would be the city's location. Please try again."<<endl;
            return;
    }
    if((indexOfUsersCity = this->searchByName(false, true)) == 55){
        return;
    }
    else{
        cout<<"Enter distance: ";
        cin>>usersDistance;
    }
    float distance;
    float e;
    int counter = 0;


    // for error checking
    foundCities[0] == "";
    float foundDistances[MAX];
    // Formula to calculate cities in a given distance on Earth
    for(int i = 0; i < MAX - 1; i++){
        e = acos(sin(deg_to_radians(cityLatitude[indexOfUsersCity]))*sin(deg_to_radians(cityLatitude[i])) + cos(deg_to_radians(cityLatitude[indexOfUsersCity]))*cos(deg_to_radians(cityLatitude[i]))*cos(deg_to_radians(deg_to_radians(cityLongitude[i] - cityLongitude[indexOfUsersCity]))));

        //distance = rad2deg(distance);
        distance = e*radiusMiles;

        if(distance <= usersDistance && usersDistance != 0 && distance > 0 && indexOfUsersCity == i){
            foundCities[counter] = cityName[i];
            foundDistances[counter] = distance;
            counter++;
        }

    }
    if(foundCities[0] == ""){
        cout<<"There were no cities in this distance"<<endl;
        return;
    }

    cout<<"Cities within your chosen distance:\n"<<endl;
    for(int n = 0; n < MAX - 1; n++){
            if(foundCities[n] != "")
                cout<<"Name: "<<foundCities[n]<<" | Distance: "<<foundDistances[n]<<endl;
    }

}
float deg_to_radians(float degrees){

    return degrees*(3.1415926535/180);

}
float rad2deg(float rad) {
  return (rad * 180 / 3.1415926535);
}
void ArrayImplementation::printAll(){
    for(int i = 0; i < MAX; i++){
            if(cityName[i] != ""){
                cout<<cityName[i]<<": "<<cityLatitude[i]<<", "<<cityLongitude[i]<<endl;
            }

    }
}
