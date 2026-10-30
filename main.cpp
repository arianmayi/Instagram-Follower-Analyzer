
#include <iostream>
#include <vector>
#include <string>
#include "Data_Generator.h"
#include "Hash_Table.h"

using namespace std;

int main() {

    //test generator, make sure it works:
    // Generate 100,000 usernames per dataset
    Data_Generator generator;

    vector<string> followers;
    vector<string> following;

    //generate 100,000 (50,000 & 50,000)
    generator.generateData(50000, followers, following);

    //check the generator works (at least the size)
    cout << "Generated followers: " << followers.size() << endl;
    cout << "Generated following: " << following.size() << endl;

    // Create Hash Table
    Hash_Table followersTable;
    Hash_Table followingTable;

    // Insert every follower
    for (const string& username : followers) {
        followersTable.insert(username);
    }

    // Insert every following
    for (const string& username: following) {
        followingTable.insert(username);
    }

    cout << "Follower Hash Table Size: " << followersTable.size() << endl;
    cout << "Following Hash Table Size: " << followingTable.size() << endl;

    //confirm the followers vector is the same as the followers-hashTable. (should be the same for following)
    size_t found = 0;

    for (const string& username : followers) {
        if (followersTable.contains(username)) {
            found++;
        }
    }

    cout << "Followers successfully found: " << found << endl;

    //Test clear function
    followersTable.clear();
    followingTable.clear();

    cout << "Follower after clear: " << followersTable.size() << endl;
    cout << "Following after clear: " << followingTable.size() << endl;

    return 0;
}
