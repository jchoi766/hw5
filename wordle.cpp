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
    set<string> &words, 
		set<string> &prefix
		);

const set<string> getPrefixes(const set<string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> words;
		set<string> prefix = getPrefixes(dict);
    wordleHelper("", 0, in, floating, dict, words, prefix);
    return words;

}

// Define any helper functions here

const set<string> getPrefixes(const set<string>& dict) {
	set<string> prefixes;
	for (string word : dict) {
		for (int i = 1; i <= word.length(); i++){
			prefixes.insert(word.substr(0, i));
		}
	}
	return prefixes;
}

void wordleHelper(
    string curr,
    int index, 
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict,
    set<string> &words, 
		set<string> &prefix
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
        wordleHelper(curr+in[index], index+1, in, floating, dict, words, prefix);
    }
    else {
        // try adding on all floating letters as next letter 
        for (size_t i = 0; i < floating.length(); i++) {
            //remove the letter added from floating 
            string newFloating = floating.substr(0, i)+floating.substr(i+1);

						//check if this prefix is a viable prefix and worth recursing 
						string newCurr = curr + floating[i];
						if (prefix.find(newCurr) != prefix.end() ) {
							wordleHelper(newCurr, index+1, in, newFloating, dict, words, prefix);
						}
						
        }
        // try all a-z letters as next letter if more blanks than remaining floating left 
        if (in.length()-index > floating.length()) {
            // there are more potential spots than taken up by floating 
            for (char next = 'a'; next <= 'z'; next++) {
                // ignore duplicates (already tried w floating) 
                if (floating.find(next) == std::string::npos){ // trying a new letter 
									//check if this prefix is a viable prefix and worth recursing 
									string newCurr = curr + next;
									if (prefix.find(newCurr) != prefix.end() ) {
										wordleHelper(newCurr, index+1, in, floating, dict, words, prefix);
									}
                    
                }
            }
        }   
    }
    

}