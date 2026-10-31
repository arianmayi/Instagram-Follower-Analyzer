
#include <iostream>
#include <vector>
#include <string>

#include "Analyzer.h"
#include "Data_Generator.h"

using namespace std;

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

    return (test1Passed && test2Passed && test3Passed) ? 0 : 1;
}
