//
// Created by arian on 10/15/2026.
//

#ifndef PROJECT2_HASH_TABLE_H
#define PROJECT2_HASH_TABLE_H

#include <string>
#include <vector>
#include <list>

using namespace std;

class Hash_Table {

private:

   //stores usernames in buckets using linked list
   vector<list<string>> buckets;

   //number of usernames stored
   size_t numOfElements;

   //hash function -> username to a bucket index
   size_t hashFunction(const string& username) const;

   //resizes tables and redistributes usernames incase load factor gets too high
   void rehash(size_t newBucketCount);

   //constexpr allows for initialization of a variable at compile time
   //stores threshold for load factor -> used for rehashing
   static constexpr double load_factor = .75;

public:

   Hash_Table(); //constructor

   //inserts username
   void insert(const string& username);

   //checks whether a username exist
   bool contains(const string& username) const;

   //returns the number of stored usernames
   size_t size() const;

   //deletes all usernames from the table (like a reset)
   void clear();

};

#endif //PROJECT2_HASH_TABLE_H
