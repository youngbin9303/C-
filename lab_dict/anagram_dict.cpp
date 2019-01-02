/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    vector<string> word_to_add;
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open())
    {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word))
        {
            word_to_add.push_back(word);
        }
    }
    for (auto & key_word : word_to_add)
    {
        auto lookup = dict.find(key_word);
        if (lookup == dict.end())
        {
            std::vector<char> char_vector;
            for (size_t i=0; i<key_word.length(); i++)
                char_vector.push_back(key_word[i]);
            std::sort(char_vector.begin(), char_vector.end());
            dict.insert(std::pair<string, std::vector<char>>(key_word, char_vector));
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (auto & key_word : words)
    {
        auto lookup = dict.find(key_word);
        if (lookup == dict.end())
        {
            vector<char> char_vector;
            for (size_t i=0; i<key_word.length(); i++)
                char_vector.push_back(key_word[i]);
            std::sort(char_vector.begin(), char_vector.end());
            dict.insert(std::pair<string, std::vector<char>>(key_word, char_vector));
        }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    vector<string> output;
    output = anagrams(word);
    if (output.size() > 1)
        return output;
    else 
	return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> output;
    for (auto & key_word : dict)
    {
        string word = key_word.first;
        vector<string> temp_vector = anagrams(word);
        if (temp_vector.size() > 1)
            output.push_back(temp_vector);
    }
    return output;
}

//get_anagrams helper
vector<string> AnagramDict::anagrams(const string & word) const
{
    vector<string> output;
    auto lookup = dict.find(word);
    if (lookup == dict.end())
        return vector<string>();
    else
    {
        vector<char> char_vector_of_the_word = (*lookup).second;
        for (auto & key_word : dict)
        {
            if (key_word.second == char_vector_of_the_word)
                output.push_back(key_word.first);
        }
        return output;
    }
}


