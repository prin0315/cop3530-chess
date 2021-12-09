#pragma once
#include "Game.h"
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <string>
#include <iostream>
#include <set>
#include "DisjointSet.h"

using namespace std;

class Graph
{
private:
	unordered_map<string, vector<pair<string, Game>>> adjList;
	
public:
	Graph();
	void insertGame(Game game);
	void matchmake(string name);
	void printNames(int n = INT_MAX);
	void printWins(string name);
	vector<string> getAdjacent(string vertex);
	void primAlgorithm(string name);
	int getElo(string vertex);
};

Graph::Graph() {}

void Graph::insertGame(Game game)
{
	pair<string, Game> newGame1(game.blackID, game);
	adjList[game.whiteID].push_back(newGame1);
	pair<string, Game> newGame2(game.whiteID, game);
	adjList[game.blackID].push_back(newGame2);
}

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
				maxTime = time;
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

		counter++;
		if (counter > 20)
			break;
	}
}

vector<string> Graph::getAdjacent(string vertex)
{
	vector<string> v;
	for (int i = 0; i < adjList[vertex].size(); i++)
	{
		v.push_back(adjList[vertex].at(i).first);
	}
	return v;
}

int Graph::getElo(string vertex)
{
	vector<pair<string, Game>> opponents = adjList[vertex];
	unsigned int maxTime = 0;
	int elo = -1;
	for (pair<string, Game> p : opponents)
	{
		unsigned int time = p.second.getDateTime();
		if (time > maxTime)
		{
			maxTime = time;
			elo = vertex == p.second.whiteID ? stoi(p.second.whiteElo) : stoi(p.second.blackElo);
		}
	}
	return elo;
}


//void Graph::primAlgorithm(string name)
//{
//	set<string> T;
//	set<string> adjacents;
//	T.insert(name);
//	vector<pair<string, Game>> adjacent = adjList[name];
//
//	string minName = "";
//	int minElo = INT_MAX;
//	for (int i = 0; i < adjacent.size(); i++)
//	{
//		adjacents.insert(adjacent[i].first);
//
//	}
//
//	while (!adjacents.empty())
//	{
//		for (int i = 1; i < adjacent.size() - 1; i++)
//		{
//			if (getElo(adjacent.at(i).first) < minElo && T.find(adjacent.at(i).first) == T.end())
//			{
//				minElo = getElo(adjacent.at(i).first);
//				minName = adjacent.at(i).first;
//			}
//		}
//
//		T.insert(minName);
//		adjacents.erase(minName);
//		minElo = INT_MAX;
//	}
//
//	for (auto itr = T.begin(); itr != T.end(); ++itr)
//	{
//		cout << *itr << " ";
//	}
//
//}

void Graph::primAlgorithm(string name)
{
	set<string> T;
	unordered_map<string, int> keys;
	unordered_map<string, string> MST;
	for (auto i = adjList.begin(); i != adjList.end(); i++)
		keys[i->first] = INT_MAX;
	keys[name] = 0;
	int safety = 0;

	while (T.size() != adjList.size())
	{
		int min = INT_MAX;
		string key;
		for (auto i = keys.begin(); i != keys.end(); i++)
		{
			if (T.find(i->first) == T.end() && i->second < min)
			{
				min = i->second;
				key = i->first;
			}
		}
		T.insert(key);
		for (pair<string, Game> p : adjList[key])
		{
			int weight = p.second.whiteID == p.first ? stoi(p.second.whiteRatingDiff) : stoi(p.second.blackRatingDiff);
			keys[p.first] = std::min(keys[p.first], weight);
			MST[p.first] = key;
		}
		safety++;
		if (safety % 10 == 0)
			cout << key;
		if (safety > INT_MAX)
			throw std::invalid_argument("Infinite while loop");
	}

	cout << "DONE" << endl;
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