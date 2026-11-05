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


//used for benchmark performance.
//allows for multiple variables to be returned from one function
struct BenchMarkResults {
    double hash_insert_ms;
    double hash_search_ms;
    double RB_insert_ms;
    double RB_search_ms;
};

class Analyzer {

    private:

    //stores following & followers to later be inserted into the hash table & red-black
    //data comes from either randomized generator or the data loader
    vector<string> followers;
    vector<string> following;

    //stores the results from relationship comparison
    vector<string> difference_following_hash; //users you follow who don't follow you back
    vector<string> difference_followers_hash; //users who follow you but you don't follow back
    vector<string> mutual_hash; //users who follow each other

    //Red-Black version
    vector<string> difference_following_RB; //users you follow who don't follow you back
    vector<string> difference_followers_RB;//users who follow you but you don't follow back
    vector<string> mutual_RB; //users who follow each other


public:

    //constructor, meant to accept data from other classes
    Analyzer(const vector<string>& followers, const vector<string>& following);

   //Analysis user relationship
    void difference_in_followers_HASH();
    void difference_in_following_HASH();

    void difference_in_followers_RB();
    void difference_in_following_RB();

    //return analysis results stored in vectors (getter functions)

    //Hash table
    const vector<string>& get_difference_following_hash() const;
    const vector<string>& get_difference_followers_hash() const;
    const vector<string>& get_mutual_hash() const;

    //Red-Black
    const vector<string>& get_difference_following_RB() const;
    const vector<string>& get_difference_followers_RB() const;
    const vector<string>& get_mutual_RB() const;

    //Benchmark Hash Table vs. Red-Black Tree
    BenchMarkResults benchMark_Performance();

};

#endif //PROJECT2_ANALYZER_H
