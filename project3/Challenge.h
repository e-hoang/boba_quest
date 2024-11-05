#ifndef CHALLENGE_H
#define CHALLENGE_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Challenge 
{
    private:
        string name_;
        string description_;
        vector<string> options_;
        int correct_option_;

    public:
        Challenge(string name, string description, vector<string> options, int correct_option);

        string getName();
        string getDescription();
        vector<string> getOptions();
        int getCorrectOption();
        
        void setName(string name);
        void setDescription(string description);
        void setOptions(vector<string> options);
        void setCorrectOption(int correct_option);
};
#endif