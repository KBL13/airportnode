#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#include <utility>
#include <sstream>
#include <fstream>
#include "Queue.h"

using namespace std;
using namespace cop4530;

template <typename T>
bool breadth(int start, int goal, const vector<T> & z, const vector<string> & a); //Function so that member data inside can be deallocated once out of scope so function can be used again

struct airport //Container for the airports
{
    int airportID; //Assigns the airport a number for easy tracking
    vector <int> connections;
    vector <int> price;
};

int main()
{
    ifstream inputFile;
    inputFile.open("proj3.input");
    if (!inputFile)
    {
        cout << "File did not open\n";
        exit(1);
    }
    
    int inputSize; //Stores the first number in the file
    int tempPrice = 0; //Temp variable to store prices into arrays
    int sourceNum;
    int destinationNum;
    
    bool sourceVar; //Error checking variables
    bool destinationVar;
    
    string userInput; //Takes in user input to continue or not
    string temp; //temporray string to be used over and over. Ex. taking in names and storing into vectors
    string sourceCity;
    string destinationCity;
    
    vector<string> airports; //vector for the names of the airport. Easier to call versus accessing them through the struct containers.
    vector<airport> network; //vector of structs
    inputFile >> inputSize;
    
    getline(inputFile,temp);//Gets rid of newline following number.
    

    for (int i = 0; i < inputSize; i++)
    {
        network.push_back(airport());
        network[i].airportID = i;
        getline(inputFile, temp);
        airports.push_back(temp);
    }

    for (int i = 0; i < inputSize; i++) //Taking in matrix numbers
    {
        for (int k = 0; k < inputSize; k++)
        {
                inputFile >> tempPrice;
                if (tempPrice > 0)
                {
                    network[i].price.push_back(tempPrice);
                    network[i].connections.push_back(k); //Takes in the price and indexs which airport it goes to
                }

        }
    }
    
    cout << inputSize << " cities:" << endl; //Prints information of each flight the airport offers
    for (int i = 0; i < inputSize; i++)
    {
        cout << "\t" << airports[i] << endl;
    }
    cout << "\ndirect flights between cities\n-----------------------------\n";
    for (int i = 0; i < inputSize; i++)
    {
        cout << airports[i] << ":" << endl;
        for (int k = 0; k < network[i].connections.size(); k++)
        {
            cout << "\t" << airports[network[i].connections[k]] << ", $" << network[i].price[k] << endl;
        }
    }
    
    cout << "-----------------------------\n\n";
    
    while (userInput == "Y" || "y") //While loop for asking source city and destination printing shortest path and price
    {
        
        sourceVar = false; //set both var to false for easy error checking of whether user input is valid
        destinationVar = false;

        cout << "Source city : ";
        getline(cin, sourceCity);
        
        for (int i = 0; i < inputSize; i++)
        {
            if (sourceCity == airports[i])
            {
                sourceNum = i;
                sourceVar = true; //True only if user inputs matches one of the listed airports from input file
            }
        }
        
        cout << "Destination city : ";
        getline(cin, destinationCity);
        
        for (int i = 0; i < inputSize; i++)
        {
            if (destinationCity == airports[i])
            {
                destinationNum = i;
                destinationVar = true; //True only if user inputs matches one of the listed airports from input file
            }
        }
        
        cout << "finding min_hop route...." << endl;
        
        if (sourceVar && destinationVar)
        {
            //breadth search function call
			breadth(sourceNum,destinationNum, network, airports);

        }
        else
        {
            if (sourceVar == false)
            {
                cout << "\tpath not found, source city, " << sourceCity << ", not on map\n"; //Error printing
            }
            else
            {
                cout << "\tpath not found, destination city, " << destinationCity << ", not on map\n";
            }
        }
                
        cout << "\nSearch another route? (Y/N)";
        
        getline(cin, userInput); //Determines if user input is valid 
        if (userInput == "n")
        {
            break;
        }
        else if (userInput == "N")
        {
            break;
        }
		else if (userInput == "Y")
		{

		}
		else if (userInput == "y")
		{

		}
		else
		{
			break;
		}
    }
    
    inputFile.close();
    
    return 0;
}

template <typename T> //airport was declared inside main and since global variables not allowed, template did the job
bool breadth(int start, int goal, const vector<T> & z, const vector<string> & a)
{
	vector <int> shortPath; //Stores the airports ID in order from goal to start
	bool arr [a.size()]; //array of boolean expressions used to determine shortest flight path
	int prev[a.size()]; //array of ints to determine the pattern
	int startNum = start;
	int nextNum;
	int total = 0; //variable that will hold total price

	for (int i = 0; i < a.size(); i++)
	{
		arr[i] = false; //sets array of boolean expressions to false.
	}

	Queue <int> search; //implementing queue for breadth search

	if(start == goal) //If they are traveling to the same city, source == destination, then it will output default statement
	{
		cout << a[start] << ", $0";
	}
	else //Otherwise if source!=destination, the breadth function can start
	{
		search.push(start); //Takes in starting city
		arr[startNum] = true; //Sets the boolean array of airportID to true
		for (int i = 0; i < a.size()-1; i++)
		{
			if (i == 0) //base case for taking in the first neighbors of the starting city
			{
				for(int k = 0; k < z[startNum].connections.size();k++)
				{
						search.push(z[startNum].connections[k]); //adds ID to queue
						arr[z[startNum].connections[k]] = true; //Sets index of ID to true
						prev[z[startNum].connections[k]] = startNum; //Find where neighbors are in array but as indexes and sets the start number to those indexs.
				}
				search.pop(); //Dequeues
				startNum = search.front(); //sets new starting number to compare
			}
			else
			{
				for(int k = 0; k < z[startNum].connections.size();k++)
				{
					if(arr[z[startNum].connections[k]] == false) //would have not worked if i=0 so separated and created a base case instead
					{
						search.push(z[startNum].connections[k]);
						arr[z[startNum].connections[k]] = true;
						prev[z[startNum].connections[k]] = startNum;
					}
				}
				search.pop(); //Dequeues
				startNum = search.front();//sets new starting number to compare
			}
		}
		//prev array now contains the key to trace back
		nextNum = goal;
		while(nextNum != start)
		{
			shortPath.push_back(nextNum); //Adds the path/flight to vector
			nextNum = prev[nextNum]; //Adds the next one from the prev array
		}

		cout << "\t" << a[start];

		for (int i = shortPath.size()-1; i >= 0; i--) //Used to print out flight path
		{
			if (i == shortPath.size()-1) //Also implemented a base case for the price of the first path where it was convient to access shortPath[i] from the back since short path's order is goal->start
			{
				for (int j = 0; j < z[start].connections.size(); j++)
				{
					if (z[start].connections[j] == shortPath[i])
					{
						total = z[start].price[j];
					}
				}
			}
			cout << " -> " << a[shortPath[i]]; //Prints the airports
		}

		for (int i = 0; i < shortPath.size(); i++) //Nested for loop for checking and accessing the correct price from connections(neighbors) vectors. Basically like a 2d array
		{
			for(int k = 0; k < z[shortPath[i]].price.size(); k++)
			{
				if (z[shortPath[i]].connections[k] == shortPath[i+1] && shortPath.size() > 1) //Only runs if shortPath has more than 2 stops, reason being the base case handles the 1 stop
				{
					total += (z[shortPath[i]].price[k]); //Adds to the total sum
				}
			}
		}
		cout << ", $" << total;
	}
	return true;

}