//
// Created by arian on 10/15/2026.
//

#include "Analyzer.h"

#include "Hash_Table.h"
#include "Red_Black.h"

#include <vector>
#include <string>

using namespace std;

//constructor
Analyzer::Analyzer(const vector<string>& followers, const vector<string>& following)
    : followers(followers), following(following) {
}

//Hash Table implementation
void Analyzer::difference_in_followers() {

    //create following hash table, compare against follower vector
    Hash_Table following_table;
    difference_followers.clear();

    //Fills the Hash Tables for comparison
    for (size_t i = 0; i < following.size(); i++) {
        following_table.insert(following[i]);
    }

    //loop through the vector of followers, look up in the hash table of following.
    //check for match
    //if false, push into the difference
    for (size_t i = 0; i < followers.size(); i++) {
        if (!following_table.contains(followers[i])) {
            difference_followers.push_back(followers[i]);
        }
    }
}

//Hash Table implementation
void Analyzer::difference_in_following() {

    Hash_Table follower_table;
    difference_following.clear(); //erase any previous data
    mutual.clear();

    //populate the follower Hash Table
    for (size_t i = 0; i < followers.size(); i++) {
        follower_table.insert(followers[i]);
    }

    for (size_t i = 0; i < following.size(); i++) {
        if (!follower_table.contains(following[i])) {
            difference_following.push_back(following[i]);
        }else {
            mutual.push_back(following[i]); //mutual found
        }
    }
}
