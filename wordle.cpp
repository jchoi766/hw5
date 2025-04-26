#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    string curr,
    int index, 
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    set<string> &words);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> words;
    wordleHelper("", 0, in, floating, dict, words);
    return words;

}

// Define any helper functions here
void wordleHelper(
    string curr,
    int index, 
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    set<string> &words
)
{
    // if current word is done, check if potential solution 
    if (index == in.length()) {
        if ((floating.size() == 0) && (dict.find(curr) != dict.end())){
            words.insert(curr);
        }
        return; // done with this combination 
    }
    // if fixed letter, add fixed letter to current index 
    if (in[index] != '-') {
        wordleHelper(curr+in[index], index+1, in, floating, dict, words);
    }
    else {
        // try adding on all floating letters as next letter 
        for (size_t i = 0; i < floating.length(); i++) {
            //remove the letter added from floating 
            string newFloating = floating.substr(0, i)+floating.substr(i+1);
            wordleHelper(curr+floating[i], index+1, in, newFloating, dict, words);
        }
        // try all a-z letters as next letter if more blanks than remaining floating left 
        if (in.length()-index > floating.length()) {
            // there are more potential spots than taken up by floating 
            for (char next = 'a'; next <= 'z'; next++) {
                // ignore duplicates (already tried w floating) 
                if (floating.find(next) == std::string::npos){ // trying a new letter 
                    wordleHelper(curr+next, index+1, in, floating, dict, words);
                }
            }
        }   
    }
    

}