#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(string name) //parameterized constructor
{
    name_ = name;
    gold_ = 0;
    thirst_ = 0;
}

string Player::getName() //player name getter method
{
    return name_;
}

int Player::getGold() //gold getter method
{
    return gold_;
}

int Player::getThirst() //thirst getter method
{
    return thirst_;
}

vector<string> Player::getInventory() //inventory getter method
{
    return inventory_;
}

void Player::setGold(int gold) //setting gold
{
    gold_ = gold;
}

void Player::setThirst(int thirst) //setting thirst
{
    thirst_ = thirst;
}

void Player::setPosition(int row, int col) 
{
    row_ = row;
    col_ = col;
}

void Player::addToInventory(string item) //adding to inventory
{
    inventory_.push_back(item);
}

void Player::removeFromInventory(string item) //removing from inventory
{
    for (int i = 0; i < inventory_.size(); i++) //for loop to go through inventory
    {
        if (inventory_[i] == item) //case if item is found in inventory
        {
            inventory_.erase(inventory_.begin() + i); //remove item from inventory
            return;
        }
    }
}


void Player::displayInventory() //displays inventory
{
    if (inventory_.empty()) //case if inventory is empty
    {
        cout << "Inventory is empty." << endl;
    }
    else //case if inventory is not empty
    {
        cout << "Inventory:" << endl;
        for (int i = 0; i < inventory_.size(); i++) //for loop to go through inventory
        {
            cout << "- " << i + 1 << ". " << inventory_[i] << endl; //print item
        }
    }
}

bool Player::isThirsty() //checks if player is thirsty
{
    return thirst_ > 75;
}

void Player::drinkBeverage(int index) //lets player drink boba
{
    if (inventory_.empty()) //case if inventory is empty
    {
        cout << "Inventory is empty." << endl;
        return;
    }
    inventory_.erase(inventory_.begin() + index);
}