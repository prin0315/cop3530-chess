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
	// Functions below are mainly for debug, not necessarily actual proper graph algorithms or even well implemented
	void printNames(int n = INT_MAX);
	void printWins(string name);
	vector<string> getAdjacent(string vertex);
	void primAlgorithm(string name, Graph graph);
	int getElo(string vertex);
	int sumOfMST();
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
	pair<string, Game> p = adjList[vertex].at(0);
	return stoi(p.second.blackRatingDiff);
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


void Graph::primAlgorithm(string name, Graph graph)
{
	set<string> T;
	set<string> adjacents;
	string id = name;
	T.insert(id);
	vector<string> adjacent = graph.getAdjacent(id);

	string minName = "";
	int minElo = INT_MAX;
	for (int i = 1; i < adjacent.size() - 1; i++)
	{
		adjacents.insert(adjacent.at(i));

	}

	while (!adjacents.empty())
	{
		for (int i = 1; i < adjacent.size() - 1; i++)
		{
			if (graph.getElo(adjacent.at(i)) < minElo && T.find(adjacent.at(i)) == T.end())
			{
				minElo = graph.getElo(adjacent.at(i));
				minName = adjacent.at(i);
			}
		}

		T.insert(minName);
		adjacents.erase(minName);
		minElo = INT_MAX;
	}

	for (auto itr = T.begin(); itr != T.end(); ++itr)
	{
		cout << *itr << " ";
	}

}

int Graph::sumOfMST()
{
	DisjointSet ds;
	ds.makeSet(vertices);
	int res = 0;

	for (const auto& entry : graph) {
		int c = entry.first; // weight 
		pair<int, int> p = entry.second; // two vertices 
		int u = p.first;
		int v = p.second;
		int x = ds.findRoot(u);
		int y = ds.findRoot(v);
		if (x != y) {
			res += c;
			ds.unionSet(x, y);
		}
	}

	return res;
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