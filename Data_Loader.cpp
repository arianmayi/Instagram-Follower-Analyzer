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

/*
 * Real data FYI
 *
 * Example JSON structure for followers:
 *
 * [
 *   {
 *     "title": "",
 *     "string_list_data": [
 *       {
 *         "value": "twofold.harmony"
 *       }
 *     ]
 *   }
 * ]
 *
 * Username path: data[i]["string_list_data"][0]["value"]
 */

/*
 * Also real data
 *
 * Example JSON structure for following:
 *
 * {
 *   "relationships_following": [
 *     {
 *       "title": "valelives"
 *     }
 *   ]
 * }
 *
 * Username path: data["relationships_following"][i]["title"]
 */

//constructor
Data_Loader::Data_Loader() {};

//JSON alias
using json = nlohmann::json;

//load follower data from file
bool Data_Loader::load_followers(const string &followers_file) {

    //temp vectors in case of mismatch data along the way...
    //if we have 500 followers but #300 is invalid, 299 will be pushed. we dont want that.
    vector<string> temp_followers;

    try {
        ifstream file(followers_file);

        if (!file.is_open()) {
            throw runtime_error("Error opening file: " + followers_file);
        }

        json data;
        file >> data;

        //first, validate the follower JSON file starts w/ an array.
        if (!data.is_array()) {
            throw runtime_error("Invalid followers JSON: expected an array []");
        }

        if (data.empty()) {
            throw runtime_error("No followers found");
        }

        //loop through JSON file, validate, push.
        for (int i = 0; i < data.size(); i++) {

            //make sure the data obj is a JSON obj {}
            if (!data[i].is_object()) {
                throw runtime_error("Invalid follower: expected JSON object {}");
            }

            //make sure string_list_data exists
            if (!data[i].contains("string_list_data")) {
                throw runtime_error("Invalid format: missing data");
            }

            //make sure string_list_data is type []. Instagram JSON format requirement.
            if (!data[i]["string_list_data"].is_array()) {
                throw runtime_error("Expected array []");
            }

            //if the string_list_data doesn't contain anything, no point of continuing.
            if (data[i]["string_list_data"].empty()) {
                throw runtime_error("array is empty");
            }

            //make sure that the value,username is within a {} (JSON obj)
            if (!data[i]["string_list_data"][0].is_object()) {
                throw runtime_error("Expected object type {}");
            }

            //make sure there is a string called value which is associated to username
            if (!data[i]["string_list_data"][0].contains("value")) {
                throw runtime_error("value not found");
            }

            //username has to be a string
            if (!data[i]["string_list_data"][0]["value"].is_string()) {
                throw runtime_error("Expected string value");
            }

            //empty string ""
            if (data[i]["string_list_data"][0]["value"].empty()) {
                throw runtime_error("username not found");
            }

            //if everything is passed, push back valid username
            string username = data[i]["string_list_data"][0]["value"].get<std::string>();
            temp_followers.push_back(username);
        }
    }
    catch (const runtime_error& e) {
        cout << "RUNTIME ERROR: " << e.what() << endl;
        return false;
    }
    //probably will never execute... but just in case
    catch (const exception& e) {
        cout << "GENERAL EXCEPTION: " << e.what() << endl;
        return false;
    }
    followers = temp_followers;
    return true;
}

//load following data from file
bool Data_Loader::load_following(const string &following_file) {

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


