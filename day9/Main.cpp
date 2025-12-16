#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <unordered_set>

void partOne(std::vector<std::pair<unsigned long long, unsigned long long>> list);
void partTwo(std::vector<std::pair<unsigned long long, unsigned long long>> list);
std::pair<unsigned long long, unsigned long long> split(std::string s);

int main() {
	char cwd[PATH_MAX];
	std::string dir = getcwd(cwd, sizeof(cwd));
	std::ifstream file(dir + "\\input.txt");
	std::string s;

	std::vector<std::pair<unsigned long long, unsigned long long>> list;
	while(std::getline(file, s)) {
		list.push_back(split(s));
	}

	partOne(list);
	partTwo(list);

	return 0;
}

void partOne(std::vector<std::pair<unsigned long long, unsigned long long>> list) {
	unsigned long long max_area = 0;

	for(int i = 0; i < list.size(); i++) {
		for(int j = i + 1; j < list.size(); j++) {
			unsigned long long x0 = std::max(std::get<0>(list[i]), std::get<0>(list[j])); 
			unsigned long long x1 = std::min(std::get<0>(list[i]), std::get<0>(list[j]));
			unsigned long long y0 = std::max(std::get<1>(list[i]), std::get<1>(list[j]));
			unsigned long long y1 = std::min(std::get<1>(list[i]), std::get<1>(list[j]));
			max_area = std::max(max_area, (x0-x1+1) * (y0-y1+1));
		}
	}

	std::cout << max_area << "\n";
}

void partTwo(std::vector<std::pair<unsigned long long, unsigned long long>> list) {

}

std::pair<unsigned long long, unsigned long long> split(std::string s) {
	for(int i = 0; i < s.length(); i++) {
		if(s.at(i) == ',') {
			return {std::stoi(s.substr(0, i)), std::stoi(s.substr(i+1, s.length() - i + 1))};
		}
	}
	return {0,0};
}
