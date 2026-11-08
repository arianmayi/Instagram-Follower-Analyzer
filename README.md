# Instagram Follower Analyzer:

## Project Overview:

The Instagram Follower Analyzer is an application that allows users to analyze their Instagram followers and following lists. It compares two custom-built data structures, a Hash Table and a Red-Black Tree, to determine follower relationships and evaluate the performance between data structures.

The application features a graphical user interface built using SFML 3, allowing users to upload their Instagram data or generate randomized datasets for testing.

## Purpose of the Project - Features

The application determines:
- The total number of accounts following you.
- The total number of accounts you follow.
- Accounts you follow that do not follow you back.
- Mutual followers (accounts where both users follow each other).
- The performance differences between Hash Table and Red-Black Tree insertion and search operations.

## Installation & Setup

The project uses CMake with SFML 3 and nlohmann/json

## How to Use the Application

IMPORTANT: In CLion, set the project2 run configurations working directory to $ProjectFileDir$ to ensure the application loads the font from the assets folder correctly. (Ignore if no error was found when building)

## Option 1: Instagram Data (Recommended)

Export your Instagram data through Accounts Center -> Your information and permissions -> Export your information.

For the export, select:
- Information: Followers and Following only
- Data Range: All time (IMPORTANT)
- Format: JSON (WILL NOT WORK IN HTML)
- Pick an option to download your information, will be delivered in a couple of minutes

Extract the downloaded ZIP file, locate followers.json and following.json

In the application, select LOAD JSON, choose your followers file (ORDER MATTERS), then the following file. Click Analyze Followers.

## Option 2: Generated Data (FOR COMPLEXITY COMPARISON - LARGER DATA SETS)

Enter a dataset size (100 - 100,000). Click Generate Data, then Analyze Followers.

## Results

Use the three tabs to switch between accounts not following you back, accounts you don't follow back, and mutual followers. Scroll to view entire list.

The Performance Comparison section displays Hash Table and Red-Black tree insertion/search times in milliseconds.

Click ? for in-app instructions on the top right of the application.

