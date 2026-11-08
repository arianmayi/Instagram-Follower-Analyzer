//
// Created by arian on 10/15/2026.
//

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <commdlg.h>

#include "Display.h"

#include <algorithm>
#include <stdexcept>
#include <optional>

using namespace std;

namespace {
    optional<string> selectJsonFile(const char* dialogTitle) {

        //stores the path selected by user
        char filePath[32768] = {};

        //configure the windows file selection
        OPENFILENAMEA dialog = {};
        dialog.lStructSize = sizeof(dialog);
        dialog.lpstrFile = filePath;
        dialog.nMaxFile = sizeof(filePath);

        //only show JSON files
        dialog.lpstrFilter = "JSON Files (*.json)\0*.json\0"
        "All Files (*.*)\0*,*\0";

        dialog.nFilterIndex = 1;
        dialog.lpstrTitle = dialogTitle;

        //only allow existing files and preserve the working directory
        dialog.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_NOCHANGEDIR;

        if (!GetOpenFileNameA(&dialog)) {
            return nullopt;
        }

        //return selected file path
        return string(filePath);
    }
}

Display::Display() : window(sf::VideoMode({1400, 1050}), "Instagram Follower Analyzer"),
                     titleText(font), subtitleText(font), statusText(font), loadText(font), generateText(font),
                     analyzeText(font), card1Text(font), card2Text(font), card3Text(font), followersTotalText(font),
                     followingTotalText(font), resultsTitle(font), benchmarkTitle(font), notFollowingTabText(font),
                     dontFollowTabText(font), mutualTabText(font), datasetLabel(font), datasetInputText(font),
                     overlapLabel(font), overlapInputText(font) {
    if (!font.openFromFile("assets/Inter_18pt-Regular.ttf")) {
        throw runtime_error("Failed to load font");
    }

    helpButton.setSize({45.f, 40.f});
    helpButton.setPosition({1290.f, 55.f});
    helpButton.setFillColor(sf::Color(45, 55, 100));
    helpButton.setOutlineThickness(1.f);
    helpButton.setOutlineColor(sf::Color::White);

    dashboardPanel.setSize({1360.f, 1000.f});
    dashboardPanel.setPosition({20.f, 20.f});
    dashboardPanel.setFillColor(sf::Color(8, 12, 32));
    dashboardPanel.setOutlineThickness(2.f);
    dashboardPanel.setOutlineColor(sf::Color(40, 60, 120));

    headerPanel.setSize({1310.f, 100.f});
    headerPanel.setPosition({40.f, 40.f});
    headerPanel.setFillColor(sf::Color(15, 20, 55));
    headerPanel.setOutlineThickness(1.f);
    headerPanel.setOutlineColor(sf::Color(70, 90, 170));

    titleText.setFont(font);
    titleText.setString("Instagram Follower Analyzer");
    titleText.setCharacterSize(48);
    titleText.setPosition({70.f, 50.f});
    titleText.setFillColor(sf::Color::White);

    subtitleText.setFont(font);
    subtitleText.setString("Follower Analysis Dashboard");
    subtitleText.setCharacterSize(20);
    subtitleText.setFillColor(sf::Color(180, 180, 200));
    subtitleText.setPosition({75.f, 110.f});

    statusText.setFont(font);
    statusText.setCharacterSize(18);
    statusText.setFillColor(sf::Color::Green);
    statusText.setPosition({1050.f, 75.f});
    statusText.setString("Ready");

    loadButton.setSize({620.f, 100.f});
    loadButton.setPosition({40.f, 170.f});
    loadButton.setFillColor(sf::Color(227, 22, 121));
    loadButton.setOutlineThickness(1.f);
    loadButton.setOutlineColor(sf::Color(80, 80, 80));

    generateButton.setSize({620.f, 100.f});
    generateButton.setPosition({700.f, 170.f});
    generateButton.setFillColor(sf::Color(34, 134, 255));
    generateButton.setOutlineThickness(1.f);
    generateButton.setOutlineColor(sf::Color(80, 80, 80));

    datasetLabel.setFont(font);
    datasetLabel.setCharacterSize(18);
    datasetLabel.setFillColor(sf::Color::White);
    datasetLabel.setString("Dataset Size:");
    datasetLabel.setPosition({40.f, 280.f});

    datasetInputBox.setSize({180.f, 40.f});
    datasetInputBox.setPosition({180.f, 272.f});
    datasetInputBox.setFillColor(sf::Color(20, 25, 65));
    datasetInputBox.setOutlineThickness(2.f);
    datasetInputBox.setOutlineColor(sf::Color(60, 60, 120));

    datasetInputText.setFont(font);
    datasetInputText.setCharacterSize(20);
    datasetInputText.setString(datasetInput);
    datasetInputText.setPosition({195.f, 278.f});
    datasetInputText.setFillColor(sf::Color::White);

    overlapLabel.setFont(font);
    overlapLabel.setCharacterSize(18);
    overlapLabel.setFillColor(sf::Color::White);
    overlapLabel.setString("Overlap %: ");
    overlapLabel.setPosition({400.f, 280.f});

    overlapInputBox.setSize({120.f, 40.f});
    overlapInputBox.setPosition({520.f, 272.f});
    overlapInputBox.setFillColor(sf::Color(20, 25, 65));
    overlapInputBox.setOutlineThickness(2.f);
    overlapInputBox.setOutlineColor(sf::Color(60, 60, 120));

    overlapInputText.setFont(font);
    overlapInputText.setCharacterSize(20);
    overlapInputText.setString(overlapInput);
    overlapInputText.setPosition({535.f, 278.f});
    overlapInputText.setFillColor(sf::Color::White);

    analyzeButton.setSize({1280.f, 60.f});
    analyzeButton.setPosition({40.f, 330.f});
    analyzeButton.setFillColor(sf::Color(20, 25, 65));
    analyzeButton.setOutlineThickness(1.f);
    analyzeButton.setOutlineColor(sf::Color(80, 80, 80));

    loadText.setFont(font);
    loadText.setCharacterSize(32);
    loadText.setString("Load JSON");
    loadText.setStyle(sf::Text::Bold);
    loadText.setPosition({260.f, 198.f});
    loadText.setFillColor(sf::Color::White);

    generateText.setFont(font);
    generateText.setCharacterSize(32);
    generateText.setString("Generate Data");
    generateText.setStyle(sf::Text::Bold);
    generateText.setPosition({900.f, 198.f});
    generateText.setFillColor(sf::Color::White);

    analyzeText.setFont(font);
    analyzeText.setCharacterSize(32);
    analyzeText.setString("Analyze Followers");
    analyzeText.setStyle(sf::Text::Bold);
    analyzeText.setPosition({530.f, 342.f});
    analyzeText.setFillColor(sf::Color::White);

    card1.setSize({400.f, 110.f});
    card1.setPosition({40.f, 420.f});
    card1.setFillColor(sf::Color(227, 22, 121));
    card1.setOutlineThickness(1.f);
    card1.setOutlineColor(sf::Color(60, 60, 60));

    card2.setSize({400.f, 110.f});
    card2.setPosition({480.f, 420.f});
    card2.setFillColor(sf::Color(150, 50, 255));
    card2.setOutlineThickness(1.f);
    card2.setOutlineColor(sf::Color(60, 60, 60));

    card3.setSize({400.f, 110.f});
    card3.setPosition({920.f, 420.f});
    card3.setFillColor(sf::Color(34, 134, 255));
    card3.setOutlineThickness(1.f);
    card3.setOutlineColor(sf::Color(60, 60, 60));

    card1Text.setFont(font);
    card1Text.setCharacterSize(26);
    card1Text.setStyle(sf::Text::Bold);
    card1Text.setPosition({80.f, 430.f});
    card1Text.setFillColor(sf::Color::White);

    card2Text.setFont(font);
    card2Text.setCharacterSize(26);
    card2Text.setStyle(sf::Text::Bold);
    card2Text.setPosition({520.f, 430.f});
    card2Text.setFillColor(sf::Color::White);

    card3Text.setFont(font);
    card3Text.setCharacterSize(26);
    card3Text.setStyle(sf::Text::Bold);
    card3Text.setPosition({960.f, 430.f});
    card3Text.setFillColor(sf::Color::White);

    followersTotalText.setFont(font);
    followersTotalText.setCharacterSize(18);
    followersTotalText.setPosition({850.f, 65.f});

    followingTotalText.setFont(font);
    followingTotalText.setCharacterSize(18);
    followingTotalText.setPosition({850.f, 95.f});

    resultsPanel.setSize({1280.f, 320.f});
    resultsPanel.setPosition({40.f, 530.f});
    resultsPanel.setFillColor(sf::Color(15, 20, 55));
    resultsPanel.setOutlineThickness(1.f);
    resultsPanel.setOutlineColor(sf::Color(60, 60, 60));

    benchmarkPanel.setSize({1280.f, 180.f});
    benchmarkPanel.setPosition({40.f, 840.f});
    benchmarkPanel.setFillColor(sf::Color(15, 20, 55));
    benchmarkPanel.setOutlineThickness(1.f);
    benchmarkPanel.setOutlineColor(sf::Color(60, 60, 60));

    resultsTitle.setFont(font);
    resultsTitle.setCharacterSize(28);
    resultsTitle.setStyle(sf::Text::Bold);
    resultsTitle.setString("Not Following Back");
    resultsTitle.setPosition({60.f, 545.f});
    resultsTitle.setFillColor(sf::Color::White);

    benchmarkTitle.setFont(font);
    benchmarkTitle.setCharacterSize(28);
    benchmarkTitle.setStyle(sf::Text::Bold);
    benchmarkTitle.setString("Performance Comparison");
    benchmarkTitle.setPosition({60.f, 855.f});
    benchmarkTitle.setFillColor(sf::Color::White);

    hashCard.setSize({600.f, 95.f});
    hashCard.setPosition({60.f, 900.f});
    hashCard.setFillColor(sf::Color(227, 22, 121));

    treeCard.setSize({600.f, 95.f});
    treeCard.setPosition({700.f, 900.f});
    treeCard.setFillColor(sf::Color(150, 50, 255));

    notFollowingTab.setSize({400.f, 40.f});
    notFollowingTab.setPosition({55.f, 610.f});

    dontFollowTab.setSize({400.f, 40.f});
    dontFollowTab.setPosition({478.f, 610.f});

    mutualTab.setSize({400.f, 40.f});
    mutualTab.setPosition({900.f, 610.f});

    notFollowingTabText.setFont(font);
    notFollowingTabText.setCharacterSize(18);
    notFollowingTabText.setFillColor(sf::Color::White);
    notFollowingTabText.setString("Not Following Back");
    notFollowingTabText.setPosition({90.f, 620.f});

    dontFollowTabText.setFont(font);
    dontFollowTabText.setCharacterSize(18);
    dontFollowTabText.setFillColor(sf::Color::White);
    dontFollowTabText.setString("You Don't Follow Back");
    dontFollowTabText.setPosition({515.f, 620.f});

    mutualTabText.setFont(font);
    mutualTabText.setCharacterSize(18);
    mutualTabText.setFillColor(sf::Color::White);
    mutualTabText.setString("Mutual");
    mutualTabText.setPosition({935.f, 620.f});
}

void Display::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Display::processEvents() {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
            sf::Vector2f mousePos = window.mapPixelToCoords({mouse->position.x, mouse->position.y});

            //open or close help menu when user clicks the "?" button

            if (buttonPressed(helpButton,mousePos)) {
                showHelp = !showHelp;
                continue;
            }

            //prevents other buttons from being clicked while help is open
            if (showHelp) {
                continue;
            }

            if (buttonPressed(loadButton, mousePos)) {
                loadJsonData();
            }
            if (buttonPressed(generateButton, mousePos)) {
                currentView = ListView::NOT_FOLLOWING_BACK;

                analyzer.reset();
                scrollOffset = 0;

                size_t datasetSize = 50000;
                if (!datasetInput.empty()) {
                    datasetSize = std::stoull(datasetInput);
                }
                datasetSize = std::max<size_t>(100, datasetSize);
                datasetSize = std::min<size_t>(100000, datasetSize);

                double overlapPercent = 25.0;
                if (!overlapInput.empty()) {
                    overlapPercent = std::stod(overlapInput);
                }
                overlapPercent = std::max(0.0, overlapPercent);
                overlapPercent = std::min(100.0, overlapPercent);

                generator.generateData(datasetSize, followers, following, overlapPercent);
                statusText.setString("Generated: " + to_string(datasetSize) + " users");
                statusText.setFillColor(sf::Color::Green);
            }
            if (buttonPressed(analyzeButton, mousePos)) {
                performAnalysis();
            }
            if (buttonPressed(notFollowingTab, mousePos)) {
                currentView = ListView::NOT_FOLLOWING_BACK;
                scrollOffset = 0;
            }
            if (buttonPressed(dontFollowTab, mousePos)) {
                currentView = ListView::YOU_DONT_FOLLOW_BACK;
                scrollOffset = 0;
            }
            if (buttonPressed(mutualTab, mousePos)) {
                currentView = ListView::MUTUAL;
                scrollOffset = 0;
            }
            if (datasetInputBox.getGlobalBounds().contains(mousePos)) {
                enteringDatasetSize = true;
                enteringOverlap = false;
                if (firstDatasetClick) {
                    datasetInput.clear();
                    datasetInputText.setString("");
                    firstDatasetClick = false;
                }
            }
            else if (overlapInputBox.getGlobalBounds().contains(mousePos)) {
                enteringOverlap = true;
                enteringDatasetSize = false;
                if (firstOverlapClick) {
                    overlapInput.clear();
                    overlapInputText.setString("");
                    firstOverlapClick = false;
                }
            }
            else {
                enteringDatasetSize = false;
                enteringOverlap = false;
            }
        }
        if (const auto* text = event->getIf<sf::Event::TextEntered>()) {
            if (enteringDatasetSize) {
                char c = static_cast<char>(text->unicode);
                if (isdigit(c)) {
                    if (datasetInput.size() < 6) {
                        datasetInput += c;
                    }
                }
                else if (text->unicode == 8 && !datasetInput.empty()) {
                    datasetInput.pop_back();
                }
                datasetInputText.setString(datasetInput);
            }
            if (enteringOverlap) {
                char c = static_cast<char>(text->unicode);
                if (isdigit(c)) {
                    if (overlapInput.size() < 3) {
                        overlapInput += c;
                        if (!overlapInput.empty()) {
                            int value = stoi(overlapInput);
                            if (value > 100) {
                                overlapInput = "100";
                            }
                        }
                    }
                }
                else if (text->unicode == 8 && !overlapInput.empty()) {
                    overlapInput.pop_back();
                }
                overlapInputText.setString(overlapInput);
            }
        }
        if (const auto* wheel = event->getIf<sf::Event::MouseWheelScrolled>()) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (resultsPanel.getGlobalBounds().contains(mousePos)) {
                if (wheel->delta > 0) {
                    scrollOffset -= 3;
                }
                else {
                    scrollOffset += 3;
                }
                scrollOffset = std::max(0, scrollOffset);
            }
        }
    }
}

void Display::performAnalysis() {
    if (followers.empty() || following.empty()) {
        statusText.setFillColor(sf::Color::Red);
        statusText.setString("Load or generate data first");
        return;
    }

    analyzer = make_unique<Analyzer>(followers, following);

    analyzer->difference_in_followers_HASH();
    analyzer->difference_in_following_HASH();
    analyzer->difference_in_followers_RB();
    analyzer->difference_in_following_RB();

    benchmarkResults = analyzer->benchMark_Performance();

    statusText.setFillColor(sf::Color::Green);
    statusText.setString("Analysis Complete");
}

void Display::drawStatistics() {
    window.draw(card1);
    window.draw(card2);
    window.draw(card3);

    if (analyzer) {
        card1Text.setString("Don't Follow Back\n" + to_string(analyzer->get_difference_following_hash().size()));
        card2Text.setString("You Don't Follow Back\n" + to_string(analyzer->get_difference_followers_hash().size()));
        card3Text.setString("Mutual Followers\n" + to_string(analyzer->get_mutual_hash().size()));
    }
    else {
        card1Text.setString("Don't Follow Back\n0");
        card2Text.setString("You Don't Follow Back\n0");
        card3Text.setString("Mutual Followers\n0");
    }

    window.draw(card1Text);
    window.draw(card2Text);
    window.draw(card3Text);
}

void Display::drawUsernameList() {
    const vector<string>* users = nullptr;

    window.draw(resultsPanel);
    window.draw(resultsTitle);

    notFollowingTab.setFillColor(currentView == ListView::NOT_FOLLOWING_BACK ? sf::Color(227,22,121) : sf::Color(40,40,40));
    dontFollowTab.setFillColor(currentView == ListView::YOU_DONT_FOLLOW_BACK ? sf::Color(150,55,255) : sf::Color(40,40,40));
    mutualTab.setFillColor(currentView == ListView::MUTUAL ? sf::Color(34,134,255) : sf::Color(40,40,40));


    window.draw(notFollowingTab);
    window.draw(dontFollowTab);
    window.draw(mutualTab);

    window.draw(notFollowingTabText);
    window.draw(dontFollowTabText);
    window.draw(mutualTabText);

    if (!analyzer) {
        sf::Text placeholder(font);

        placeholder.setCharacterSize(20);
        placeholder.setPosition({70.f, 650.f});
        placeholder.setString("No analysis data available");

        window.draw(placeholder);
        return;
    }

    if (analyzer) {
        notFollowingTabText.setString("Not Following You Back (" + to_string(analyzer->get_difference_following_hash().size()) + ")");
        dontFollowTabText.setString("People You Don't Follow Back (" + to_string(analyzer->get_difference_followers_hash().size()) + ")");
        mutualTabText.setString("Mutual Followers (" + to_string(analyzer->get_mutual_hash().size()) + ")");
    }

    switch (currentView) {
        case ListView::NOT_FOLLOWING_BACK:
            resultsTitle.setString("Not Following You Back");
            users = &analyzer->get_difference_following_hash();
            break;
        case ListView::YOU_DONT_FOLLOW_BACK:
            resultsTitle.setString("People You Don't Follow Back");
            users = &analyzer->get_difference_followers_hash();
            break;
        case ListView::MUTUAL:
            resultsTitle.setString("Mutual Followers");
            users = &analyzer->get_mutual_hash();
            break;
    }

    const int visibleRows = 9;

    int maxScroll = max(0, (int)(*users).size() - visibleRows);
    scrollOffset = min(scrollOffset, maxScroll);

    for (int i = 0; i < visibleRows; i++) {
        int index = scrollOffset + i;

        if (index >= (*users).size()) {
            break;
        }

        sf::Text user(font);
        sf::RectangleShape row;

        row.setSize({1200.f, 32.f});
        row.setPosition({55.f, 670.f + i * 28.f});
        row.setFillColor((i % 2 == 0) ? sf::Color(20, 25, 65) : sf::Color(15, 20, 55));

        window.draw(row);

        user.setCharacterSize(20);
        user.setPosition({70.f, 672.f + i * 28.f});
        user.setString((*users)[index]);

        window.draw(user);
    }
}

void Display::drawBenchmark() {
    window.draw(benchmarkPanel);
    window.draw(benchmarkTitle);

    //does not display the following/followers/mutual data until analyzer has finished
    //the comparison & benchmark
    if (!analyzer) {
        return;
    }

    window.draw(hashCard);
    window.draw(treeCard);

    sf::Text hashText(font);

    hashText.setCharacterSize(20);
    hashText.setPosition({100.f, 915.f});
    hashText.setString("Hash Table\n" "Insert: " + to_string(benchmarkResults.hash_insert_ms) + " ms\n" "Search: " + to_string(benchmarkResults.hash_search_ms) + " ms");

    window.draw(hashText);

    sf::Text RBText(font);

    RBText.setCharacterSize(20);
    RBText.setPosition({740.f, 915.f});
    RBText.setString("Red Black Tree\n" "Insert: " + to_string(benchmarkResults.RB_insert_ms) + " ms\n" + "Search: " + to_string(benchmarkResults.RB_search_ms) + " ms");

    window.draw(RBText);

    string insertWinner = benchmarkResults.hash_insert_ms < benchmarkResults.RB_insert_ms ? "Hash Table Faster" : "Red-Black Tree Faster";
    string searchWinner = benchmarkResults.hash_search_ms < benchmarkResults.RB_search_ms ? "Hash Table Faster" : "Red-Black Tree Faster";

    sf::Text winnerText(font);

    winnerText.setCharacterSize(18);
    winnerText.setPosition({500.f, 850.f});
    winnerText.setFillColor(sf::Color(80, 255, 120));
    winnerText.setString("Insertion Winner: " + insertWinner + "\nSearch Winner: " + searchWinner);

    window.draw(winnerText);
}

void Display::render() {
    window.clear(sf::Color(15, 15, 15));

    window.draw(dashboardPanel);
    window.draw(headerPanel);

    window.draw(titleText);
    window.draw(subtitleText);
    window.draw(statusText);

    window.draw(loadButton);
    window.draw(generateButton);

    window.draw(datasetLabel);
    window.draw(datasetInputBox);
    window.draw(datasetInputText);

    window.draw(overlapLabel);
    window.draw(overlapInputBox);
    window.draw(overlapInputText);

    window.draw(analyzeButton);

    window.draw(loadText);
    window.draw(generateText);
    window.draw(analyzeText);

    followersTotalText.setString("Followers: " + to_string(followers.size()));
    followingTotalText.setString("Following: " + to_string(following.size()));

    window.draw(followersTotalText);
    window.draw(followingTotalText);

    drawStatistics();
    drawUsernameList();
    drawBenchmark();

    if (showHelp) {
        drawHelp();
    }

    //draw help button
    window.draw(helpButton);

    //draw the question mark inside help button
    sf::Text helpText(font);
    helpText.setString("?");
    helpText.setCharacterSize(30);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition({1303.f,55.f});
    window.draw(helpText);

    window.display();
}

void Display::update() {
    if (enteringDatasetSize) {
        datasetInputBox.setOutlineColor(sf::Color(34, 134, 255));
    }
    else {
        datasetInputBox.setOutlineColor(sf::Color(60, 60, 120));
    }
    if (enteringOverlap) {
        overlapInputBox.setOutlineColor(sf::Color(34, 134, 255));
    }
    else {
        overlapInputBox.setOutlineColor(sf::Color(60, 60, 120));
    }
}

bool Display::buttonPressed(const sf::RectangleShape& button, sf::Vector2f mousePos) {
    return button.getGlobalBounds().contains(mousePos);
}

//SMFL display JSON files & generated data
void Display::loadJsonData() {

    //followers JSON file
    optional<string> followersPath = selectJsonFile("Select your Instagram Followers JSON file");

    if (!followersPath) {
        return;
    }

    //following JSON file
    optional<string> followingPath = selectJsonFile("Select your Instagram following JSON file");

    if (!followingPath) {
        return;
    }

    //temporary loader so failed imports don't overwrite the previously loaded datasets
    Data_Loader newLoader;

    bool followersLoaded = newLoader.load_followers(*followersPath);
    bool followingLoaded = newLoader.load_following(*followingPath);

    if (!followersLoaded || !followingLoaded) {
        statusText.setFillColor(sf::Color::Red);
        statusText.setString("Failed to load Instagram JSON files");
        return;
    }

    //stores successful JSON files
    followers = newLoader.get_followers();
    following = newLoader.get_following();

    analyzer.reset();
    scrollOffset = 0;
    currentView = ListView::NOT_FOLLOWING_BACK;

    statusText.setFillColor(sf::Color::Green);
    statusText.setString("JSON files loaded successfully");
}

//help function that helps users understand how the app works
void Display::drawHelp() {
    //Darken the dashboard while help is open
    sf::RectangleShape overlay({1400.f, 1050.f});
    overlay.setFillColor(sf::Color(0,0,0,190));
    window.draw(overlay);

    //help panel
    sf::RectangleShape panel({900.f,640.f});
    panel.setPosition({250.f,190.f});
    panel.setFillColor(sf::Color(20,25,65));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(80,110,200));
    window.draw(panel);

    //help title
    sf::Text title(font);
    title.setString("How to use Instagram Follower Analyzer");
    title.setCharacterSize(30);
    title.setFillColor(sf::Color::White);
    window.draw(title);

    sf::Text instructions(font);

    //simple instructions
    instructions.setString(
    "1. LOAD JSON\n"
    "   Select your Instagram followers and following JSON files (FOLLOWER FILE FIRST).\n\n"
    "2. GENERATE DATA\n"
    "   Or enter a dataset size and generate sample usernames.\n\n"
    "3. OVERLAP PERCENTAGE\n"
    "   Or enter an overlap percentage to change the amount of mutuals.\n\n"
    "3. ANALYZE FOLLOWERS\n"
    "   Click Analyze Followers to compare the datasets.\n\n"
    "4. VIEW RESULTS\n"
    "   Click the pink, purple, or blue tabs to switch lists.\n"
    "   Use your mouse wheel to scroll through usernames.\n\n"
    "5. PERFORMANCE COMPARISON\n"
    "   Compare Hash Table and Red-Black Tree execution times.\n"
    "   Lower execution time means faster performance."
    );

    instructions.setCharacterSize(21);
    instructions.setLineSpacing(1.15f);
    instructions.setPosition({290.f,220.f});
    instructions.setFillColor(sf::Color(220,225,240));
    window.draw(instructions);

    //tells user how to close the help panel
    sf::Text closeText(font);
    closeText.setString("Click ? again to return to dashboard");
    closeText.setCharacterSize(18);
    closeText.setPosition({290.f,780.f});
    closeText.setFillColor(sf::Color(100,200,255));
    window.draw(closeText);
}
