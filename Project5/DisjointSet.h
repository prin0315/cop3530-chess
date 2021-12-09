#pragma once
#include <iostream> 
#include <set> 
#include <vector> 
#include <map> 
#include <unordered_map> 
#include <climits> 

class DisjointSet {

    unordered_map<int, int> parent;

public:
    void makeSet(const set<int>& vertices) {
        for (int v : vertices) {
            parent[v] = v;
        }
    }

    // find the root of the set in which vertex k belongs to 
    int findRoot(int k) {
        if (parent[k] == k)
            return k;
        return findRoot(parent[k]);
    }

    // union two subsets that a and b are inside 
    void unionSet(int a, int b) {
        // find the roots of two sets in which  
  // vertex a and b belongs to 
        int x = findRoot(a);
        int y = findRoot(b);

        parent[y] = x;
    }

};