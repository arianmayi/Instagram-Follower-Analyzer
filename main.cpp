#include <iostream>
#include "Data_Loader.h"

using namespace std;
int main() {

    //test 1
    //data loader obj
    //testing follower file (real data)
    Data_Loader loader;

    //file name
    string filename = "followers_1.json";

    //check if file is loaded correctly
    loader.load_followers(filename);

    cout << loader.get_followers().size() << endl;


    return 0;
}