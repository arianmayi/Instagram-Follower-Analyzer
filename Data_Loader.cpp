//
// Created by arian on 10/15/2026.
//

#include "Data_Loader.h"
#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;

/*
 *Purpose of this class:
 *Read the imported .json files
 *store following and followers for separate use
 */

//constructor
Data_Loader::Data_Loader() {};

//json alias
using json = nlohmann::json;

//load follower data from file
bool Data_Loader::load_followers(string &followers_file) {

    ifstream file(followers_file);

    if (!file.is_open()) {
        cout << "ERROR OPENING FILE" << endl;
        return false;
    }

    json data;
    file >> data;

    for (int i = 0; i < data.size(); i++) {
        string username = data[i]["string_list_data"][0]["value"].get<std::string>();
        followers.push_back(username);
    }
    return true;
}

//load following data from file
bool Data_Loader::load_following(string &following_file) {

    ifstream file(following_file);

    if (!file.is_open()) {
        cout << "ERROR OPENING FILE" << endl;
        return false;
    }

    json data;
    file >> data;

    for (int i = 0; i < data["relationships_following"].size(); i++) {
        string username = data["relationships_following"][i]["title"].get<std::string>();
        following.push_back(username);
    }
    return true;
}


//Gets vector of follower data
const vector<string>& Data_Loader::get_followers() const {
   return followers;
}

//Gets vector of following data
const vector<string>& Data_Loader::get_following() const {
    return following;
}


