/*
 *
 * Section: CS216-003
 * Project: 3
 *
 * Purpose: Solve a Word Ladder puzzle from user input of two words of the same length, using a read-in dictionary text file as a word bank (building on material from Labs 11-13) & compiled using a makefile
 * Author: Monynich Kiem
 *
 * Due: Monday, December 9th, 2019
*/

#include <fstream>	    
#include <algorithm>    

//header files
#include "Graph.h"
#include "WordLadder.h"

using namespace std;

int main(int argc, char* argv[]){

    //check if the user inputted in a second argument aka the file needing to be read
    if (argc != 2)
    {
        cout << "Warning: need exactly one command line argument." << endl;
        cout << "Usage: " << argv[0] << " inputfile_name" << endl;
        return 1;
    }

	ifstream in_file;
	in_file.open(argv[1]);

    //check input file
    if (!in_file.good())
    {
        cout << "Warning: cannot open file named " << argv[1] << "!" << endl;
        return 2;
    }

//Read data from the input word dictionary file, assume "good data" from the input file
//read one line at a time then tokenize it and insert to WordLadder object
//*each word in the input file is on a new line

//words will be stored into a vector that will be used in the alt constructor for WordLadder object
vector<string> wordInput;

 while (!in_file.eof()){

//tokenize input and insert to string vector

     string new_word;
     getline(in_file, new_word);
     wordInput.push_back(new_word);

} //end of in_file.eof() loop

//close the file
in_file.close();

//create WordLadder object from the string vector
WordLadder wordLadder(wordInput);

//while loop menu repeatedly until user hits "Enter" key
string word1, word2;

    while (true)
    {
        cout << endl;
        cout << "Welcome to CS216 Word Ladder!" << endl;
        cout << "Please give me two English words, and I will convert the first into the second by modifying one letter at a time." << endl;
        cout << "Please type the FIRST word (or type Enter to quit): " << endl;
	    
	getline(cin, word1);
        
        if (word1 == ""){
            break;}
        
        cout << "Please type the SECOND word (or type Enter to quit): " << endl;
	    
	getline(cin, word2);
        
        if (word2 == ""){
            break;}
	
        //convert both word1 and word2 to all lower-case letters
        transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
        transform(word2.begin(), word2.end(), word2.begin(), ::tolower);

	//check if words are matching length, if not print error message
	if (word1.length() != word2.length()){
		cout << "The two words must be the same length!" << endl; 
	}

	//words are the smae legnth
	else
	{

        vector<string> ladder = wordLadder.getLadder(word1, word2);
        
	// Display the ladder distance from word1 to word2
        // Display the shortest path on the word ladder from word1 to word2
        // the ladder distance is defined as the number of vertices(word) 
	// on the shortest path from one vertex to another
        // the ladder distance of the same vertex to itself is 1-word

	// display the ladder if it exists
        if (ladder.size() > 1)
        {
            cout << "The ladder from " << word1 << " to " << word2 << " is " << ladder.size() << "-words long." << endl;
            cout << "A ladder from [" << word1 << "] to [" << word2 << "]:" << endl;
            cout << ladder[0];
            
	    for (size_t i=1; i < ladder.size(); i++)
            {
                cout << " ---> " << ladder[i];
            }
            
	    cout << endl;
        }

	}//end else stmt

} //end while-true loop
	
	cout << "Have a beautiful day. See you next time..." << endl << endl;

	return 0;

}//end main()

