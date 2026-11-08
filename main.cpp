
#include <iostream>
#include <vector>
#include <string>

#include "Analyzer.h"
#include "Data_Generator.h"
#include "Display.h"

using namespace std;

int main() {


    //vectors to be filled for testing
    vector<string> following;
    vector<string> followers;

    //generate random data
    Data_Generator generateData;
    int data_points = 50000;

    //fill the vectors with the random data generated
    generateData.generateData(data_points, following,followers);

    //use analysis
    Analyzer analysis(followers,following);

    //Hash table analysis
    analysis.difference_in_following_HASH();
    analysis.difference_in_followers_HASH();

    //Red-Black analysis
    analysis.difference_in_following_RB();
    analysis.difference_in_followers_RB();

    //Hash Table results
    vector<string> hash_following_difference= analysis.get_difference_following_hash();
    vector<string> hash_follower_difference = analysis.get_difference_followers_hash();
    vector<string> hash_mutual = analysis.get_mutual_hash();

    //Red Black results
    vector<string> RB_following_difference= analysis.get_difference_following_RB();
    vector<string> RB_follower_difference = analysis.get_difference_followers_RB();
    vector<string> RB_mutual = analysis.get_mutual_RB();

    BenchMarkResults results = analysis.benchMark_Performance();


    //Display the number of followers and following the user has
    cout << endl;

    cout << "# OF USERS YOU FOLLOW: " << following.size() << endl;
    cout << "# OF USERS FOLLOW YOU: " << followers.size() << endl << endl;

    cout << "NOT FOLLOWING YOU BACK: " << hash_following_difference.size() << endl;
    cout << "YOU DON'T FOLLOW BACK: " << hash_follower_difference.size() << endl;
    cout << "# OF MUTUAL: " << hash_mutual.size() << endl;

    cout << "===========================================================" << endl;
    cout << "DIFFERENCE IN PERFORMANCE WILL BE DISPLAYED IN MILLISECONDS" << endl;
    cout << "===========================================================" << endl;

    cout << "Hash Insert: " << results.hash_insert_ms << "ms" << endl;
    cout << "Hash Search: " << results.hash_search_ms << "ms" << endl;

    cout << "===========================================================" << endl;

    cout << "Red-Black Insert: " << results.RB_insert_ms << "ms" << endl;
    cout << "Red-Black Search: " << results.RB_search_ms << "ms" << endl;

    Display display;
    display.run();
}
