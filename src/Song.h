#pragma once
#using <iostream>
using namespace std;

class Song {
public:
    string title;
    string artist;
    bool exp; // whether a song is explicit or not
    float danceability;
    float energy;
    float loudness;
    float acousticness;
    int year;
    int score = 0;
};
