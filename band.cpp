#include "band.hpp"

#include <iostream>
#include <random>
#include <time.h>

using namespace std;

Feedback BandMember::getFeedback(string lyric) {

    CONNOTATION lyricConnotation = parser->calculateConnotation(lyric);
    int connotationDelta = lyricConnotation - static_cast<int>( getIdealConnotation() );

    Feedback response = { justRightResponse, false };

    if     (connotationDelta < -5) {
        response.message = wayTooNegativeResponse;
    }
    else if (connotationDelta < -1) {
        response.message = tooNegativeResponse;
    }
    else if (connotationDelta > 5) {
        response.message = wayTooPositiveResponse;
    }
    else if (connotationDelta > 1) {
        response.message = tooPositiveResponse;
    }
    else {
        response.isPositive = true;
    }

    return response;

}

string BandMember::getBio() {
    string finalString = "";
    finalString += "Hi! I'm " + getName() + ", and I basically just " + getBandRole() + ". You said you had a song lyric you wanted me to hear?";
    return finalString;
}