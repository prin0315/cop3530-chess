#pragma once
#include "Game.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <string>
#include <iostream>

using namespace std;

class Graph
{
private:
	unordered_map<string, vector<pair<string, Game>>> adjList;
	void visit(string name, int& elo, double& wl);
public:
	Graph();
	void insertGame(Game game);
	void matchmake(string name);
	// Functions below are mainly for debug, not necessarily actual proper graph algorithms or even well implemented
	void printNames(int n = INT_MAX); 
	void printWins(string name);
};

Graph::Graph() {}

void Graph::insertGame(Game game)
{
	pair<string, Game> newGame1(game.blackID, game);
	adjList[game.whiteID].push_back(newGame1);
	pair<string, Game> newGame2(game.whiteID, game);
	adjList[game.blackID].push_back(newGame2);
}

//void Graph::matchmake(string name)
//{
//	vector<pair<string, Game>> playerGames = adjList[name];
//	queue<string> q;
//	q.push(name);
//	for (pair<string, Game> p : playerGames)
//	{
//		//for each opponent the given player has played, check all of their opponents
//		int wl = 0;
//		int elo = -1;
//		int maxTime = 0;
//		for (pair<string, Game> op : adjList[p.first])
//		{
//			bool isWhite = p.first == op.second.whiteID;
//			bool won = isWhite == stoi(op.second.whiteRatingDiff) > 0;
//			wl = won ? wl + 1 : wl - 1;
//			unsigned int time = op.second.getDateTime();
//			if (time > maxTime)
//			{
//				time == maxTime;
//				elo = isWhite ? stoi(op.second.whiteElo) : stoi(op.second.blackElo);
//			}
//		}
//		if (elo - )
//	}
//}

void Graph::matchmake(string name)
{
	unordered_set<string> marked;
	queue<string> q;
	q.push(name);
	marked.insert(name);
	int counter = 0;
	while (!q.empty())
	{
		string current = q.front();
		q.pop();

		int elo = -1;
		int wins = 0;
		int losses = 0;
		int maxTime = 0;
		for (pair<string, Game> p : adjList[current])
		{
			bool isWhite = current == p.second.whiteID;
			bool won = isWhite == stoi(p.second.whiteRatingDiff) > 0;
			if (won)
				wins++;
			else
				losses++;
			unsigned int time = p.second.getDateTime();
			if (time > maxTime)
			{
				time = maxTime;
				elo = isWhite ? stoi(p.second.whiteElo) : stoi(p.second.blackElo);
			}
			if (marked.find(p.first) == marked.end())
			{
				q.push(p.first);
				marked.insert(p.first);
			}
		}
		double wl = wins / (wins + losses);
		cout << "name: " << current << " wl: " << wl << " elo: " << elo << endl;

		counter++;
		if (counter > 20)
			break;
	}
}

//void Graph::visit(string name, int& elo, double& wl)
//{
//	int maxTime = 0;
//	for (pair<string, Game> p : adjList[name])
//	{
//		bool isWhite = name == p.second.whiteID;
//		bool won = isWhite == stoi(p.second.whiteRatingDiff) > 0;
//		wl = won ? wl + 1 : wl - 1;
//		unsigned int time = p.second.getDateTime();
//		if (time > maxTime)
//		{
//			time == maxTime;
//			elo = isWhite ? stoi(op.second.whiteElo) : stoi(op.second.blackElo);
//		}
//	}
//}

void Graph::printNames(int n)
{
	int count = 0;
	for (auto iter = adjList.begin(); iter != adjList.end(); iter++)
	{
		cout << iter->first << endl;

		count++;
		if (count >= n)
			break;
	}
}

void Graph::printWins(string name)
{
	for (pair<string, Game> p : adjList[name])
	{
		string ratingDiff = p.second.winner == p.second.whiteID ? p.second.whiteRatingDiff : p.second.blackRatingDiff;
		cout << "Opponent: " << p.first << " Rating Diff: " << ratingDiff << " Time: " << p.second.getDateTime() << endl;
	}
}