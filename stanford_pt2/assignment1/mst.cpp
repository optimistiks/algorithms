#include <vector>;
#include <iostream>;
#include <sstream>;
#include <string>;
#include <fstream>;
#include <algorithm>;
#include <unordered_map>;


using namespace std;

typedef int Vertex;

struct Edge {
	Vertex from;
	Vertex to;
	int cost;
};

typedef vector<Edge> Edges;
typedef unordered_map<Vertex, Edges> AdjacencyList;

int main() {
	ifstream infile("main.txt");
	string line;

	AdjacencyList adjList;
	Edges edges;

	Vertex from;
	Vertex to;
	int cost;

	int c = 0;
	while (getline(infile, line))
	{	
		++c;
		if (c == 1) continue;

		istringstream iss(line);
		iss >> from;
		iss >> to;
		iss >> cost;

		if (adjList.find(from) == adjList.end()) {
			adjList.insert(pair<Vertex, Edges>(from, Edges()));
		}

		if (adjList.find(to) == adjList.end()) {
			adjList.insert(pair<Vertex, Edges>(to, Edges()));
		}

		Edge eFromTo;
		eFromTo.from = from;
		eFromTo.to = to;
		eFromTo.cost = cost;

		Edge eToFrom;
		eToFrom.from = to;
		eToFrom.to = from;
		eToFrom.cost = cost;

		adjList.find(from)->second.push_back(eFromTo);
		adjList.find(to)->second.push_back(eToFrom);

		edges.push_back(eFromTo);
		edges.push_back(eToFrom);
	}	

	cout << adjList.size() << endl;

	unordered_map<int, bool> spanned{ pair<int, bool>(adjList.begin()->first, true) };
	vector<Edge> tree;
	long long sum = 0;

	while (spanned.size() != adjList.size()) {
		Edge min;
		min.from = 0;
		for (Edges::const_iterator eit = edges.begin(); eit != edges.end(); ++eit) {
			if (!spanned.count((*eit).to) && spanned.count((*eit).from) && (min.from == 0 || min.cost > (*eit).cost)) {
				min = *eit;
			}
		}
		if (min.from != 0) {
			cout << "found min edge going from " << min.from << " to " << min.to << " with cost " << min.cost << endl;
			spanned.insert(pair<int, bool>(min.to, true));
			tree.push_back(min);
			sum += min.cost;
		}
	}

	cout << sum << endl;

	return 0;
}