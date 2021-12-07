#pragma once
#include "Game.h"
#include <vector>
#include <map>
#include <string>

using namespace std;

class Graph
{
	Graph();
	map<string, vector<pair<string, Game>>> adjList;
	void insertGame(Game game);
};

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