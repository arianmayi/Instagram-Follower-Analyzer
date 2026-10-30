//
// Created by arian on 10/15/2026.
//

#include "Hash_Table.h"
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include <utility>

using namespace std;

Hash_Table::Hash_Table() {
    numOfElements = 0;
    buckets.resize(101); //start with 101 linked list buckets
}

size_t Hash_Table::hashFunction(const string &username) const {
    size_t hashVal = 0;
    for (char c : username) {
        hashVal = hashVal * 31 + static_cast<unsigned char>(c);
    }

    return hashVal % buckets.size(); //returns the index of where the username will be stored
}

void Hash_Table::rehash(size_t newBucketCount) {

    vector<list<string>> temp;
    temp.resize(newBucketCount);

    //get each list in the hash table
    for (size_t i = 0; i < buckets.size(); i++) {
        //loop through each string within each list
        for (const string& username : buckets[i]) {

            //rehash each value to its new bucket, based on new bucket size
            size_t hashVal = 0;
            for (char c : username) {
                hashVal =  hashVal * 31 + static_cast<unsigned char>(c);
            }

            //push all old values to new bucket index within the temp vector
            size_t new_index = hashVal % newBucketCount;
            temp[new_index].push_back(username);
        }
    }

    //repopulate buckets with temp (move function comes from utility)
    buckets = move(temp);
}

//inserts the username at associated index
//we can assume there will never be duplicates in the data given that Instagram (& the data generator)
//does not allow for duplicate usernames
void Hash_Table::insert(const string &username) {

    //check current load factor before inserting anything (+1 to project new element for load factor)
    double loadFactor = static_cast<double>(numOfElements + 1)/buckets.size();

    //if the current load factor is larger than the threshold, rehash
    if (loadFactor > load_factor) {
        size_t table_size = buckets.size();
        size_t new_bucket_count = table_size * 2;
        rehash(new_bucket_count);
    }

    //now insert
    size_t index = hashFunction(username);
    buckets[index].push_back(username);
    numOfElements++;
}

//used for the analyzer
bool Hash_Table::contains(const string &username) const {

    size_t index = hashFunction(username); //get the index of the username we are looking for

    //search for the username in the linked list pointed by the index #
    auto it = find(buckets[index].begin(), buckets[index].end(), username);
    if (it != buckets[index].end()) {
        return true;
    }
    return false;
}

//returns the total elements that have been inserted
size_t Hash_Table::size() const {
    return numOfElements;
}

void Hash_Table::clear() {
    buckets.clear();
    buckets.resize(101);
    numOfElements = 0;
}