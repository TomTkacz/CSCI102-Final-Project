#include "connotations.hpp"

#include <fstream>
#include <regex>
#include <random>
#include <time.h>
#include <iostream>

using namespace std;

AFINNParser::AFINNParser(string fileName) {

    ifstream file(fileName);
    string line;

    if (file.is_open()) {
        while (getline(file,line)) {

            // using regular expressions to parse the sentiment analysis file
            regex searchExpression(R"([^\t]+)");
            smatch match;
            string values[2];
            int i=0;

            // SOURCED FROM https://stackoverflow.com/a/35026140/21030228
            string::const_iterator searchStart( line.cbegin() );
            while ( regex_search( searchStart, line.cend(), match, searchExpression ) ) {
            // END OF SOURCE
                values[i] = match[0];
                searchStart = match.suffix().first;
                i++;
            }
            
            // stores the word and converts its connotation to a CONNOTATION
            string word = values[0];
            CONNOTATION wordConnotation = static_cast<CONNOTATION>( stoi( values[1] ) );

            // adds the word to a vector and its connotation to a map at index [the word]
            connotations[word] = wordConnotation;
            words.push_back(word);

            /* -- scrapped for time --
            if ( word.length() < 3 ) continue;

            string lastThreeLetters = word.substr(word.length()-3,word.length());
            
            if ( lastThreeLetters == "ing" )
                verbs.push_back(word);

            if ( lastThreeLetters == "ial" || lastThreeLetters == "ful" || lastThreeLetters == "ous")
                adjectives.push_back(word);
            */

        }
        file.close();

    }
    else {
        throw runtime_error("Error opening '" + fileName + "'.");
    }

}

CONNOTATION AFINNParser::getWordConnotation(string word) {
    if (!connotations.count(word)) throw invalid_argument("The key '" + word + "' was not found.");
    return connotations[word];
}

/* -- scrapped for time --
WordWithConnotation AFINNParser::getRandomWord() {
    int index = rand() % words.size();
    return WordWithConnotation { words[index], getWordConnotation(words[index]) };
}

WordWithConnotation AFINNParser::getRandomVerb() {
    int index = rand() % verbs.size();
    return WordWithConnotation { verbs[index], getWordConnotation(verbs[index]) };
}

WordWithConnotation AFINNParser::getRandomAdjective() {
    int index = rand() % adjectives.size();
    return WordWithConnotation { adjectives[index], getWordConnotation(adjectives[index]) }; 
}
*/

CONNOTATION AFINNParser::calculateConnotation(string phrase) {


    regex searchExpression(R"([^\s.?!,"]+)");
    smatch match;

    int connotationScore = 0;
    int numberOfWords = 0;

    // SOURCED FROM https://stackoverflow.com/a/35026140/21030228
    string::const_iterator searchStart( phrase.cbegin() );
    while ( regex_search( searchStart, phrase.cend(), match, searchExpression ) ) {
    // END OF SOURCE

        try {
            connotationScore += getWordConnotation( match[0] );
        }
        catch (...) {} // if a word was not indexed, it does not contribute to the connotation score
        
        searchStart = match.suffix().first;
        numberOfWords++;

    }

    double percentOfConnotatedWords = 0.2; // the percent (out of 1) of words that would need to be positive for the overall score to be ExtremelyPositive
    int sign = connotationScore < 0 ? -1 : 1;
    double boundedConnotationScore = (double)abs(connotationScore) / ( (double)numberOfWords * 5.0 * percentOfConnotatedWords ) * 5.0 * sign;
    int finalScore = boundedConnotationScore + 0.5; 

    // bounds the connotation score
    if (finalScore > 5) finalScore = 5;
    if (finalScore < -5) finalScore = -5;

    return static_cast<CONNOTATION>( finalScore );

}