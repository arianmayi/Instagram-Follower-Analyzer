//
// Created by arian on 10/15/2026.
//

#include "Display.h"
#include <algorithm>
#include <stdexcept>
using namespace std;

//DO NOT DELETE UNTIL NEAR END OF PROJECT - USE AS GUIDE

/*
 *Ngoc, this is your part of the project
 *Simple display
 *Draw Buttons, detect user clicks
 *Display totals
 *Make the UI look nice
 *SFML3
 */

Display::Display() : window(sf::VideoMode({1400, 1050}), "Instagram Follower Analyzer"),
                     titleText(font), subtitleText(font), statusText(font), loadText(font), generateText(font),
                     analyzeText(font), loadFollowersText(font), loadFollowingText(font), card1Text(font),
                     card2Text(font), card3Text(font), followersTotalText(font), followingTotalText(font),
                     resultsTitle(font), benchmarkTitle(font), notFollowingTabText(font), dontFollowTabText(font),
                     mutualTabText(font), datasetLabel(font), datasetInputText(font) {
    if (!font.openFromFile("../assets/Inter_18pt-Regular.ttf")) {
        throw runtime_error("Failed to load font");
    }

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
    titleText.setPosition({70.f, 55.f});
    titleText.setFillColor(sf::Color::White);

    subtitleText.setFont(font);
    subtitleText.setString("Follower Analysis Dashboard");
    subtitleText.setCharacterSize(20);
    subtitleText.setFillColor(sf::Color(180, 180, 200));
    subtitleText.setPosition({75.f, 110.f});

    statusText.setFont(font);
    statusText.setCharacterSize(18);
    statusText.setFillColor(sf::Color::Green);
    statusText.setPosition({1050.f, 90.f});
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
    analyzeText.setPosition({80.f, 342.f});
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
    card1Text.setPosition({80.f, 420.f});
    card1Text.setFillColor(sf::Color::White);

    card2Text.setFont(font);
    card2Text.setCharacterSize(26);
    card2Text.setStyle(sf::Text::Bold);
    card2Text.setPosition({520.f, 420.f});
    card2Text.setFillColor(sf::Color::White);

    card3Text.setFont(font);
    card3Text.setCharacterSize(26);
    card3Text.setStyle(sf::Text::Bold);
    card3Text.setPosition({960.f, 420.f});
    card3Text.setFillColor(sf::Color::White);

    followersTotalText.setFont(font);
    followersTotalText.setCharacterSize(18);
    followersTotalText.setPosition({850.f, 80.f});

    followingTotalText.setFont(font);
    followingTotalText.setCharacterSize(18);
    followingTotalText.setPosition({850.f, 110.f});

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
    notFollowingTabText.setPosition({95.f, 618.f});

    dontFollowTabText.setFont(font);
    dontFollowTabText.setCharacterSize(18);
    dontFollowTabText.setFillColor(sf::Color::White);
    dontFollowTabText.setString("You Don't Follow Back");
    dontFollowTabText.setPosition({530.f, 618.f});

    mutualTabText.setFont(font);
    mutualTabText.setCharacterSize(18);
    mutualTabText.setFillColor(sf::Color::White);
    mutualTabText.setString("Mutual");
    mutualTabText.setPosition({910.f, 618.f});

    // loadFollowersButton.setSize({620.f, 100.f});
    // loadFollowersButton.setPosition({40.f, 170.f});
    // loadFollowersText.setString("Load Followers");
    //
    // loadFollowingButton.setSize({620.f, 100.f});
    // loadFollowingButton.setPosition({700.f, 170.f});
    // loadFollowingText.setString("Load Following");
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
                generator.generateData(datasetSize, followers, following);
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
                if (firstDatasetClick) {
                    datasetInput.clear();
                    datasetInputText.setString("");
                    firstDatasetClick = false;
                }
            }
            else {
                enteringDatasetSize = false;
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

    window.display();
}

void Display::update() {
    if (enteringDatasetSize) {
        datasetInputBox.setOutlineColor(sf::Color(34, 134, 255));
    }
    else {
        datasetInputBox.setOutlineColor(sf::Color(60, 60, 120));
    }
}

bool Display::buttonPressed(const sf::RectangleShape& button, sf::Vector2f mousePos) {
    return button.getGlobalBounds().contains(mousePos);
}

void Display::loadJsonData() {
    currentView = ListView::NOT_FOLLOWING_BACK;

    bool followersLoaded = loader.load_followers("files/followers.json");
    bool followingLoaded = loader.load_following("files/following.json");

    analyzer.reset();
    scrollOffset = 0;

    if (followersLoaded && followingLoaded) {
        followers = loader.get_followers();
        following = loader.get_following();

        statusText.setFillColor(sf::Color::Green);
        statusText.setString("Loaded: " + to_string(followers.size()) + " followers and " + to_string(following.size()) + " following");
    }
    else {
        statusText.setFillColor(sf::Color::Red);
        statusText.setString("Failed to load JSON files");
    }
}