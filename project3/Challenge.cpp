#include "Challenge.h"
#include <iostream>
using namespace std;

Challenge::Challenge(string name, string description, vector<string> options, int correct_option) //parameterized constructor
{
    name_ = name;
    description_ = description;
    options_ = options;
    correct_option_ = correct_option;
}

string Challenge::getName() //name getter method 
{
    return name_;
}

string Challenge::getDescription() //description getter method
{
    return description_;
}

vector<string> Challenge::getOptions() //options getter method
{
    return options_;
}

int Challenge::getCorrectOption() //correct option getter method
{
    return correct_option_;
}