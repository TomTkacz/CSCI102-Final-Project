#include "connotations.hpp"
#include "band.hpp"
#include <array>
#include <iostream>

using namespace std;

#define NUMBER_OF_BAND_MEMBERS 4

AFINNParser parser("resource/AFINN-en-165.txt"); // parses the text file that contains the terms and their connotations
BandMember* bandMembers[NUMBER_OF_BAND_MEMBERS];

int numberOfRemainingTries = 3;
bool hasLost = false;

int main() {

    bandMembers[0] = new Vocalist(&parser,"Adam");
    bandMembers[1] = new Bassist(&parser,"Suzie");
    bandMembers[2] = new Drummer(&parser,"Mark");
    bandMembers[3] = new Guitarist(&parser,"Amanda");

    for (BandMember* bandMember : bandMembers) {

        bool canMoveOn = false;

        cout << bandMember->getBio() << endl;

        while (!canMoveOn) {

            cout << "You have " << numberOfRemainingTries << " tries left to get your bandmates to like you." << endl;
            cout << "Enter a song lyric that you think " << bandMember->getName() << " would like: ";

            char input[256];
            cin.getline(input,256); // stores entire line's input
            Feedback response = bandMember->getFeedback(input);

            // prints the band member's response the the lyrics
            cout << bandMember->getName() << " says: \"" << response.message << "\"" << endl;

            if (!response.isPositive)
                numberOfRemainingTries--;
            else
                canMoveOn = true;

            hasLost = numberOfRemainingTries == 0; 
            if (hasLost) break;

        }

        if (hasLost) break;

    }

    if (!hasLost) {
        cout << "YOU WIN!!!" << endl;
        return 0;
    }
    cout << "YOU LOSE!!!" << endl;

    return 0;
}