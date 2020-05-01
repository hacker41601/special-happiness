/*
 * File: WordLadder.cpp
 * Course: CS216-003
 * Project: Project 3 
 * Purpose: Provide the implementation of WordLadder class
 */

#ifndef WORDLADDER_CPP
#define WORDLADDER_CPP

#include "WordLadder.h"
#include "Graph.h"

// default constructor
WordLadder::WordLadder()
{
// blank on purpose!!!!!!!!
}

// alternative constructor
WordLadder::WordLadder(const vector<string>& words)
{
    for(string word: words)
    {
	    insertWord(word);
    }
}

// to add a newword in the collection based on length
void WordLadder::insertWord(string newword)
{
    wordsByLength[newword.length()].push_back(newword);
}

// return a graph from the group of words with the same lengths = length
// there is an edge between two words
// if two words are only different in a single letter
// this function will be called by getLadder
// make buckets for them!

Graph<string> WordLadder::WordsGraph(int length) const
{
	Graph<string> groupWords;
	map<string, vector<string>> buckets;
	vector<string> words = wordsByLength.find(length)->second;

// make buckets with '?'

// for each word in the bucket of words with the same length
for (auto i = 0; i < words.size(); i++){

	//for each letter in the word
	for (auto j = 0; j < words[i].length(); j++){

		// see if bucket for the words exists
		// else - make new bucket and add the word
		string tempWord = words[i];
		tempWord.at(j) = '?';

		if (buckets.find(tempWord) == buckets.end()){
			vector<string> tempBucket;
			tempBucket.push_back(words[i]);
			buckets[tempWord] = tempBucket;
		}
		else{
			buckets.find(tempWord)->second.push_back(words[i]);
		}
	} //end for loop for the word

} //end for loop comparing words

//add vertices
//groupWords will have an edge between each word in a bucket bc they differ by one letter

//for each '?' key in the map
for (auto i = buckets.begin(); i != buckets.end(); i++)
{
	vector<string> tempBucket = i->second;
	int tempBucket_size = tempBucket.size(); // size of vector associated with this key word
	
	// for each word in the bucket (ie, each entry in the associated vector of related words)
	for (auto j = 0; j < tempBucket_size; j++){
		
		// compare to other words in the bucket and add edge as needed
		for(auto it = (j+1); it < tempBucket_size; it++)
		{
			if (tempBucket[j] != tempBucket[it])
			{
				groupWords.addEdge(tempBucket[j], tempBucket[it]); /* adds edge between the two "vertices on the graph"...ie, the two words in the bucket specified above */
			} // end if

		} // end for loop that makes the edges

	} // end for loop of the words buckets

} // end loop for loop of the MAP of the buckets

	return groupWords;

} // end WordsGraph()

// return a vector of words
// ladder from word1 to word2
// any two adjacent words along the ladder differ in only one character
vector<string> WordLadder::getLadder(string word1, string word2) const
{
	int wordSize = word1.size(); //assumes words are same length
	vector<string> ladder;

	Graph<string> tempGraph = WordsGraph(wordSize);
	map<string,int> distance;
	map<string, string> go_through;
	int dis = tempGraph.BFS(word1, word2, distance, go_through);
       
   	//if there isn't a path, tell them there isnt one
   	if (dis == NOPATH)
    	{
    		// path does not exist
   		cout << "There is no ladder from [" << word1<< "] to [" << word2 << "]" << endl;
    	}

   	// add in error message 
   	else if (dis == INVALID_VERTEX)
	{    
   		cout << "Invalid source Vertex or/and destination Vertex!" << endl;
		cout << "There is no ladder from [" << word1<< "] to [" << word2 << "]" << endl;
	}

   	// same worda
    	else if (dis == 0)
    	{
   	 	cout  << "The two words must be different!" << endl;
    	}

    	else{ 
    	// make a stack, refer to lab12

    	// make stack and add word2
    	// stack is F I L O
    
	stack<string> wordStack;
    	wordStack.push(word2);

    	string current = word2;
    	while (go_through[current] != word1)
	{
   	 	wordStack.push(go_through[current]);
  	  	current = go_through[current];
   	 }

	//add word1
	wordStack.push(go_through[word1]);
   	ladder.push_back(wordStack.top());
    	wordStack.pop();    

	while (!wordStack.empty())
	{
	       ladder.push_back(wordStack.top());
	       wordStack.pop();
   	 }

    } // end else

return ladder;

}//end getLadder

#endif

