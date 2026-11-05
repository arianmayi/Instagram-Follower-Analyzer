//
// Created by arian on 10/15/2026.
//

#ifndef PROJECT2_DATA_GENERATOR_H
#define PROJECT2_DATA_GENERATOR_H
#include <vector>
#include <string>
using namespace std;

//randomized data generation for the algorithms to work with -> meets 100k+ proj requirnment
//Role: Ngoc
//Generates 100k followers and/or following
//ex: generate_following(75000), generate_followers(25000).... 100,000 total.


class Data_Generator {
private:
    int overlapPercentage = 0;
    string generateUser();

public:
    Data_Generator();

    void generateData(size_t total, vector<string>& datasetA, vector<string>& datasetB);

    void generateData(size_t total, vector<string>& datasetA, vector<string>& datasetB, int overlapPercentage);

    int getOverlapPercentage() const;
};



#endif //PROJECT2_DATA_GENERATOR_H
