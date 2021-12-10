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
	int maxCounter = 20; //Caps the number of potential candidates as 20, as higher numbers have diminishing returns
	int requestedElo = 0; // stores the elo of the given name

	// since we don't know if they are black or white, look in the graph and return the proper elo
	if (adjList[name].at(0).second.blackID == name)
	{
		requestedElo = stoi(adjList[name].at(0).second.blackElo);
	}
	else if (adjList[name].at(0).second.whiteID == name)
	{
		requestedElo = stoi(adjList[name].at(0).second.whiteElo);
	}

	// Use these to find the highest matches and lowest elos.
	int minElo = INT_MAX; // find lowest elo
	int maxMatches = 0; // find maximum number of matches
	int closestElo = 0; // keep track of the lowest elo differences between players
	int requestedMatches = 0; // stores the number of matches the given player has played
	while (!q.empty())
	{
		string current = q.front();
		q.pop();

		// default values
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
			bool won = isWhite == stoi(p.second.whiteRatingDiff) > 0; //wins are when ELO goes up; ties are not counted
			if (won)
				wins++;
			else
				losses++;
			unsigned int time = p.second.getDateTime();
			if (time > maxTime) //Ensures player's ELO is from their last game played
			{
				maxTime = time;
				elo = isWhite ? stoi(p.second.whiteElo) : stoi(p.second.blackElo);
			}
			if (marked.find(p.first) == marked.end())
			{
				q.push(p.first);
				marked.insert(p.first);
			}

			/* this finds the player with the closest elo to the given one */
			if (abs(elo - requestedElo) < minElo && (current != name)) // obviously the same player has a difference of 0, so account for that
			{
				/* out of these, take the one with closest number of matches played to the given player*/
				if (abs((wins + losses) - requestedMatches) > maxMatches)
				{
					goodMatches.clear(); // clear the vector as we only want to store one value
					minElo = abs(elo - requestedElo); // keep track of the min elo. absolute value so no negatives
					maxMatches = abs((wins + losses) - requestedMatches); // keep track of the closest match counts.
					goodMatches.push_back(current); // push best result so far into the vector
					closestElo = elo; // keep track of the closest elo
				}
			}
		}

		//Caps loop at maxCounter
		counter++;
		if (counter > maxCounter)
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

/* DFS algorithm from the lectures 8b - Graph Traversals and Algorithms.pdf Slide 15*/
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

/* Djikstra's algorithm adapted from pseudocode in lecture 8b Slide 55*/
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
					d[i->first] = 1; //if source is right next to destination, quickly exits
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
		for (auto i = VS.begin(); i != VS.end(); i++) // finds minimum distance
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
		if (smallest == dest) //we don't need lengths of all vertices, just the destination
			return d[dest];
	}
	return d[dest];
}

/* Goes through the graph and print out all nodes adjacent to the one provided */
void Graph::getAdjacent(string vertex)
{
	cout << "Adjacent nodes:" << endl;
	for (int i = 0; i < adjList[vertex].size(); i++)
	{
		cout << i << ": " << adjList[vertex].at(i).first << endl;
	}

}

void Graph::printNames(int n)
{
	int count = 0;
	for (auto iter = adjList.begin(); iter != adjList.end(); iter++)
	{
		for (int i = 0; i < iter->second.size(); i++)
		{
			cout << count << ": " << iter->second.at(i).first << endl;
			count++;
		}

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
