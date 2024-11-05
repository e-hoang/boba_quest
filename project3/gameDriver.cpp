#include "Challenge.h"
#include "Player.h"
#include "Shop.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <fstream>
using namespace std;

// g++ -std=c++17 gameDriver.cpp Challenge.cpp Map.cpp Player.cpp Shop.cpp

void addToLeaderboard(Player player, int movesMade, int thirstLevel, bool won){
    ofstream myfile;
    myfile.open ("leaderboard.txt", ios_base::app);
    if(!won)
        myfile << "(LOST) ";
    myfile << player.getName() << ": " << movesMade << " Moves Made, " << thirstLevel << " Thirstiness" << endl;
    myfile.close();
}

void displayLeaderboard(){
    cout << "Here's how everyone else did (and you):" << endl;
    string line;
    ifstream myfile ("leaderboard.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
        cout << " - " << line << '\n';
        }
        myfile.close();
    }
    else cout << "Unable to open file";
}

void cToContinue(){
    cout << "Type c to continue" << endl;
    char c;
    cin >> c;
}

void runGame() 
{
    // Initialize game objects
    Map gameMap;
    vector<string> menu = {"Milk Tea","Thai Tea", "Matcha Tea"};
    vector<int> prices = {3, 4, 4};
    Shop shop("Tea House", menu, prices);
    vector<Challenge> challenges;
    challenges.push_back(Challenge("Trivia", "Where did boba originate?", {"a) Taiwan", "b) China", "c) Japan"}, 1));
    challenges.push_back(Challenge("Math", "I have 5 boba drinks and drink 3. How many are left?", {"a) 4", "b) 3", "c) 2"}, 3));
    challenges.push_back(Challenge("Trivia", "What are boba pearls called?", {"a) Tolloca", "b) Pudding", "c) Tapioca"}, 3));

    string playerName;
    cout << "What is your name: ";
    cin >> playerName;
    Player player(playerName);
    player.setThirst(0);

    // Set up game
    gameMap.resetMap();
    player.setPosition(5, 5);
    player.setGold(100);
    srand(time(0));
    gameMap.addNPC(rand() % gameMap.getNumRows(), rand() % gameMap.getNumRows()); //adding NPC's
    gameMap.addNPC(rand() % gameMap.getNumRows(), rand() % gameMap.getNumCols());
    gameMap.addNPC(rand() % gameMap.getNumRows(), rand() % gameMap.getNumCols());
    gameMap.addRoom(rand() % gameMap.getNumRows(), rand() % gameMap.getNumCols()); // add shop
    gameMap.exploreSpace(gameMap.getPlayerRow(), gameMap.getPlayerCol());

    int challengesCompleted = 0;
    int movesMade = 0;


    // Game loop
    while (true) 
    {
        // Display game menu
        cout << "What would you like to do?" << endl;
        cout << "1. Play" << endl;
        cout << "2. Controls" << endl;
        cout << "3. Inventory" << endl;
        cout << "4. Stats" << endl;
        // cout << "5. Recipes" << endl;
        cout << "5. Exit" << endl;
        int choice;
        cin >> choice;

        // Process user choice
        switch (choice){
            case 1: {
                // Move player on map
                char moveDirection;
                bool isMoveSuccessful;
                while (true){
                    gameMap.displayMap();
                    
                    if(player.isThirsty()){
                        cout << "WARNING, YOU ARE DEHYDRATED" << endl;
                    }

                    if(player.getThirst() >= 100){
                        cout << "GAME OVER. You died from dehydration" << endl;
                        addToLeaderboard(playerName, movesMade, player.getThirst(), false);
                        displayLeaderboard();
                        exit(0);
                    }

                    cout << "Enter move direction (WASD) or M for Menu: ";
                    cin >> moveDirection;
                    if(tolower(moveDirection) == 'm')
                        break;
                    isMoveSuccessful = gameMap.move(moveDirection);

                    if (!isMoveSuccessful){
                        cout << "Invalid move. Please try again." << endl;
                    } else{
                        gameMap.exploreSpace(gameMap.getPlayerRow(), gameMap.getPlayerCol());
                        movesMade++;
                        player.setThirst(player.getThirst() + 5);
                        cout << "Your thirst level is at " << player.getThirst() << endl;
                        if(gameMap.isNPCLocation(gameMap.getPlayerRow(), gameMap.getPlayerCol()) && challengesCompleted != 3){
                            cout << "I have a challenge for you! If you complete it then you will be one step closer to your escape" << endl;
                            Challenge currentChallenge = challenges[challengesCompleted];
                            char answerChoice;
                            while(true){
                                cout << "----- Challenge" << " " << challengesCompleted + 1 << ": " << currentChallenge.getName() << " -----" << endl;
                                cout << currentChallenge.getDescription() << endl;
                                for(string option : currentChallenge.getOptions()){
                                    cout << option << endl;
                                }
                                cout << "What's your answer?" << endl;
                                cin >> answerChoice;
                                cout << (char) (currentChallenge.getCorrectOption() + 96) << endl;
                                if(answerChoice == (char) currentChallenge.getCorrectOption() + 96){
                                    challengesCompleted++;
                                    cout << "That's Correct! Only " << challenges.size() - challengesCompleted << " challenges left to earn your leave." << endl;
                                    gameMap.removeNPC(gameMap.getPlayerRow(), gameMap.getPlayerCol());
                                    cToContinue();
                                    break;
                                } else{
                                    if(player.getThirst() >= 100){
                                        cout << "GAME OVER. You died from dehydration" << endl;
                                        addToLeaderboard(playerName, movesMade, player.getThirst(), false);
                                        displayLeaderboard();
                                        exit(0);
                                    }
                                    cout << "WRONG. You gained 15 thirst. You're now at " << player.getThirst() << ". Try again!" << endl;
                                    player.setThirst(player.getThirst() + 15);
                                    cToContinue();
                                }
                            }
                        } else if (gameMap.isRoomLocation(gameMap.getPlayerRow(), gameMap.getPlayerCol())){
                            shop.DisplayMenu();
                            cout << "What would you like to drink?" << endl;
                            cin >> choice;
                            choice -= 1;
                            if(shop.SellItem(choice, player)){
                                player.setGold(player.getGold() - shop.GetPrices()[choice]);
                                player.addToInventory(shop.GetMenu()[choice]);
                                cout << "You now have " << shop.GetMenu()[choice] << " in your inventory" << endl;
                            } else{
                                cout << "Yikes, it looks like you don't have enough money for that" << endl;
                            }
                        }
                    }

                    // Check if player has reached the exit
                    if (gameMap.isDungeonExit(gameMap.getPlayerRow(), gameMap.getPlayerCol()))
                    {
                        if(challengesCompleted == 3){
                            cout << "You have escaped!" << endl;
                            cout << "In the end, you took " << movesMade << " steps," << endl;
                            cout << "had a thirstiness level of " << player.getThirst() << "," << endl;
                            cout << "had $" << player.getGold() << "," << endl;
                            cout << "and this left in your inventory: ";
                            if (player.getInventory().empty()) 
                            {
                                cout << "Empty" << endl;
                            } 
                            else 
                            {
                                player.displayInventory();
                            }
                            cout << endl << "-------------------------------" << endl << endl;
                            addToLeaderboard(playerName, movesMade, player.getThirst(), true);
                            displayLeaderboard();
                            exit(0);
                            break;
                        } else{
                            cout << "You must complete all challenges before you can leave" << endl;
                        }
                    }
                }
                break;
            }
            
            
            case 2: { // Controls
                cout << "---- CONTROLS ----" << endl;
                cout << "W - Move Up" << endl;
                cout << "S - Move Down" << endl;
                cout << "A - Move Left" << endl;
                cout << "D - Move Right" << endl;
                cout << "------------------" << endl;
                cToContinue();
                break;
            }
            
            case 3: {
                // display inventory
                player.displayInventory();
                if(player.getInventory().empty()){
                    cToContinue();
                    break;
                }
                cout << "Would you like to drink anything?" << endl;
                cin >> choice;
                choice -= 1;
                player.setThirst(player.getThirst() - 50);
                cout << "You drank " << player.getInventory()[choice] << ", and are now at " << player.getThirst() << " thirst" << endl;
                player.drinkBeverage(choice);
                cToContinue();
                break;
            }

            case 4: {
                cout << "------- PLAYER STATS -------" << endl;
                cout << "Challenges Completed: " << challengesCompleted << endl;
                cout << "Moves Made: " << movesMade << endl;
                cout << "Thirstiness: " << player.getThirst() << endl;
                cout << "Money: $" << player.getGold() << endl;
                player.displayInventory();
                cout << "----------------------------" << endl;
                cToContinue();
                break;
            }

            case 5:{
                cout << "You quit" << endl;
                break;
            }
        }
    }
}

int main()
{
    Map myMap;
    myMap.resetMap();
    runGame();
    return 0;
}