//
// Created by arian on 10/15/2026.
//

#include "Analyzer.h"

#include "Hash_Table.h"
#include "Red_Black.h"

#include <vector>
#include <string>
#include <chrono> //used for benchmark (timer)

using namespace std;

//constructor
Analyzer::Analyzer(const vector<string>& followers, const vector<string>& following)
    : followers(followers), following(following) {
}

//==================== ANALYSIS =======================================================
//==================== HASH IMPLEMENTATION =============================================

void Analyzer::difference_in_followers_HASH() {

    //create following hash table, compare against follower vector
    Hash_Table following_table;

    //clear any previous data
    difference_followers_hash.clear();

    //Fills the Hash Tables for comparison
    for (size_t i = 0; i < following.size(); i++) {
        following_table.insert(following[i]);
    }

    //loop through the vector of followers, look up in the hash table of following.
    //check for match
    //if false, push into the difference
    for (size_t i = 0; i < followers.size(); i++) {
        if (!following_table.contains(followers[i])) {
            difference_followers_hash.push_back(followers[i]);
        }
    }
}

void Analyzer::difference_in_following_HASH() {

    //create follower hash table, compare against following vector
    Hash_Table follower_table;

    //clear any previous data
    difference_following_hash.clear();

    //clear any previous data
    mutual_hash.clear();

    //populate the follower Hash Table
    for (size_t i = 0; i < followers.size(); i++) {
        follower_table.insert(followers[i]);
    }

    for (size_t i = 0; i < following.size(); i++) {
        if (!follower_table.contains(following[i])) {
            difference_following_hash.push_back(following[i]);
        }else {
            mutual_hash.push_back(following[i]); //mutual found
        }
    }
}

//==================== RED-BLACK IMPLEMENTATION =============================================

void Analyzer::difference_in_followers_RB() {

    //create tree filled with users you follow
    RedBlackTree following_tree;
    difference_followers_RB.clear(); //clear any data

    for (size_t i = 0; i < following.size(); i++) {
        following_tree.insert(following[i]);
    }

    for (size_t i = 0; i < followers.size(); i++) {
        if (!following_tree.containsUser(followers[i])) {
            difference_followers_RB.push_back(followers[i]);
        }
    }
}

void Analyzer::difference_in_following_RB() {

    RedBlackTree follower_tree;
    difference_following_RB.clear();
    mutual_RB.clear();

    for (size_t i = 0; i < followers.size(); i++) {
        follower_tree.insert(followers[i]);
    }

    for (size_t i = 0; i < following.size(); i++) {
        if (!follower_tree.containsUser(following[i])) {
            difference_following_RB.push_back(following[i]);
        }else {
            mutual_RB.push_back(following[i]);
        }
    }
}

//==================== GETTERS =======================================================

//==================== HASH IMPLEMENTATION =============================================

//will return a vector of all users you follow that do not follow you back
const vector<string> &Analyzer::get_difference_following_hash() const {
    return difference_following_hash;
}

//will return a vector of all users who follows you & you don't follow them back
const vector<string> &Analyzer::get_difference_followers_hash() const {
    return difference_followers_hash;
}

//returns a vector containing mutual relationship amongst users (following each other)
const vector<string> &Analyzer::get_mutual_hash() const {
    return mutual_hash;
}

//==================== RED-BLACK IMPLEMENTATION =============================================

const vector<string> &Analyzer::get_difference_following_RB() const {
    return difference_following_RB;
}

const vector<string> &Analyzer::get_difference_followers_RB() const {
    return difference_followers_RB;
}

const vector<string> &Analyzer::get_mutual_RB() const {
    return mutual_RB;
}

//==================== BENCHMARK COMPARISON =======================================================

BenchMarkResults Analyzer::benchMark_Performance() {
    //objs used to determine performance
    Hash_Table follower_table; //hash table obj
    RedBlackTree follower_tree; //red-black obj

    //=============== HASH INSERTION PERFORMANCE =========================

    //measure time needed to insert all followers into the hash table
    auto start_insert_hash = chrono::steady_clock::now();
    for (const string& username : followers) {
        follower_table.insert(username);
    }

    auto end_insert_hash = chrono::steady_clock::now();

    //stores the time in ms, the time it takes for insertion in the hash table
    double hash_insert_ms = chrono::duration<double,milli>(end_insert_hash-start_insert_hash).count();

    //=============== HASH SEARCH PERFORMANCE =========================
    int search_hash_counter = 0; //returns non-follow backs for hash table (should be same # as red black)
    auto start_search_hash = chrono::steady_clock::now();

    //measure the time it takes to search for a username within a hashtable
    for (size_t i = 0; i < following.size(); i++) {
        if (!follower_table.contains(following[i])) {
            search_hash_counter++;
        }
    }

    auto end_search_hash = chrono::steady_clock::now();
    double hash_search_ms = chrono::duration<double,milli>(end_search_hash - start_search_hash).count();

    //=============== RED-BLACK INSERTION PERFORMANCE =========================

    auto start_insert_RB = chrono::steady_clock::now();
    for (const string& username : followers) {
        follower_tree.insert(username);
    }

    auto end_insert_RB = chrono::steady_clock::now();
    double RB_insert_ms = chrono::duration<double,milli>(end_insert_RB - start_insert_RB).count();

    int search_RB_counter = 0; //returns non-follow backs for red-black (should be same # as hash table)
    auto start_search_RB = chrono::steady_clock::now();

    for (size_t i = 0; i < following.size(); i++) {
        if (!follower_tree.containsUser(following[i])) {
            search_RB_counter++;
        }
    }

    auto end_search_RB = chrono::steady_clock::now();
    double RB_search_ms = chrono::duration<double,milli>(end_search_RB - start_search_RB).count();

    return {hash_insert_ms, hash_search_ms, RB_insert_ms, RB_search_ms};

}


