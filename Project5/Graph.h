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
#include <stack>

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
	void getAdjacent(string vertex);
	int getElo(string vertex);
	int DFS(string from, string to);
	int Djikstra(string source, string dest);
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
	vector<string> goodMatches;
	unordered_set<string> marked;
	queue<string> q;
	q.push(name);
	marked.insert(name);
	int counter = 0;
	int requestedElo = 0;
	if (adjList[name].at(0).second.blackID == name)
	{
		requestedElo = stoi(adjList[name].at(0).second.blackElo);
	}
	else if (adjList[name].at(0).second.whiteID == name)
	{
		requestedElo = stoi(adjList[name].at(0).second.whiteElo);
	}

	int minElo = INT_MAX;
	int maxMatches = 0;
	int closestElo = 0;
	int requestedMatches = 0;
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
			if (current == name)
			{
				requestedMatches++;
			}
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

			if (abs(elo - requestedElo) < minElo && (current != name))
			{
				if (abs((wins + losses) - requestedMatches) > maxMatches)
				{
					goodMatches.clear();
					minElo = abs(elo - requestedElo);
					maxMatches = abs((wins + losses) - requestedMatches);
					goodMatches.push_back(current);
					closestElo = elo;
				}
			}
		}


		double wl = (double)wins / ((double)wins + losses);

		counter++;
		if (counter > 20)
			break;
	}

	if (goodMatches.empty())
	{
		cout << "Could not find a good match for: " << name << "." << endl;
	}
	else
	{
		cout << "We were given " << name << " with a current elo of " << requestedElo << " and " << requestedMatches << " matches played." << endl;
		cout << "The best match is " << goodMatches.at(0) << " with an elo of " << closestElo << " and " << maxMatches << " matches played." << endl;
	}
}

int Graph::DFS(string from, string to)
{

		std::set<string> visited;
		std::stack<string> s;
		visited.insert(from);
		s.push(from);
		while (!s.empty())
		{
			string u = s.top();
			s.pop();
			vector<pair<string, Game>> neighbors = adjList[u];
			for (pair<string, Game> v : neighbors)
			{
				if (v.first == to)
				{
					break;
				}
				else
				{
					if (visited.count(v.first) == 0)
					{
						visited.insert(v.first);
						s.push(v.first);
					}
				}
			}
		}

		return visited.size();
}

int Graph::Djikstra(string source, string dest)
{
	set<string> S;
	set<string> VS;
	unordered_map<string, int> d;
	S.insert(source);
	d[source] = 0;
	for (auto i = adjList.begin(); i != adjList.end(); i++)
	{
		if (i->first != source)
		{
			VS.insert(i->first);
			bool connected = false;
			for (pair<string, Game> p : adjList[i->first])
			{
				if (p.first == source)
				{
					if (i->first == dest)
						return 1;
					connected = true;
					d[i->first] = 1;
					break;
				}
			}
			if (!connected)
				d[i->first] = INT_MAX;
		}
	}

	while (!VS.empty())
	{
		int min = INT_MAX;
		string smallest = "";
		for (auto i = VS.begin(); i != VS.end(); i++)
		{
			if (d[*i] < min)
			{
				min = d[*i];
				smallest = *i;
			}
		}
		VS.erase(smallest);
		S.insert(smallest);
		for (pair<string, Game> p : adjList[smallest])
		{
			if (VS.find(p.first) != VS.end())
			{
				if (d[smallest] + 1 < d[p.first])
					d[p.first] = d[smallest] + 1;
			}
		}
		if (smallest == dest)
			return d[dest];
	}
	return d[dest];
}

void Graph::getAdjacent(string vertex)
{
	cout << "Adjacent nodes:" << endl;
	for (int i = 0; i < adjList[vertex].size(); i++)
	{
		cout << i << ": " << adjList[vertex].at(i).first << endl;
	}

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



void Graph::printNames(int n)
{
	int count = 0;
	for (auto iter = adjList.begin(); iter != adjList.end(); iter++)
	{
		cout << count << ": " << iter->first << endl;

		count++;
		if (count >= n)
			break;
	}
}

void Graph::printWins(string name)
{
	int i = 1;
	for (pair<string, Game> p : adjList[name])
	{
		cout << "Game " << i << ":" << endl;
		string ratingDiff = p.second.winner == p.second.whiteID ? p.second.whiteRatingDiff : p.second.blackRatingDiff;
		cout << "Game mode:" << p.second.event << "| Opponent: " << p.first << " | Rating Diff: " << ratingDiff << " | Date: " << p.second.date << endl;
		i++;
		cout << endl;
	}
}