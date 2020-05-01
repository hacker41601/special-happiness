/*
 * Course: CS216-03x
 * Project: PA2
 * Purpose: it reads data from an input file which passes as command line argument
 *          then stores in an object of IMDB class (to represent imdb database in two map objects)
 *          The input file format:
 *          Movie Title; actor1, actor2, ..., actorN
 *          it then allowes user to search for all actors in either one of two movies
 *          and output the list of actors depedning on what options the user selects
 * 
 * Author: Monynich Kiem
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <map>
#include <sstream>
#include "imdb.h"

using namespace std;

void analyzeMovies(const IMDB& imdb);
void analyzeCoActors(const IMDB& imdb);

int main(int argc, char* argv[])
{
    // Check whether the number of command line arguments is exactly one 
    if (argc != 2)
    {
        cout << "Warning: need exactly one command line argument." << endl;
        cout << "Usage: " << argv[0] << " inputfile_name" << endl;
        return 1;
    }

    ifstream in_file;
    in_file.open(argv[1]);

    // Check whether the input file can be open successfully or not
    if (!in_file.good())
    {
        cout << "Warning: cannot open file named " << argv[1] << "!" << endl;
        return 2;
    
    }
    //Change the way you read the file using movie_actors.txt instead of actor_movies.txt
    // Read data from the input file, assume "good data" from the input file
    // each line of the input file: MovieTitle; actor1, actor2, ..., actorN
    // read one line at a time then tokenize it:
    // create a pair <movieTitle, the set of actorNames which the actor was in>
    //        and insert to IMDB object
    IMDB cs216_imdb;

   while (!in_file.eof())
    {
        string line;
        getline(in_file, line);
        string actorName, movieTitle;
        // check if the text line is not empty then tokenize it
        if (line.length() != 0)
        {
            istringstream iss(line);
            getline(iss, movieTitle,';');

            // Extract extra white space
            iss>>ws;

            // Create a new set of movies associated with actorName
            set<string> actors;

            while (getline(iss, actorName, ','))
            {
                actors.insert(actorName);
                // extract white space 
                iss>>ws;
            }
            // insert the pair to IMDB object: cs216_imdb
            cs216_imdb.insert_a_movie(movieTitle, actors);
        }
    }
    // close the input file
    in_file.close();

    int option;
    while (true)
    {
        cout << "This application stores information about Actors and their Movies, please choose your option (Enter Q or q to quit):" << endl;
        cout << "1. Actors in Movies" << endl;
        cout << "2. Actors and co-actors" << endl;
        cin >> option;
        cin.ignore(256, '\n');

        if (cin.fail())
        {
            string input_to_check;
            cin.clear();
	    getline(cin, input_to_check);//this is to prevent a repititive error message 
            if (input_to_check == "Q" || input_to_check == "q")
                break;
            else
            {
                cout << "Invalid option!" << endl;
                continue;
            }
        }

        switch (option)
        {
            case 1: analyzeMovies(cs216_imdb);
		    //modify this function so that there are 3 subfunctions A,O, and C 
                    break;
		    //this is from Lab8
		    
            case 2: analyzeCoActors(cs216_imdb);
                    break;
		    //this is from Lab9

            default:
                    cout << "Invalid option!" << endl;
        }
    }

    cout << "Thank you for using my program, bye..." << endl;
    return 0;
}//end of main


// this function asks the user to input two movie titles
// then finds the matched two movies from the map
// and displays all the actors in either of the two movies
// if no matched movie then display "Invalid movie title" and do nothing
// note that using const call by reference is for efficiency purpose:
//           no copy of IMDB object is made and the argument has been protected
void analyzeMovies(const IMDB& imdb)
{
    // Ask the user to input two movie titles to search for
    string movie1, movie2;
    cout << "Please input the first movie title: ";
    getline(cin,movie1);
    cout << "Please input the second movie title: ";
    getline(cin,movie2);
    
    // Check if both movie1 and movies can be matched with movies in the map
    // If either one is not, quit the program
    // Otherwise display all the actors in either of two movies
    //                   which are actually the union of two sets
    string matchedMovie1, matchedMovie2;
    matchedMovie1 = imdb.matchExistingMovie(movie1);
    matchedMovie2 = imdb.matchExistingMovie(movie2);
  
    if ((matchedMovie1.length() > 0) && (matchedMovie2.length() > 0))
    {
        cout << "Your input matches the following two movies: " <<endl;
        cout << matchedMovie1 << endl;
        cout << matchedMovie2 << endl;
        cout << "Both movies are in the database, searching actors..." << endl;

        set<string> all;   // to store the union of actors_in_movie1 and actors_in_movie2
        all = imdb.find_actors_in_a_movie(matchedMovie1);
        set<string> actors_in_movie2 = imdb.find_actors_in_a_movie(matchedMovie2);
	set<string> actors_in_movie1 = imdb.find_actors_in_a_movie(matchedMovie1);
        for (auto i = actors_in_movie2.begin(); i != actors_in_movie2.end(); i++)
            all.insert(*i);

    	cout << "Please input your menu option (enter Q or q to quit):" << endl;
	cout << "A - Print all actors in either of the two movies." << endl;
	cout << "C - Print all the common actors in both of the movies." << endl;
	cout << "O - Print all the actors who are in one movie but not both." << endl;

	string user_option;
	cin >> user_option;
	while (user_option != "Q" &&  user_option != "q") 
	{
	//This is option A
    	// Display all the 
	// actors in either one movie
	if (user_option == "A" || user_option == "a") {
       		cout << "All the actors in either of the two movies:" << endl;
        	for (auto i = all.begin(); i != all.end(); i++)
            	cout << *i << endl;
		//this for loop is a union of two sets therefore displaying all the actors
		
		cout << "Please input your menu option (enter Q or q to quit):" << endl;
		cout << "A - Print all actors in either of the two movies." << endl;
		cout << "C - Print all the common actors in both of the movies." << endl;
		cout << "O - Print all the actors who are in one movie but not both." << endl;
	
	}
	else if (user_option == "C" || user_option == "c") {
		//this prints out the common actors
		//intersection between actors in movie 1 and actors in movie 2
		//sort actors_in_movie1.txt actors_in_movie2.txt | uniq -d
		cout << "All the common actors in both movies:" << endl;
		set<string> common;
		for (auto i = actors_in_movie2.begin(); i != actors_in_movie2.end(); i++)
		{
			if (actors_in_movie1.find(*i) != actors_in_movie1.end())
			{
				common.insert(*i);
			}
		}//this looks for actors that are found in movie1 from movie2 and display them
		for (auto j = common.begin(); j != common.end(); j++)
		{
			cout << *j << endl;
		}
		
 		cout << "Please input your menu option (enter Q or q to quit):" << endl;
                cout << "A - Print all actors in either of the two movies." << endl;
                cout << "C - Print all the common actors in both of the movies." << endl;
                cout << "O - Print all the actors who are in one movie but not both." << endl;
	
	}
	else if (user_option == "O" || user_option == "o") {
		//this prints out the actors in one movie but not the other
		//union minus intersection between actors in movie 1 and actors in movie 2
		//sort actors_in_movie1.txt actors_in_movie2.txt | uniq -u
		cout << "Actor(s) in only one of the movies:" << endl;
		set<string> unique;
		for (auto i = actors_in_movie2.begin(); i != actors_in_movie2.end(); i++)
		{
			if (actors_in_movie1.find(*i) == actors_in_movie1.end())
			{
				unique.insert(*i);
			}
		}
		//add in for loop for unique2
		//similar to option c, this finds actors in movie1 that aren't the same in movie 2 and displays them
		for (auto i = actors_in_movie1.begin(); i != actors_in_movie1.end(); i++)
		{
			if (actors_in_movie2.find(*i) == actors_in_movie2.end())
			{
				unique.insert(*i);
			}
		}
		for (auto j = unique.begin(); j != unique.end(); j++)
		{
			cout << *j << endl;
		}
		//add in for loop for output
		
		cout << "Please input your menu option (enter Q or q to quit):" << endl;
                cout << "A - Print all actors in either of the two movies." << endl;
                cout << "C - Print all the common actors in both of the movies." << endl;
                cout << "O - Print all the actors who are in one movie but not both." << endl;
	
	}
	else {
		cout << "Invalid option" << endl;
		cout << "Please input your menu option (enter Q or q to quit):" << endl;
                cout << "A - Print all actors in either of the two movies." << endl;
                cout << "C - Print all the common actors in both of the movies." << endl;
                cout << "O - Print all the actors who are in one movie but not both." << endl;
	
	}
	
	cin >> user_option;
	//this is where you insert the other 3 submenu options
	//Option Cc is where you print all the common actors
	//Option Oo is where you print out all the actors in one but not the other
	//Option Qq is quitting back to the main menu but not the program
	//If none of these option then display an error message and continue displaying the submenu
	}//while loop ends
		
	
    }
    else
    {
        cout << "Invalid movie title." << endl;
        return;
    }

}//end of analyzing movies

void analyzeCoActors(const IMDB& imdb)
{
	//copy from lab9
	string actor_name;
       	cout << "Finding the co-actors of the actor by typing his/her name: ";
	getline(cin, actor_name);

	//the next two lines are what allows the user input to go through the function and let it not be case sensitive
	string matchedActor;
	matchedActor = imdb.matchExistingActor(actor_name);
	if (!imdb.isExistingActor(matchedActor))
       	{
		cout << "The actor name you entered is not in the database." << endl;
		return;
	}

    	set<string> movies_of_actor;
    	movies_of_actor = imdb.find_movies_for_an_actor(matchedActor);
    	set<string> actors_in_a_movie;
    	for (auto i = movies_of_actor.begin(); i != movies_of_actor.end(); i++)
    	{	
        	cout << "The co-actors of " << matchedActor << " in the movie \"" << *i << "\" are: " << endl;
       
	       	// Display all the co-actors in one movie
        	actors_in_a_movie = imdb.find_actors_in_a_movie(*i);//last edit here
        	for (auto j = actors_in_a_movie.begin(); j != actors_in_a_movie.end(); j++)
        	{
                	if (*j != matchedActor)
                 	{
                         cout << *j << endl;

                        //if the actor name is in the for loop, just cout everything before and after it but not all of it
			}//this will only cout names that arent thr same as the input
		}
		
		cout << "***********************************" << endl;
    }
	//copy from lab9 
	
}//end of analyzing co-actors
