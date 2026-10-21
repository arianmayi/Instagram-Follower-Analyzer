//
// Created by arian on 10/15/2026.
//

#ifndef PROJECT2_DATA_LOADER_H
#define PROJECT2_DATA_LOADER_H
#include<vector>
#include<string>
using namespace std;

/*
 *Purpose of this class:
 *Read the imported .json files
 *store following and followers for separate use
 */
class Data_Loader {

    private:

        //stores the files
        string followers_file;
        string following_file;

        //stores the following/follower data
        vector<string> followers;
        vector<string> following;

    public:

        Data_Loader();

        //returns true if the data was loaded/parsed correctly, else false.
        bool load_followers(const string& followers_file);
        bool load_following(const string& following_file);

        //getters for red-black & hash table build
        const vector<string>& get_followers() const;
        const vector<string>& get_following() const;

};

#endif //PROJECT2_DATA_LOADER_H
