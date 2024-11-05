#include "Drink.h"
#include <iostream>
using namespace std;

Drink::Drink(string name, int price, int healthRestore, int energyRestore) //parameterized constructor 
{
    name_ = name;
    price_ = price;
    healthRestore_ = healthRestore;
    energyRestore_ = energyRestore;
}

string Drink::getName() //name getter method
{
    return name_;
}

int Drink::getPrice() //price getter method
{
    return price_;
}

int Drink::getHealthRestore() //health restore getter method
{
    return healthRestore_;
}

int Drink::getEnergyRestore() //energy restore getter method
{
    return energyRestore_;
}