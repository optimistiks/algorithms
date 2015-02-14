#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

typedef int Vertex;
typedef vector<Vertex> Edges;
typedef map<Vertex, Edges> AdjacencyList;
typedef AdjacencyList::const_iterator MapIterator;

bool isExplored(map<Vertex, bool> const & explored, Vertex const & v) {
	return explored.count(v) == 1;
};

void DFS1(AdjacencyList const & adjList, Vertex & s, map<Vertex, bool> & explored, int & t, map<int, Vertex> & fTimes) {
	explored.insert(pair<Vertex, bool>(s, true));
	Edges const & edges = adjList.at(s);
	for (Edges::const_iterator it = edges.begin(); it != edges.end(); ++it) {
		Vertex v = *it;
		if (!isExplored(explored, v)) {
			DFS1(adjList, v, explored, t, fTimes);
		}
	}
	++t;
	fTimes.insert(pair<int, Vertex>(t, s));
};

void DFS2(AdjacencyList const & adjList, Vertex & s, map<Vertex, bool> & explored, Vertex & leader, map<Vertex, Vertex> & leaders, map<Vertex, int> & sizes) {
	explored.insert(pair<Vertex, bool>(s, true));
	leaders.insert(pair<Vertex, Vertex>(s, leader));

	//change size of SCC
	map<Vertex, int>::iterator it = sizes.find(leader);
	if (it == sizes.end()) {
		sizes.insert(pair<Vertex, int>(leader, 1));
	}
	else {
		++it->second;
	}

	if (adjList.count(s) == 1) {
		Edges const & edges = adjList.at(s);

		for (Edges::const_iterator it = edges.begin(); it != edges.end(); ++it) {
			Vertex v = *it;
			if (!isExplored(explored, v)) {
				DFS2(adjList, v, explored, leader, leaders, sizes);
			}
		}
	}
};

void reverse(AdjacencyList const & adjList, AdjacencyList & reversedAdjList) {
	for (MapIterator iter = adjList.begin(); iter != adjList.end(); ++iter)
	{
		Edges e;
		reversedAdjList.insert(pair<Vertex, Edges>(iter->first, e));
		typedef vector<int>::const_iterator VectorIterator;
		for (VectorIterator vec_iter = iter->second.begin(); vec_iter != iter->second.end(); ++vec_iter) {
			Vertex key = *vec_iter;
			AdjacencyList::iterator it = reversedAdjList.find(key);
			if (it == reversedAdjList.end()) {
				Edges edges{ iter->first };
				reversedAdjList.insert(pair<Vertex, Edges>(key, edges));
			}
			else {
				it->second.push_back(iter->first);
			}
		}
	}
};

int main() {
	ifstream infile("scc.txt");
	string line;

	AdjacencyList adjList;
	int idx = 1;
	while (getline(infile, line))
	{
		istringstream iss{line};

		Edges tokens{ istream_iterator<Vertex>{iss}, istream_iterator<Vertex>{} };

		Vertex key = tokens.at(0);
		tokens.erase(tokens.begin());

		AdjacencyList::iterator it = adjList.find(key);
		if (it == adjList.end()) {
			adjList.insert(pair<Vertex, Edges>(key, tokens));
		}
		else {
			it->second.insert(it->second.end(), tokens.begin(), tokens.end());
		}

		cout << idx++ << endl;
	}

	//create a reversed version
	AdjacencyList reversedAdjList;
	reverse(adjList, reversedAdjList);

	map<Vertex, bool> explored;

	cout << "loop 1" << endl;
	// loop 1
	map<int, Vertex> fTimes;
	int t = 0;
	for (AdjacencyList::const_reverse_iterator iter = reversedAdjList.rbegin(); iter != reversedAdjList.rend(); ++iter)
	{
		Vertex i = iter->first;
		if (!isExplored(explored, i)) {
			DFS1(reversedAdjList, i, explored, t, fTimes);
		}
	}

	cout << "loop 2" << endl;
	// loop 2
	explored.clear();
	Vertex leader;
	map<Vertex, Vertex> leaders;
	map<Vertex, int> sizes;
	for (map<int, Vertex>::const_reverse_iterator iter = fTimes.rbegin(); iter != fTimes.rend(); ++iter)
	{
		Vertex i = iter->second;
		if (!isExplored(explored, i)) {
			leader = i;
			DFS2(adjList, i, explored, leader, leaders, sizes);
		}
	}

	vector<int> leaderSizes;
	for (map<Vertex, int>::const_iterator iter = sizes.begin(); iter != sizes.end(); ++iter)
	{
		leaderSizes.push_back(iter->second);
	}

	sort(leaderSizes.begin(), leaderSizes.end());

	cout << leaderSizes.at(leaderSizes.size() - 1) << endl;
	cout << leaderSizes.at(leaderSizes.size() - 2) << endl;
	cout << leaderSizes.at(leaderSizes.size() - 3) << endl;
	cout << leaderSizes.at(leaderSizes.size() - 4) << endl;
	cout << leaderSizes.at(leaderSizes.size() - 5) << endl;

	return 0;
}