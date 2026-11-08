//
// Created by arian on 10/15/2026.
//

#ifndef PROJECT2_DISPLAY_H
#define PROJECT2_DISPLAY_H

#include <SFML/Graphics.hpp>
#include "Analyzer.h"
#include "Data_Generator.h"
#include "Data_Loader.h"
#include <memory>
#include <string>
#include <vector>
using namespace std;

enum class ListView {
    NOT_FOLLOWING_BACK, YOU_DONT_FOLLOW_BACK, MUTUAL
};

class Display {
private:
    sf::RenderWindow window;
    sf::Font font;

    Data_Loader loader;
    Data_Generator generator;

    vector<string> followers;
    vector<string> following;

    unique_ptr<Analyzer> analyzer;
    BenchMarkResults benchmarkResults;

    sf::RectangleShape dashboardPanel;
    sf::RectangleShape headerPanel;

    sf::RectangleShape loadButton;
    sf::RectangleShape generateButton;
    sf::RectangleShape analyzeButton;

    sf::RectangleShape card1;
    sf::RectangleShape card2;
    sf::RectangleShape card3;
    sf::RectangleShape hashCard;
    sf::RectangleShape treeCard;

    sf::RectangleShape resultsPanel;
    sf::RectangleShape benchmarkPanel;

    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text statusText;

    sf::Text loadText;
    sf::Text generateText;
    sf::Text analyzeText;

    sf::Text card1Text;
    sf::Text card2Text;
    sf::Text card3Text;

    sf::Text followersTotalText;
    sf::Text followingTotalText;

    sf::Text resultsTitle;
    sf::Text benchmarkTitle;

    int scrollOffset = 0;

    sf::RectangleShape notFollowingTab;
    sf::RectangleShape dontFollowTab;
    sf::RectangleShape mutualTab;

    sf::Text notFollowingTabText;
    sf::Text dontFollowTabText;
    sf::Text mutualTabText;

    sf::RectangleShape datasetInputBox;

    sf::Text datasetLabel;
    sf::Text datasetInputText;

    string datasetInput = "50000";
    bool enteringDatasetSize = false;
    bool firstDatasetClick = true;

    sf::RectangleShape overlapInputBox;

    sf::Text overlapLabel;
    sf::Text overlapInputText;

    string overlapInput = "25";
    bool enteringOverlap = false;
    bool firstOverlapClick = true;

    //Help menu
    sf::RectangleShape helpButton;
    bool showHelp = false;

    ListView currentView = ListView::NOT_FOLLOWING_BACK;

public:
    Display();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void drawStatistics();
    void drawUsernameList();
    void drawBenchmark();
    void performAnalysis();
    bool buttonPressed(const sf::RectangleShape& button, sf::Vector2f mousePos);
    void loadJsonData();
    void drawHelp();
};

#endif //PROJECT2_DISPLAY_H
