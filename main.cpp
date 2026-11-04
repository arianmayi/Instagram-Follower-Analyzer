
#include <iostream>
#include <vector>
#include <string>

#include "Analyzer.h"
#include "Data_Generator.h"
#include "Red_Black.h"

using namespace std;


void testRedBlackTree() {
    cout << "\n========== RED-BLACK TREE TESTS ==========\n";

    int passed = 0;
    int total = 0;

    // Helper for printing test results
    auto check = [&](const string& name, bool result) {
        total++;

        if (result) {
            passed++;
        }

        cout << name << ": "
             << (result ? "PASSED" : "FAILED") << endl;
    };

    // TEST 4: Empty tree
    {
        RedBlackTree tree;

        check("Empty Tree",
              !tree.containsUser("Alex"));
    }

    // TEST 5: Single node
    {
        RedBlackTree tree;
        tree.insert("Alex");

        check("Single Node",
              tree.containsUser("Alex") &&
              !tree.containsUser("Brian"));
    }

    // TEST 6: Left-Left rotation
    {
        RedBlackTree tree;

        tree.insert("Charlie");
        tree.insert("Brian");
        tree.insert("Alex");

        check("LL Rotation",
              tree.containsUser("Charlie") &&
              tree.containsUser("Brian") &&
              tree.containsUser("Alex"));
    }

    // TEST 7: Right-Right rotation
    {
        RedBlackTree tree;

        tree.insert("Alex");
        tree.insert("Brian");
        tree.insert("Charlie");

        check("RR Rotation",
              tree.containsUser("Alex") &&
              tree.containsUser("Brian") &&
              tree.containsUser("Charlie"));
    }

    // TEST 8: Left-Right rotation
    {
        RedBlackTree tree;

        tree.insert("Charlie");
        tree.insert("Alex");
        tree.insert("Brian");

        check("LR Rotation",
              tree.containsUser("Charlie") &&
              tree.containsUser("Alex") &&
              tree.containsUser("Brian"));
    }

    // TEST 9: Right-Left rotation
    {
        RedBlackTree tree;

        tree.insert("Alex");
        tree.insert("Charlie");
        tree.insert("Brian");

        check("RL Rotation",
              tree.containsUser("Alex") &&
              tree.containsUser("Charlie") &&
              tree.containsUser("Brian"));
    }

    // TEST 10: Duplicate usernames
    {
        RedBlackTree tree;

        tree.insert("Alex");
        tree.insert("Alex");
        tree.insert("Brian");
        tree.insert("Brian");

        check("Duplicate Insertions",
              tree.containsUser("Alex") &&
              tree.containsUser("Brian") &&
              !tree.containsUser("Charlie"));
    }

    // TEST 11: Recoloring
    {
        RedBlackTree tree;

        tree.insert("David");
        tree.insert("Brian");
        tree.insert("Frank");
        tree.insert("Alex");

        check("Recoloring",
              tree.containsUser("David") &&
              tree.containsUser("Brian") &&
              tree.containsUser("Frank") &&
              tree.containsUser("Alex"));
    }

    // TEST 12: Sorted insertion
    {
        RedBlackTree tree;

        for (int i = 0; i < 1000; i++) {
            tree.insert("user_" + to_string(i));
        }

        bool valid = true;

        for (int i = 0; i < 1000; i++) {
            if (!tree.containsUser("user_" + to_string(i))) {
                valid = false;
                break;
            }
        }

        check("Sorted Insertions", valid);
    }

    // TEST 13: Large randomized dataset
    {
        RedBlackTree tree;
        Data_Generator generator;

        vector<string> followers;
        vector<string> following;

        generator.generateData(10000, followers, following);

        for (const string& username : followers) {
            tree.insert(username);
        }

        bool valid = true;

        for (const string& username : followers) {
            if (!tree.containsUser(username)) {
                valid = false;
                break;
            }
        }

        check("10,000 Random Usernames", valid);
    }

    cout << "\nRed-Black Tree Results: "
         << passed << "/" << total
         << " tests passed.\n";
}



int main() {

    // TEST 1: Small dataset with known results
    cout << "========== TEST 1: SMALL DATASET ==========\n";

    vector<string> followers = {"Alex", "Brian", "Chris", "David"};
    vector<string> following = {"Alex", "Chris", "Emma", "Frank"};

    Analyzer analyzer(followers, following);

    // Perform both relationship comparisons
    analyzer.difference_in_followers();
    analyzer.difference_in_following();

    // Display users who follow you but you don't follow back
    cout << "\nFollowers you don't follow back:\n";
    for (const string& username : analyzer.get_difference_followers()) {
        cout << username << endl;
    }

    // Display users you follow who don't follow you back
    cout << "\nUsers not following you back:\n";
    for (const string& username : analyzer.get_difference_following()) {
        cout << username << endl;
    }

    // Display mutual followers
    cout << "\nMutual followers:\n";
    for (const string& username : analyzer.get_mutual()) {
        cout << username << endl;
    }

    // Verify expected results
    bool test1Passed =
        analyzer.get_difference_followers() == vector<string>{"Brian", "David"} &&
        analyzer.get_difference_following() == vector<string>{"Emma", "Frank"} &&
        analyzer.get_mutual() == vector<string>{"Alex", "Chris"};

    cout << "\nTest 1: " << (test1Passed ? "PASSED" : "FAILED") << endl;


    // TEST 2: Large randomized dataset
    cout << "\n========== TEST 2: LARGE DATASET ==========\n";

    Data_Generator generator;

    vector<string> bigFollowers;
    vector<string> bigFollowing;

    generator.generateData(50000, bigFollowers, bigFollowing);

    Analyzer bigAnalyzer(bigFollowers, bigFollowing);

    bigAnalyzer.difference_in_followers();
    bigAnalyzer.difference_in_following();

    size_t followersOnly = bigAnalyzer.get_difference_followers().size();
    size_t followingOnly = bigAnalyzer.get_difference_following().size();
    size_t mutual = bigAnalyzer.get_mutual().size();

    cout << "Generated followers: " << bigFollowers.size() << endl;
    cout << "Generated following: " << bigFollowing.size() << endl;

    cout << "\nFollowers you don't follow back: " << followersOnly << endl;
    cout << "Users not following you back: " << followingOnly << endl;
    cout << "Mutual followers: " << mutual << endl;

    // Each dataset should be fully accounted for
    bool test2Passed =
        bigFollowers.size() == 50000 &&
        bigFollowing.size() == 50000 &&
        followersOnly + mutual == bigFollowers.size() &&
        followingOnly + mutual == bigFollowing.size();

    cout << "\nTest 2: " << (test2Passed ? "PASSED" : "FAILED") << endl;

    // TEST 3: Repeat analysis to check for duplicate results
    cout << "\n========== TEST 3: REPEATED ANALYSIS ==========\n";

    bigAnalyzer.difference_in_followers();
    bigAnalyzer.difference_in_following();

    bool test3Passed =
        bigAnalyzer.get_difference_followers().size() == followersOnly &&
        bigAnalyzer.get_difference_following().size() == followingOnly &&
        bigAnalyzer.get_mutual().size() == mutual;

    cout << "Test 3: " << (test3Passed ? "PASSED" : "FAILED") << endl;

    cout << "\n========== FINAL RESULT ==========\n";
    cout << ((test1Passed && test2Passed && test3Passed)
             ? "ALL TESTS PASSED!"
             : "ONE OR MORE TESTS FAILED!")
         << endl;

    testRedBlackTree();

    return (test1Passed && test2Passed && test3Passed) ? 0 : 1;
    
}
