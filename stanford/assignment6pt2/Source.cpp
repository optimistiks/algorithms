#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

struct comparator{
	bool operator() (int i, int j) {
		return i > j;
	}
};

typedef priority_queue<int, vector<int>, comparator> MinHeap;
typedef priority_queue<int, vector<int>> MaxHeap;


int main() {
	ifstream infile("Median.txt");
	string line;
	int number;
	MaxHeap lesserHalf;
	MinHeap biggerHalf;

	int medianSum = 0;

	while (getline(infile, line))
	{
		istringstream iss{ line };
		iss >> number;



		if (lesserHalf.empty() || number < lesserHalf.top()) {
			lesserHalf.push(number);
		}
		else {
			biggerHalf.push(number);
		}

		if (biggerHalf.size() - lesserHalf.size() == 2) {
			lesserHalf.push(biggerHalf.top());
			biggerHalf.pop();
		}

		if (lesserHalf.size() - biggerHalf.size() == 2) {
			biggerHalf.push(lesserHalf.top());
			lesserHalf.pop();
		}

		int k = biggerHalf.size() + lesserHalf.size();
		int median = k % 2 == 0 ? lesserHalf.top() : (biggerHalf.size() > lesserHalf.size() ? biggerHalf.top() : lesserHalf.top());

		medianSum += median;
	}

	cout << medianSum % 10000 << endl;

	return 0;
}