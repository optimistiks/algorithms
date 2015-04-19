#include <vector>;
#include <iostream>;
#include <sstream>;
#include <string>;
#include <fstream>;
#include <algorithm>;
#include <unordered_map>;

using namespace std;

typedef unordered_map<int, unordered_map<int, int>> result;

struct Item {
	int value;
	int weight;

	bool operator < (const Item& item) const
	{
		return weight < item.weight;
	}
};

int getFromCache(int i, int x, unordered_map<string, int> & cache) {
	string key = to_string(i) + "-" + to_string(x);
	if (cache.count(key)) {
		return cache.at(key);
	}
	return -1;
}

void setToCache(int i, int x, unordered_map<string, int> & cache, int solution) {
	string key = to_string(i) + "-" + to_string(x);
	cache.insert(pair<string, int>(key, solution));
}

int solve(int i, int x, const vector<Item> & items, unordered_map<string, int> & cache, int & count) {
	++count;
	if (i == 0) return 0;

	int weight = items.at(i - 1).weight;
	int value = items.at(i - 1).value;

	int case1 = getFromCache(i - 1, x, cache);
	if (case1 == -1) {
		case1 = solve(i - 1, x, items, cache, count);
		setToCache(i - 1, x, cache, case1);
	}
	if (weight > x) {
		return case1;
	}

	int case2 = getFromCache(i - 1, x - weight, cache);

	if (case2 == -1) {
		case2 = solve(i - 1, x - weight, items, cache, count);
		setToCache(i - 1, x - weight, cache, case2);
	}

	case2 += value;

	return case1 > case2 ? case1 : case2;
}


int main() {
	ifstream infile("main2.txt");
	string line;

	vector<Item> items;
	int capacity;


	int c = 0;
	while (getline(infile, line))
	{
		istringstream iss(line);

		if (c == 0) {
			iss >> capacity;
		}
		else {
			Item item;
			iss >> item.value;
			iss >> item.weight;
			items.push_back(item);
		}

		++c;
	}

	sort(items.rbegin(), items.rend());
	
	unordered_map<string, int> cache;
	int depth = 0;
	cout << solve(items.size(), capacity, items, cache, depth) << endl;
	cout << depth << endl;

	return 0;
}