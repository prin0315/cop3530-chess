#pragma once
#include "Game.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class Graph
{
private:
	map<string, vector<pair<string, Game>>> adjList;
public:
	Graph();
	void insertGame(Game game);
	void printNames(); //mainly for debug
};

Graph::Graph() {}

void Graph::insertGame(Game game)
{
	if (game.winner == game.whiteID)
	{
		pair<string, Game> newGame(game.blackID, game);
		adjList[game.whiteID].push_back(newGame);
	}
	else
	{
		pair<string, Game> newGame(game.whiteID, game);
		adjList[game.blackID].push_back(newGame);
	}
}

void Graph::printNames()
{
	for (auto iter = adjList.begin(); iter != adjList.end(); iter++)
	{
		cout << iter->first << endl;
	}
}