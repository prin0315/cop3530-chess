#pragma once
#include "Game.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <string>
#include <iostream>

using namespace std;

class Graph
{
private:
	unordered_map<string, vector<pair<string, Game>>> adjList;
public:
	Graph();
	void insertGame(Game game);
	void matchmake(string name);
	void matchmakeDfs(string name);
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


void Graph::matchmakeDfs(string name)
{
	unordered_set<string> marked;
	stack<string> s;
	s.push(name);
	marked.insert(name);
	for (int i = 0; i < 20 && !s.empty(); i++)
	{
		string current = s.top();
		s.pop();

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
				s.push(p.first);
				marked.insert(p.first);
			}
		}
		double wl = (double)wins / ((double)wins + losses);
		cout << "name: " << current << " wl: " << wl << " elo: " << elo << endl;
	}
}


void Graph::matchmake(string name)
{
	unordered_set<string> marked;
	queue<string> q;
	q.push(name);
	marked.insert(name);
	for (int i = 0; i < 20 && !q.empty(); i++)
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
		double wl = (double)wins / ((double)wins + losses);
		cout << "name: " << current << " wl: " << wl << " elo: " << elo << endl;
	}
}


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