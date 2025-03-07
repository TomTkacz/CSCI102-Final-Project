#pragma once

#include "connotations.hpp"

#include <string>
#include <map>
#include <array>

using namespace std;

struct Feedback {
    string message;
    bool isPositive;
};

class BandMember {
public:
    BandMember(AFINNParser* parser, string inputName) : parser(parser), name(inputName) {}

    virtual string getBio();
    virtual CONNOTATION getIdealConnotation() = 0;

    Feedback getFeedback(string lyric);
    string getName() { return name; }
    // WordWithConnotation getWayOfDressing() { return wayOfDressing; } --scrapped for time
    virtual string getBandRole() = 0;
    // array<WordWithConnotation,3> getHobbies() { return hobbies; } --scrapped for time
    AFINNParser* parser;

protected:

    string name;
    // WordWithConnotation wayOfDressing; --scrapped for time
    // array<WordWithConnotation,3> hobbies; --scrapped for time

    string wayTooNegativeResponse = "You could at least TRY to write something with SOME positivity... what is this??";
    string tooNegativeResponse = "Oh... well, I was thinking of something a bit cheerier. Can you do that?";
    string tooPositiveResponse = "That's a bit... cheerier than I'd go for.";
    string wayTooPositiveResponse = "I'm gonna need something darker... like... a LOT darker.";
    string justRightResponse = "Now that's a powerful lyric! Love it!!!";

};

class Vocalist : public BandMember {
public:
    Vocalist(AFINNParser* parser, string inputName) : BandMember(parser,inputName) {}
    CONNOTATION getIdealConnotation() { return VeryPositive; }
    string getBandRole() { return "sing the songs"; }
};

class Bassist : public BandMember {
public:
    Bassist(AFINNParser* parser, string inputName) : BandMember(parser,inputName) {}
    CONNOTATION getIdealConnotation() { return ExtremelyNegative; }
    string getBandRole() { return "play the bass"; }
};

class Drummer : public BandMember {
public:
    Drummer(AFINNParser* parser, string inputName) : BandMember(parser,inputName) {}
    CONNOTATION getIdealConnotation() { return BarelyNegative; }
    string getBandRole() { return "play the drums"; }
};

class Guitarist : public BandMember {
public:
    Guitarist(AFINNParser* parser, string inputName) : BandMember(parser,inputName) {}
    CONNOTATION getIdealConnotation() { return Positive; }
    string getBandRole() { return "play the guitar"; }
};