#include <iostream>
#include <chrono>
#include "Reader.h"
#include "Game.h"
#include "Graph.h"

using namespace std;

int main()
{
	//Number of games to be read from CSV
	cout << "Please put the number of data points to use: ";
	int n;
	cin >> n;

	cout << "Reading " << n << " rows of data..." << endl;
	//Creates graph and loads in data
	Reader reader("chess_games.csv");
	Graph graph;
	for (int i = 0; i < n; i++)
	{
		Game g = reader.read();
		graph.insertGame(g);
	}

	//debug stuff, prints first 500 names in graph and asks for a user whose opponents can be listed
	/*if (n < 500)
		graph.printNames();
	else
	{
		graph.printNames(500);
		cout << "(only first 500 printed)" << endl;
	}
	*/

	cout << endl;

	cout << "Features:" << endl;
	cout << "1) Display all names in the graph." << endl;
	cout << "2) Display all adjacent nodes of a specific player." << endl;
	cout << "3) Print the stats of every game the person has played. " << endl;
	cout << "4) Find the best match for a specific player." << endl;
	cout << "5) Compare Dijkstra and DFS Shortest Path Algorithms." << endl;
	cout << endl;
	cout << "Enter the corresponding number for each feature: ";
	
	int option = -1;
	cin >> option;

	cout << endl;

	string name;
	switch (option)
	{
		case 1:

			cout << "Enter how many names to print. Enter 0 to show all names in the graph." << endl;
			int number;
			cin >> number;
			cout << endl;
			if (number == 0)
			{
				graph.printNames(n);
			}
			else
			{
				graph.printNames(number);
			}
			break;

		case 2:

			cout << "Please enter a name to use: ";
			cin >> name;

			cout << endl;
			graph.getAdjacent(name);
			break;

		case 3:
			cout << "Please enter a name to use: ";
			cin >> name;

			cout << endl;
			graph.printWins(name);
			break;

		case 4:
			cout << "Please enter a name to use: ";
			cin >> name;

			cout << endl;
			graph.matchmake(name);
			break;

		case 5:

			cout << "Please enter two names to use:" << endl;
			string name1;
			cin >> name1;
			string name2;
			cin >> name2;

			auto start = std::chrono::high_resolution_clock::now();
			cout << "The Djikstra Shortest Path algorithm found there to be " << graph.Djikstra(name1, name2) << " nodes between " << name1 << " and " << name2 << "." << endl;
			auto stop = std::chrono::high_resolution_clock::now();
			auto difference = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
			cout << "It took Djikstra's algorithm " << difference.count() << " nanoseconds." << endl;

			cout << endl;
			start = std::chrono::high_resolution_clock::now();
			cout << "The DFS Shortest Path algorithm found there to be " << graph.DFS(name1, name2) << " nodes between " << name1 << " and " << name2 << "." << endl;
			stop = std::chrono::high_resolution_clock::now();
			difference = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
			cout << "It took the DFS Shortest Path algorithm " << difference.count() << " nanoseconds." << endl;

			
			break;
	}

	return 0;
}