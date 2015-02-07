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

int main() {
	srand(time(NULL));

	ifstream infile("../kargerMinCut.txt");
	string line;

	vector<int> vertices;
	map <int, vector<int>> adjList;

	while (getline(infile, line))
	{
		istringstream iss{ line };

		vector<int> tokens{ istream_iterator<int>{iss},
			istream_iterator<int>{} };

		int key = tokens.at(0);
		tokens.erase(tokens.begin());

		vertices.push_back(key);
		adjList.insert(pair<int, vector<int>>(key, tokens));
	}

	while (vertices.size() > 2) {
		// Select one vertex at random. let this be V1.
		int v1 = vertices.at(rand() % vertices.size());

		// Select one vertex (also at random) from adj list of V1. let this be V2.
		vector<int> & v1AdjList = adjList.at(v1);
		int v2 = v1AdjList.at(rand() % v1AdjList.size());

		// MERGE() adj list of V2 into adj list of V1.
		vector <int> & v2AdjList = adjList.at(v2);
		v1AdjList.insert(v1AdjList.end(), v2AdjList.begin(), v2AdjList.end());

		// REMOVE SELF LOOPS : Remove V1 and V2(if any) from the merged adj list.
		for (int i = 0; i != v1AdjList.size(); ++i) {
			if (v1AdjList.at(i) == v1 || v1AdjList.at(i) == v2) {
				v1AdjList.erase(v1AdjList.begin() + i);
				--i;
			}
		}

		//Loop through V1s adj list. Let Ai be the ith element in the list. Go to Ai's adj list,
		//Search and rename any and all V2 entry as V1.
		for (int i = 0; i != v1AdjList.size(); ++i) {
			int ai = v1AdjList.at(i);
			vector <int> & aiAdjList = adjList.at(ai);
			for (int j = 0; j != aiAdjList.size(); ++j) {
				if (aiAdjList.at(j) == v2) {
					aiAdjList.at(j) = v1;
				}
			}
		}

		// Delete V2 node with its adj list.
		for (int i = 0; i != vertices.size(); ++i) {
			if (vertices.at(i) == v2) {
				vertices.erase(vertices.begin() + i);
				break;
			}
		}
		adjList.erase(v2);
	}

	cout << adjList.begin()->second.size() << endl;

	return 0;
}