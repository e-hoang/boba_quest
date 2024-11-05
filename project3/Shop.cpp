#include "Shop.h"
#include <iostream>
using namespace std;

Shop::Shop(string name, vector<string> menu, vector<int> prices) //parameterized constructor
{
    name_ = name;
    menu_ = menu;
    prices_ = prices;
}

string Shop::GetName() //shop name getter method
{
    return name_;
}

vector<string> Shop::GetMenu() //menu getter method
{
    return menu_;
}

vector<int> Shop::GetPrices() //price getter method
{
    return prices_;
}

void Shop::DisplayMenu() //menu display method
{
    cout << "Welcome to " << name_ << "! Take a look at our menu:" << endl;
    for (int i = 0; i < menu_.size(); i++)
    {
        cout << i+1 << ". " << menu_[i] << " - $" << prices_[i] << endl; //output name and price of menu items
    }
}

bool Shop::SellItem(int index, Player player) //selling items to player method
{
    if (index < 0 || index >= menu_.size() || player.getGold() < prices_[index]) 
        return false; //case if item doesn't exist or player can't afford item

    cout << "You bought " << menu_[index] << " for $" << prices_[index] << "." << endl; //output for sale
    return true;
}