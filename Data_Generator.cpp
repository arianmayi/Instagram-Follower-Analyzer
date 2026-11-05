//
// Created by arian on 10/15/2026.
//

#include "Data_Generator.h"
#include <vector>
#include <random>
#include <unordered_set>
#include <algorithm>
using namespace std;

//generator to generate random numbers
namespace {
    mt19937 rng(random_device{}());
}

//constructor
Data_Generator::Data_Generator() {}

//generates usernames with randomizations
string Data_Generator::generateUser() {
    //characters that can be used for generated username
    static const string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    //length of generated usernames
    uniform_int_distribution<> userLength(6, 12);
    //randomly selects a character within chars
    uniform_int_distribution<> charIndex(0, chars.size() - 1);

    //randomly selects the length for the user
    int length = userLength(rng);
    string username;

    //builds the username with selected length and characters
    for (int i = 0; i < length; i++) {
        username += chars[charIndex(rng)];
    }

    return username;
}

void Data_Generator::generateData(size_t total, vector<string>& datasetA, vector<string>& datasetB) {
    //randomly chooses a percentage to affect dataset A
    uniform_int_distribution<> percent(0, 100);
    generateData(total, datasetA, datasetB, percent(rng));
}

//generates and inputs users into both datasets with some overlap
void Data_Generator::generateData(size_t total, vector<string>& datasetA, vector<string>& datasetB, int overlapPercent) {
    //clears datasets when called again for multiple uses (just in case)
    datasetA.clear();
    datasetB.clear();

    unordered_set<string> used;

    //generates usernames and adds to dataset A
    while (datasetA.size() < total) {
        string username = generateUser();
        //if the set doesn't already have the username, insert into dataset A
        if (used.insert(username).second) {
            datasetA.push_back(username);
        }
    }

    //safety check to keep % values between 0 and 100
    if (overlapPercentage < 0) {
        overlapPercentage = 0;
    }
    if (overlapPercentage > 100) {
        overlapPercentage = 100;
    }

    //overlap = what user inputs and/or from random
    this->overlapPercentage = overlapPercent;
    //calculates the percentage into the total size
    size_t overlapCount = (total * overlapPercentage) / 100;

    //shuffles the dataset A
    shuffle(datasetA.begin(), datasetA.end(), rng);

    //adds the randomly selected usernames from dataset A over to dataset B
    for (size_t i= 0; i < overlapCount; i++) {
        datasetB.push_back(datasetA[i]);
    }

    //generates the rest of usernames into dataset B
    while (datasetB.size() < total) {
        string username = generateUser();
        //if the set doesn't already have the username, add to dataset B
        if (used.insert(username).second) {
            datasetB.push_back(username);
        }
    }
}

int Data_Generator::getOverlapPercentage() const {
    return overlapPercentage;
}