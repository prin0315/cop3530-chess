#include <iostream>
#include "Reader.h"
#include "Game.h"
#include "Graph.h"

using namespace std;

int main()
{
	//Number of games to be read from CSV
	cout << "Input N = ";
	int n;
	cin >> n;

	//Creates graph and loads in data
	Reader reader("chess_games.csv");
	Graph graph;
	for (int i = 0; i < n; i++)
	{
		Game g = reader.read();
		graph.insertGame(g);
	}

	cout << "ENTER NAME" << endl;
	string name;
	cin >> name;
	graph.printWins(name);
	graph.matchmake(name);
	graph.matchmakeDfs(name);

	return 0;
}