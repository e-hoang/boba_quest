#ifndef SHOP_H
#define SHOP_H
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
using namespace std;

class Shop 
{
    private:
        string name_;
        vector<string> menu_;
        vector<int> prices_;

    public:
        Shop(string name, vector<string> menu, vector<int> prices);

        string GetName();
        void SetName(string name);

        vector<string> GetMenu();
        void SetMenu(vector<string> menu);

        vector<int> GetPrices();
        void SetPrices(vector<int> prices);
        
        void DisplayMenu();
        bool SellItem(int index, Player player);
};
#endif
