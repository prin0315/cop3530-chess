#include <iostream>
#include "Reader.h"
#include "Game.h"
#include "Graph.h"

using namespace std;

int main()
{
	cout << "Input N = ";
	int n;
	cin >> n;

	Reader reader("chess_games.csv");
	Graph graph;
	for (int i = 0; i < n; i++)
	{
		Game g = reader.read();
		graph.insertGame(g);
	}
	graph.printNames();

	return 0;
}