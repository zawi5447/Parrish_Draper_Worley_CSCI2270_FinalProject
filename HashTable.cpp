//
//  HashTable.cpp
//
//  Final Project
//  CSCI-2270
//  Conor Parrish, James Draper, Luke Worley
//

#include <iostream>
#include <vector>
#include "HashTable.h"

using namespace std;

HashTable::HashTable(){
    table = vector<Location*> (tableSize);
    for(int i=0; i<tableSize; i++){
        table[i] = NULL;
    }
}
HashTable::~HashTable(){

}

void HashTable::insertLocation(std::string in_title, int lives){
    int index = hashSum (in_title);
    Location *newLocation = new Location(in_title, lives);
    Location *possible = table[index];

    if (possible == NULL)
    {
        cout<< index << " "<< in_title<<" no collision"<<endl;
        table[index] = newLocation;
        newLocation->next = NULL;
    }
    else
    {
        //cout<<" collision";
        if (in_title.compare(possible->title)>0) // if in title is after possible  alphabetically
        {

        //cout<<index<<" "<<in_title<<" collision"<<endl;
            while(possible->next!=NULL)
            {
                if(in_title.compare(possible->next->title)<0) // if its supposed to go in the middle
                {
                    break;
                }
                possible = possible -> next;
            }
            //cout<< newLocation -> title <<endl;
            newLocation->next = possible->next;
            possible->next = newLocation;
        }
        else
        {
            //cout<<"head collision"<<endl;
            newLocation->next = possible;
            table[index] = newLocation;
        }
    }

}
//prototype:
//  table.findLocation("location")
//Description:
//  This function takes in the location at which the player would like to be. It goes through our
//  hashtable to find the location and give the player the options associated with that location.
//Pre-Conditions:
//  requires a string as an input
//  you must have built an instance of our hash table and filled it with locations before deleting a location

Location* HashTable::findLocation(std::string in_title){
    int index = hashSum(in_title);
    if(table[index] != NULL){
        Location *temp = table[index];
        while(temp != NULL){
            if(temp->title == in_title){
                return temp;
            }
            else{
                temp = temp->next;
            }
        }
        return NULL;
    }
    else{
        return NULL;
    }
}
//prototype:
//  map.deleteLocation("string")
// Description:
//  This function deletes a "location" from our hash table. Each of our locations are
//  to determine at what point in our rpg game the player is in.
//Pre-Conditions
//  requires a string as an input
//  you must have built an instance of our hash table and filled it with locations before deleting a location
void HashTable::deleteLocation(std::string in_title){
    Location* loc = findLocation(in_title);
    if(loc == NULL){ //Location does not exist
        cout << "not found" << endl;
    }
    else{
        int index = hashSum(in_title);
        Location *temp = table[index];
        if(temp->title == in_title){ //Location to be deleted is head of list
            //cout << "head of list" << endl;
            if(temp->next == NULL){ //Is only location in list
                table[index] = NULL;
                delete temp;
            }
            else{ //Is not only location
                table[index] = temp->next;
                delete temp;
            }
        }
        else{ //Location to be deleted is not head of list
            //cout << "not head of list" << endl;
            while(temp->next != NULL){
                if(temp->next->title == in_title){ //If next node is location to be deleted
                    Location *temp2 = temp->next;
                    temp->next = temp->next->next;
                    delete temp2;
                }
                else{
                    temp = temp->next;
                }
            }
        }
    }
}
void HashTable::printMap()
{

    bool isEmpty = true;
    for(int i=0; i<table.size(); i++){
        if(table[i] != NULL){
            isEmpty = false;
            Location *x = table[i];
            while(x != NULL){
                cout << x->title << ":" << x->lives << endl;
                x = x->next;
            }
        }
    }
    if(isEmpty == true){
        cout << "empty" << endl;
    }
}
int HashTable::hashSum(string x){ //x is the string to hash, s is the array size
    int sum = 0;
    for(int i=0; i<x.length(); i++){
        sum =sum + x[i];
    }
    sum = sum % tableSize;
    return sum;
}
// always decrements lives so that the players current life doesnt need to be known (makes it a little easier) if we want to be able to
// give the player health back we can pass an integer when that integer is greater than zero you add to health and if its less than zero you
// decrement the health
void HashTable::setHealth(std::string name)
{
    Location *toSet = findLocation(name);
    toSet->lives--;
}
//The player must have left the first level for there to be anything to print.
//Everytime the player visits a new location we must assign that new location to the end of our visited linked list.
void HashTable::printPreviousLocations(Location *head)
{
    Location *start = head;
    while (start->orderVisited!=NULL)
    {
        cout<<start->title<< "->"<<endl;
    }

}

//adds the current location to the end of the linked list
void HashTable::addToOrder (string location)
{
    Location* start = head;
    Location* tail = findLocation(location);
    while (start -> orderVisited != NULL) //head is a public member of our  class
    {
        start=start->orderVisited; //(iterate through the order we've visited)

    }
    start->orderVisited = tail;
    tail->orderVisited = NULL;
}
void HashTable::printNotVisitedLocations(Location *head)
{
    bool isEmpty = true;
    for(int i=0; i<table.size(); i++){
        if(table[i] != NULL){
            isEmpty = false;
            Location *x = table[i];
            while(x != NULL){
                if(x->visited==false)
                {
                    cout << x->title << "->";
                }

                x = x->next;
            }
        }
        cout<<endl;
    }

}
bool HashTable::allVisited(){
    bool visited = true;
    for(int i=0; i<table.size(); i++){
        if(table[i]->visited == false){
            visited = false;
        }
    }
    return visited;
}


//making changes


