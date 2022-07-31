#include <iostream>
#include <unordered_map>
#include <vector>
#include "Song.h"
#include "Sorts.h"
#include <chrono>
using namespace std::chrono;

void checkInput(string& input) {
    while (input != "0" && input != "1") {
        cout << "Invalid Entry. Enter \"0\" for no or \"1\" for yes. ";
        cin >> input;
    }
}

void checkRank(string& input) {
    while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5") {
        cout << "Please enter a valid ranking. ";
        cin >> input;
    }
}

int main() {
    string input;
    int length;
    int year;
    bool danceability;
    bool energy;
    bool loudness;
    bool acousticness;
    bool exp;
    unordered_map<string, int> rank;
    vector<Song*> songs;

    cout << "Hello! Welcome to the Playlist Generator." << endl;
    cout << "How many songs would you like in your playlist? ";
    bool valid = false;
    while (!valid) {
        cin >> input;
        try {
            length = abs(stoi(input));
            valid = true;
        } catch(invalid_argument&) {
            cout << "Please enter a valid number. ";
        }
    }

    cout << endl;
    cout << "Great! Your playlist will include " << length << " songs. " << endl;
    cout << "Now we will ask you some questions about your playlist: " << endl;

    cout << endl;
    cout << "Is there any specific year that you would like your songs to be from? " << endl;
    cout << "Enter \"0\" if not. ";
    cin >> input;
    year = stoi(input);

    cout << endl;
    cout << "Would you like your songs to have higher danceability?" << endl;
    cout << "Enter \"0\" for no or \"1\" for yes. ";
    cin >> input;
    checkInput(input);
    danceability = stoi(input);

    cout << endl;
    cout << "Would you like your songs to have more energy?" << endl;
    cout << "Enter \"0\" for no or \"1\" for yes. ";
    cin >> input;
    checkInput(input);
    energy = stoi(input);

    cout << endl;
    cout << "Would you like your songs to be loud?" << endl;
    cout << "Enter \"0\" for no or \"1\" for yes. ";
    cin >> input;
    checkInput(input);
    loudness = stoi(input);

    cout << endl;
    cout << "Would you like your songs to be more acoustic?" << endl;
    cout << "Enter \"0\" for no or \"1\" for yes. ";
    cin >> input;
    checkInput(input);
    acousticness = stoi(input);

    cout << endl;
    cout << "We will create your playlist using your year, danceability," << endl;
    cout << "energy, loudness, and acoustic preferences." << endl;
    cout << "You will now rank these qualities from 1 - 5, with" << endl;
    cout << "5 being least important to 1 being most important." << endl;

    cout << endl;
    cout << "Please enter your rank for each quality: " << endl;
    cout << "Year: ";
    cin >> input;
    checkRank(input);
    rank["year"] = 6 - stoi(input);
    cout << "Danceability: ";
    cin >> input;
    checkRank(input);
    rank["danceability"] = 6 - stoi(input);
    cout << "Energy: ";
    cin >> input;
    checkRank(input);
    rank["energy"] = 6 - stoi(input);
    cout << "Loudness: ";
    cin >> input;
    checkRank(input);
    rank["loudness"] = 6 - stoi(input);
    cout << "Acousticness: ";
    cin >> input;
    checkRank(input);
    rank["acousticness"] = 6 - stoi(input);

    for (int i = 0; i < songs.size(); i++) {
        if (year == 0) {
            songs[i]->score += rank["year"];
        } else {
            float yearPoints = abs(2022 - songs[i]->year);
            yearPoints = yearPoints / 2022;
            yearPoints = 1 - yearPoints;
            songs[i]->score += rank["year"] * yearPoints;
        }

        if (danceability) {
            songs[i]->score += rank["danceability"] * songs[i]->danceability;
        } else {
            songs[i]->score += rank["danceability"] * (1 - songs[i]->danceability);
        }

        if (energy) {
            songs[i]->score += rank["energy"] * songs[i]->energy;
        } else {
            songs[i]->score += rank["energy"] * (1 - songs[i]->energy);
        }

        float loudPoints;
        if (songs[i]->loudness >= 0) {
            loudPoints = songs[i]->loudness + 60;
        } else {
            loudPoints = 60 - abs(songs[i]->loudness);
        }
        loudPoints = loudPoints / 67.23;
        if (loudness) {
            songs[i]->score += rank["loudness"] * loudPoints;
        } else {
            songs[i]->score += rank["loudness"] * (1 - loudPoints);
        }

        if (acousticness) {
            songs[i]->score += rank["acousticness"] * songs[i]->acousticness;
        } else {
            songs[i]->score += rank["acousticness"] * (1 - songs[i]->acousticness);
        }
    }

    Sorts sorter;
    vector<Song*> copy = songs;
    // Time it takes to sort vector with Quicksort
    auto start = high_resolution_clock::now();
    sorter.quickSort(songs);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << endl;
    cout << "Quicksort time: " << duration.count() << " microseconds" << endl;
    // Time it takes to sort vector with Timsort
    start = high_resolution_clock::now();
    sorter.timSort(copy);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Timsort time: " << duration.count() << " microseconds" << endl;


    cout << endl;
    cout << "Would you like your playlist to include explicit songs?" << endl;
    cout << "Enter \"0\" for no and \"1\" for yes. ";
    cin >> input;
    exp = stoi(input);

    cout << endl;
    cout << "Here is your personalized playlist: " << endl;

    // Print out all valid songs
    int index = 0;
    for (int j = 0; j < length; j++) {
        if (exp) {
            cout << j + 1 << ". " << songs[j]->title << " by " << songs[j]->artist << endl;
        } else {
            for (int k = index; k < songs.size(); k++) {
                if (!songs[k]->exp) {
                    cout << k + 1 << ". " << songs[k]->title << " by " << songs[k]->artist << endl;
                    index = k + 1;
                    break;
                }
            }
        }
    }
    
    return 0;
}
