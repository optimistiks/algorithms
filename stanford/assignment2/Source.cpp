#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

vector<int>::iterator choosePivotFirst(const vector<int>::iterator first, const vector<int>::iterator end) {
	return first;
}

vector<int>::iterator choosePivotLast(const vector<int>::iterator first, const vector<int>::iterator end) {
	return end - 1;
}

vector<int>::iterator choosePivotMedian(const vector<int>::iterator first, const vector<int>::iterator end) {
	int n = distance(first, end);
	vector<int>::iterator middle = n % 2 == 0 ? first + (n / 2 - 1) : first + n / 2;
	vector<int>::iterator last = end - 1;

	if ((*first - *middle) * (*last - *first) >= 0) {
		return first;
	}
	else if ((*middle - *first) * (*last - *middle) >= 0) {
		return middle;
	}
	else {
		return last;
	}
}

void partition(const vector<int>::iterator first, const vector<int>::iterator end, vector<int>::iterator &p) {
	vector<int>::iterator i = p + 1;
	vector<int>::iterator j;
	for (j = p + 1; j != end; ++j) {
		if (*j < *p) {
			swap(*j, *i);
			++i;
		}
	}
	swap(*p, *(i - 1));
	swap(p, i - 1);
}

void quickSort(const vector<int>::iterator first, const vector<int>::iterator end, unsigned long &count) {
	int n = distance(first, end);

	if (n <= 1) {
		return;
	}

	count += n - 1;

	vector<int>::iterator p = choosePivotMedian(first, end);

	swap(*p, *first);
	p = first;

	partition(first, end, p);
	quickSort(first, p, count);
	quickSort(p + 1, end, count);
}

int main() {
	ifstream infile("../QuickSort.txt");
	string line;
	vector<int> numbers;
	int number;

	while (getline(infile, line))
	{
		istringstream iss(line);
		iss >> number;
		numbers.push_back(number);
	}

	unsigned long count = 0;
	quickSort(numbers.begin(), numbers.end(), count);

	cout << count << endl;

	return 0;
}