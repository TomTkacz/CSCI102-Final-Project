#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

// AFINN's connotation scoring scale goes form -5 to 5, this gives each score a name
enum CONNOTATION { ExtremelyNegative=-5, VeryNegative, Negative, AlmostNegative, BarelyNegative, Neutral, BarelyPositive, AlmostPositive, Positive, VeryPositive, ExtremelyPositive };

/* -- scrapped for time --
struct WordWithConnotation {
    string word;
    CONNOTATION connotation;
};
*/

class AFINNParser {
public:
    AFINNParser(string fileName);
    CONNOTATION getWordConnotation(string word);
    CONNOTATION calculateConnotation(string phrase);
    // WordWithConnotation getRandomWord(); --scrapped for time
    // WordWithConnotation getRandomVerb(); --scrapped for time
    // WordWithConnotation getRandomAdjective(); --scrapped for time
private: 
    vector<string> words;
    // vector<string> verbs; --scrapped for time
    // vector<string> adjectives; --scrapped for time
    map<string,CONNOTATION> connotations;
};