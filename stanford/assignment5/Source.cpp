#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Edge {
	int from;
	int to;
	int length;
};

typedef int Vertex;
typedef vector<Edge> Edges;
typedef unordered_map<Vertex, Edges> AdjacencyList;
typedef AdjacencyList::iterator AdjListIterator;
typedef AdjacencyList::const_iterator AdjListConstIterator;
typedef Edges::iterator EdgesIterator;
typedef Edges::const_iterator EdgesConstIterator;

void printAdjList(AdjacencyList const & adjList) {
	for (AdjListConstIterator ait = adjList.begin(); ait != adjList.end(); ++ait) {
		cout << ait->first << endl;
		Edges e = ait->second;
		for (EdgesConstIterator eit = e.begin(); eit != e.end(); ++eit) {
			cout << " " << eit->to << "(" << eit->length << ")";
		}
		cout << endl;
	}
}

void printShortestPath(AdjacencyList const & adjList, Vertex const & from, Vertex const & to) {
	unordered_map<Vertex, bool> processedSoFar{ {from, true} };
	unordered_map<Vertex, int> distances = { { from, 0 } };

	Vertex v;
	Vertex w;

	while (!processedSoFar.count(to)) {
		int minScore = NULL;
		Edge minEdge;

		for (unordered_map<Vertex, bool>::const_iterator it = processedSoFar.begin(); it != processedSoFar.end(); ++it) {
			v = it->first;
			int score;
			Edges const & e = adjList.at(v);
			for (EdgesConstIterator eit = e.begin(); eit != e.end(); ++eit) {
				Edge edge = *eit;
				if (!processedSoFar.count(edge.to)) {
					score = distances.at(v) + edge.length;
					if (minScore == NULL || minScore > score) {
						minScore = score;
						minEdge = edge;
					}
				}
			}
		}

		processedSoFar.insert(pair<Vertex, bool>(minEdge.to, true));
		distances.insert(pair<Vertex, int>(minEdge.to, minScore));

	}

	cout << distances.at(to) << endl;
}

int main() {
	ifstream infile("1.txt");
	string line;

	AdjacencyList adjList;
	char comma;

	while (getline(infile, line))
	{
		Vertex v;
		Vertex to;
		int length;

		istringstream iss{ line };	
		iss >> v;
		
		if (!adjList.count(v)) {
			Edges e;
			adjList.insert(pair<Vertex, Edges>(v, e));
		}

		AdjListIterator it = adjList.find(v);

		while (!iss.eof()) {
			iss >> to >> comma >> length;
			Edge e;
			e.from = v;
			e.to = to;
			e.length = length;
			it->second.push_back(e);
		}
	}

	// printAdjList(adjList);

	printShortestPath(adjList, 1, 7);
	printShortestPath(adjList, 1, 37);
	printShortestPath(adjList, 1, 59);
	printShortestPath(adjList, 1, 82);
	printShortestPath(adjList, 1, 99);
	printShortestPath(adjList, 1, 115);
	printShortestPath(adjList, 1, 133);
	printShortestPath(adjList, 1, 165);
	printShortestPath(adjList, 1, 188);
	printShortestPath(adjList, 1, 197);

	return 0;
}