//
// Created by arian on 10/15/2026.
//

#ifndef PROJECT2_ANALYZER_H
#define PROJECT2_ANALYZER_H

#include <string>
#include <vector>

using namespace std;

/*
 *Purpose of class:
 *Analyze follower/following relationships.
 *Identify accounts that do not follow the user back
 *Identify accounts the user does not follow back
 *Identify mutual followers
 *Compare Hash Table & Red-Black Tree performance
 */

class Analyzer {

    private:

    //stores following & followers to later be inserted into the hash table & red-black
    //data comes from either randomized generator or the data loader
    vector<string> followers;
    vector<string> following;

    //stores the results from relationship comparison
    vector<string> difference_following; //users you follow who don't follow you back
    vector<string> difference_followers; //users who follow you but you don't follow back
    vector<string> mutual; //users who follow each other


public:

    //constructor, meant to accept data from other classes
    Analyzer(const vector<string>& followers, const vector<string>& following);

   //Analysis user relationship
    void difference_in_followers();
    void difference_in_following();

    //return analysis results stored in vectors (getter functions)
    const vector<string>& get_difference_following() const;
    const vector<string>& get_difference_followers() const;
    const vector<string>& get_mutual() const;

    //Benchmark Hash Table vs. Red-Black Tree
    void benchMark_Performance();

};

#endif //PROJECT2_ANALYZER_H
