#include "Challenge.h"
#include "Drink.h"
#include "Player.h"
#include "Shop.h"
#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

/*Algorithmn drinkClass() (FOR CODE SKELETON)
1. Create a Drink object with values for name and price of drink, and health restore and energy restore amounts
2. Match inital values with getters
3. Update object values with setters
4. Match values with getters
5.Test Drink object by calling function
*/
void drinkClass() 
{
    Drink drink("water", 2, 0, 20);

    assert(drink.GetName() == "water"); //getters
    assert(drink.GetPrice() == 1);
    assert(drink.GetHealthRestore() == 10);
    assert(drink.GetEnergyRestore() == 20);

    drink.SetName("taro"); //setters
    drink.SetPrice(5);
    drink.SetHealthRestore(20);
    drink.SetEnergyRestore(25);
    assert(drink.GetName() == "taro"); //getters to test updates to values 
    assert(drink.GetPrice() == 5);
    assert(drink.GetHealthRestore() == 20);
    assert(drink.GetEnergyRestore() == 25);
}


/*Algorithmn challengeClass()
1. Create a Challenge object with the name of the challenge, a description, options, and a correct option
2. Match values using getters
3. Change object values using setters
4. Match values again using getters
*/
void challengeClass() 
{
    vector<string> options = {"Option 1", "Option 2", "Option 3"}; 
    Challenge challenge("Challenge 1", "Description 1", options, 1); //challenge object

    assert(challenge.GetName() == "Challenge 1"); //getters
    assert(challenge.GetDescription() == "Description 1");
    assert(challenge.GetOptions() == options);
    assert(challenge.GetCorrectOption() == 1);

    vector<string> new_options = {"Option A", "Option B", "Option C"}; //setters
    challenge.SetName("Challenge 2");
    challenge.SetDescription("Description 2");
    challenge.SetOptions(new_options);
    challenge.SetCorrectOption(2);
    assert(challenge.GetName() == "Challenge 2"); //getters to test updates
    assert(challenge.GetDescription() == "Description 2");
    assert(challenge.GetOptions() == new_options);
    assert(challenge.GetCorrectOption() == 2);
}

/*Algorithmn playerClass()
1. Create a Player object 
2. Match values using getters
3. Change object values using setters
4. Test out inventory features
5. Test out drinking beverage features
*/
void playerClass() 
{
    Player player("Kevin"); //example player name from player object

    assert(player.GetName() == "Kevin"); //getters
    assert(player.GetEnergy() == 100);
    assert(player.GetMood() == 100);
    assert(player.GetThirst() == 0);
    assert(player.GetInventory().empty());

    player.SetEnergy(45); //setters
    player.SetMood(69);
    player.SetThirst(20);
    assert(player.GetEnergy() == 45);
    assert(player.GetMood() == 69);
    assert(player.GetThirst() == 20);

    player.AddToInventory("pearls"); //adding to inventory
    player.AddToInventory("boba");
    assert(player.GetInventory().size() == 2);
    player.RemoveFromInventory("pearls"); //removing from inventory
    assert(player.GetInventory().size() == 1);
    assert(player.GetInventory()[0] == "boba");

    Drink beverage("boba", 2, 0, 10); //drinking boba
    assert(player.GetEnergy() == 69); //energy and thirst updates after drinking boba
    assert(player.GetThirst() == 31);
}

/*
1. Create a shop object called "Ingredient Store" with ingredients and prices
2. Use assert to make sure the name, ingredients, and prices match
*/
void shopClass() 
{
    Shop shop("Ingredient Store", {"pearls", "sugar", "milk"}, {15, 15, 20}); //shop object

    assert(shop.GetName() == "Ingredient Store"); //check if shop name matches
    assert(shop.GetMenu().size() == 3); //check menu size
    assert(shop.GetPrices().size() == 3); //check number of price size
}

int main() 
{
    drinkClass();
    challengeClass();
    playerClass();
    shopClass();
    return 0;
}