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
	// Functions below are mainly for debug, not necessarily actual proper graph algorithms
	void printNames(); 
	void printWins(string name);
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

void Graph::printWins(string name)
{
	for (pair<string, Game> p : adjList[name])
	{
		string ratingDiff = p.second.winner == p.second.whiteID ? p.second.whiteRatingDiff : p.second.blackRatingDiff;
		cout << "Opponent: " << p.first << "Rating Diff: " << ratingDiff << endl;
	}
}