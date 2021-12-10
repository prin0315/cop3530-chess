#pragma once
#include <iostream> 
#include <set> 
#include <vector> 
#include <map> 
#include <unordered_map> 
#include <climits> 

class DisjointSet {

    unordered_map<string, string> parent;

public:
    void makeSet(const set<string>& vertices) {
        for (string v : vertices) {
            parent[v] = v;
        }
    }

    // find the root of the set in which vertex k belongs to 
    string findRoot(string k) {
        if (parent[k] == k)
            return k;
        return findRoot(parent[k]);
    }

    // union two subsets that a and b are inside 
    void unionSet(string a, string b) {
        // find the roots of two sets in which  
  // vertex a and b belongs to 
        string x = findRoot(a);
        string y = findRoot(b);

        parent[y] = x;
    }

};