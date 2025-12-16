#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
#include <cmath>
#include <unordered_set>
#include <vector>
#include <iostream>

const int PAIR_COUNT = 1000;

struct heap_pair {
	unsigned long long dist;
	std::pair<std::string, std::string> coords;
};

void partOne(std::vector<std::string> coords);
void partTwo(std::vector<std::string> coords);
bool compare_dist(heap_pair a, heap_pair b);
bool compare_size(std::unordered_set<std::string> a, std::unordered_set<std::string> b);
unsigned long long get_distance(std::string a, std::string b);
unsigned long long get_x(std::string s);

int main() {
	char cwd[PATH_MAX];
	std::string dir = getcwd(cwd, sizeof(cwd));
	std::ifstream file(dir + "\\input.txt");
	std::string s;

	std::vector<std::string> coords;
	while(std::getline(file, s)) {
		coords.push_back(s);
	}

	partOne(coords);
	partTwo(coords);

	return 0;
}

void partOne(std::vector<std::string> coords) {
	std::vector<heap_pair> heap;
	for(int i = 0; i < coords.size(); i++) {
		for(int j = i + 1; j < coords.size(); j++) {
			heap_pair temp;
			temp.dist = get_distance(coords[i], coords[j]);
			temp.coords = {coords[i], coords[j]};
			heap.push_back(temp);
		}
	}
	
	std::make_heap(heap.begin(), heap.end(), compare_dist);

	std::vector<std::unordered_set<std::string>> circuits;
	for(int i = 0; i < PAIR_COUNT; i++) {
		std::pop_heap(heap.begin(), heap.end(), compare_dist);
		heap_pair curr = heap.back();
		heap.pop_back();

		int found0 = -1;
		int found1 = -1;
		for(int j = 0; j < circuits.size(); j++) {
			if(circuits[j].count(std::get<0>(curr.coords)) == 1) found0 = j;
			if(circuits[j].count(std::get<1>(curr.coords)) == 1) found1 = j;
		}

		if(found0 != found1 && found0 != -1 && found1 != -1) {
			for(auto j = circuits[found0].begin(); j != circuits[found0].end(); j++) {
				circuits[found1].insert(*j);	
			}
			circuits.erase(circuits.begin() + found0);
		}
		else if(found0 == -1 && found1 == -1) {
			std::unordered_set<std::string> set;
			set.insert(std::get<0>(curr.coords));
			set.insert(std::get<1>(curr.coords));
			circuits.push_back(set);
		}
		else {
			int j = found0 == -1 ? found1 : found0;
			circuits[j].insert(std::get<0>(curr.coords));
			circuits[j].insert(std::get<1>(curr.coords));
		}
	}

	std::sort(circuits.begin(), circuits.end(), compare_size);

	std::cout << circuits[0].size() * circuits[1].size() * circuits[2].size() << "\n";
}

void partTwo(std::vector<std::string> coords) {
	std::vector<heap_pair> heap;
	for(int i = 0; i < coords.size(); i++) {
		for(int j = i + 1; j < coords.size(); j++) {
			heap_pair temp;
			temp.dist = get_distance(coords[i], coords[j]);
			temp.coords = {coords[i], coords[j]};
			heap.push_back(temp);
		}
	}
	
	std::make_heap(heap.begin(), heap.end(), compare_dist);

	std::vector<std::unordered_set<std::string>> circuits;
	heap_pair curr;
	while(true) {
		std::pop_heap(heap.begin(), heap.end(), compare_dist);
		curr = heap.back();
		heap.pop_back();

		int found0 = -1;
		int found1 = -1;
		for(int j = 0; j < circuits.size(); j++) {
			if(circuits[j].count(std::get<0>(curr.coords)) == 1) found0 = j;
			if(circuits[j].count(std::get<1>(curr.coords)) == 1) found1 = j;
		}

		if(found0 != found1 && found0 != -1 && found1 != -1) {
			for(auto j = circuits[found0].begin(); j != circuits[found0].end(); j++) {
				circuits[found1].insert(*j);	
			}
			circuits.erase(circuits.begin() + found0);
		}
		else if(found0 == -1 && found1 == -1) {
			std::unordered_set<std::string> set;
			set.insert(std::get<0>(curr.coords));
			set.insert(std::get<1>(curr.coords));
			circuits.push_back(set);
		}
		else {
			int j = found0 == -1 ? found1 : found0;
			circuits[j].insert(std::get<0>(curr.coords));
			circuits[j].insert(std::get<1>(curr.coords));
		}

		if(circuits[0].size() == coords.size()) break;
	}

	std::cout << get_x(std::get<0>(curr.coords)) * get_x(std::get<1>(curr.coords)) << "\n";
}

bool compare_dist(heap_pair a, heap_pair b) {
	return a.dist > b.dist;
}

bool compare_size(std::unordered_set<std::string> a, std::unordered_set<std::string> b) {
	return a.size() > b.size();
}

// don't look at this - it is bad and I don't care
unsigned long long get_distance(std::string a, std::string b) {
	int a_i = 0;
	int b_i = 0;
	unsigned long long count = 0;
	for(int i = 0; i < 3; i++) {
		int a_j = a_i;
		int b_j = b_i;
		while(a_j < a.length() && a.at(a_j) != ',') a_j++;
		while(b_j < b.length() && b.at(b_j) != ',') b_j++;
		unsigned long long max = std::max(std::stoull(a.substr(a_i, a_j-a_i)), std::stoull(b.substr(b_i, b_j-b_i)));
		unsigned long long min = std::min(std::stoull(a.substr(a_i, a_j-a_i)), std::stoull(b.substr(b_i, b_j-b_i)));
		count += std::pow(max-min, 2);
		a_i = a_j+1;
		b_i = b_j+1;
	}
	return std::sqrt(count);
}

unsigned long long get_x(std::string s) {
	for(int i = 0; i < s.length(); i++) {
		if(s.at(i) == ',') return std::stoull(s.substr(0, i));
	}
	return 0;
}
