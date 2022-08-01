#pragma once
#include <iostream>
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
    float score = 0;
};
