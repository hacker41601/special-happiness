/*
 * File: WordLadder.h
 * Course: CS216-003
 * Project: Project 3
 * Purpose: Declaration of WordLadder class
 */

#ifndef WORDLADDER_H
#define WORDLADDER_H

#include "Graph.h"
#include <vector>
#include <stack>
#include <string>

using namespace std;

class WordLadder{

public:
// default constructor
WordLadder();

// alternative constructor
WordLadder(const vector<string>& words);

// to add a newword in the collection
void insertWord(string newword);

// return a graph from the group of words with the same lengths = length
// there is an edge between two words
// if two words are only different in a single letter
Graph<string> WordsGraph(int length) const;

// return a vector of words
// which represents a word ladder from word1 to word2
// any two adjacent words along the ladder differ in only one character
vector<string> getLadder(string word1, string word2) const;

private:
// Group all the words by the number of characters in each word:
// the private data member represents a mapping from the length (key)
// to a vector of words which contain length number of characters (value)
map<int, vector<string> > wordsByLength;
};

#endif


