#ifndef DRINK_H
#define DRINK_H
#include <iostream>
#include <string>
using namespace std;

class Drink 
{
    private:
        string name_;
        int price_;
        int healthRestore_;
        int energyRestore_;

    public:
        Drink(string name, int price, int healthRestore, int energyRestore);

        string getName();
        int getPrice();
        int getHealthRestore();
        int getEnergyRestore();

        void setName(string name);
        void setPrice(int price);
        void setHealthRestore(int healthRestore);
        void setEnergyRestore(int energyRestore);
};
#endif