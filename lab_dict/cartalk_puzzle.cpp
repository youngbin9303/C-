/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<StringTriple> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    /* Your code goes here! */
    vector<StringTriple> output;
    vector<string> word_vector;
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open())
    {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word))
        {
            if (word.length() == 5)
                word_vector.push_back(word);
        }
    }
    for (auto & key_word : word_vector)
    {
        string remove_first = key_word.substr(1);
        string remove_second;
        remove_second.append(key_word.begin(), key_word.begin()+1);
        remove_second.append(remove_first.begin()+1,remove_first.end());
        if (d.homophones(key_word, remove_first) && d.homophones(remove_first, remove_second) && d.homophones(remove_second, key_word))
        {
            StringTriple answer;
            get<0>(answer) = key_word;
            get<1>(answer) = remove_first;
            get<2>(answer) = remove_second;
            output.push_back(answer);
        }
        
        
    }
    return output;
}

