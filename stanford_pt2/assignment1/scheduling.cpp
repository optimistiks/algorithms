#include <vector>;
#include <iostream>;
#include <sstream>;
#include <string>;
#include <fstream>;
#include <algorithm>;

using namespace std;

struct Job {
	int weight;
	int length;
	float score;
	unsigned long long completion;

	bool operator < (const Job& job) const
	{
		if (score != job.score) return score < job.score;
		else                    return weight < job.weight;
	}
};

int main() {
	ifstream infile("main.txt");
	string line;
	vector<Job> jobs;

	int weight;
	int length;

	int c = 0;

	while (getline(infile, line))
	{	
		++c;
		if (c == 1) continue;
		istringstream iss(line);
		iss >> weight;
		iss >> length;

		Job j;
		j.weight = weight;
		j.length = length;
		j.score = (float)weight / length;

		jobs.push_back(j);
	}	

	cout << jobs.size() << endl;

	sort(jobs.begin(), jobs.end());

	unsigned long long completion = 0;
	unsigned long long sum = 0;

	for (vector<Job>::reverse_iterator it = jobs.rbegin(); it != jobs.rend(); ++it) {
		completion += (*it).length;
		(*it).completion = completion;
		sum += (completion * (*it).weight);
	}

	cout << sum << endl;

	return 0;
}