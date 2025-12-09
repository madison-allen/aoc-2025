#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

void partOne(std::vector<std::vector<unsigned long long>> ranges, std::vector<unsigned long long> list);
void partTwo(std::vector<std::vector<unsigned long long>> ranges);
bool customComparator(std::vector<unsigned long long> a, std::vector<unsigned long long> b);


int main() {
	char cwd[PATH_MAX];
	std::string dir = getcwd(cwd, sizeof(cwd));
	std::ifstream file(dir + "\\input.txt");
	std::string s;
	
	std::vector<std::vector<unsigned long long>> ranges;
	std::getline(file, s);
	while(s != "") {
		int i = 0;
		std::vector<unsigned long long> v;
		while(s.at(i) != '-') i++;
		unsigned long long start = std::stoull(s.substr(0, i));
		unsigned long long end = std::stoull(s.substr(i+1, s.length() - i));
		v.push_back(start);
		v.push_back(end);
		ranges.push_back(v);
		std::getline(file, s);
	}
	std::vector<unsigned long long> list;

	while(std::getline(file, s)) {
		list.push_back(std::stoull(s));
	}

	partOne(ranges, list);
	partTwo(ranges);

	return 0;
}

void partOne(std::vector<std::vector<unsigned long long>> ranges, std::vector<unsigned long long> list) {
	int count = 0;

	for(int i = 0; i < list.size(); i++) {
		for(int j = 0; j < ranges.size(); j++) {
			if(list[i] >= ranges[j][0] && list[i] <= ranges[j][1]) {
				count++;
				break;
			}
		}
	}

	std::cout << count << "\n";
}

void partTwo(std::vector<std::vector<unsigned long long>> ranges) {
	std::sort(ranges.begin(), ranges.end(), customComparator);
	unsigned long long count = 0;

	unsigned long long start = ranges[0][0];
	unsigned long long end = ranges[0][1];
	for(int i = 1; i < ranges.size(); i++) {
		if(ranges[i][0] <= end) {
			end = ranges[i][1] > end ? ranges[i][1] : end;
		}
		else {
			count += end - start + 1;
			start = ranges[i][0];
			end = ranges[i][1];
		}
	}
	count += end - start + 1;

	std::cout << count << "\n";
}

bool customComparator(std::vector<unsigned long long> a, std::vector<unsigned long long> b) {
	if(a[0] == b[0]) return a[1] < b[1];
	return a[0] < b[0];
}
