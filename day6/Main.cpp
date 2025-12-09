#include <iostream>
#include <fstream>
#include <vector>

void partOne(std::vector<std::vector<unsigned long long>> grid, std::vector<char> ops);
void partTwo(std::vector<std::vector<std::string>> grid, std::vector<char> ops);
std::vector<unsigned long long> split(std::string s);
std::vector<char> split_ops(std::string s, std::vector<int>& indices);
std::vector<unsigned long long> rearrange_digits(std::vector<std::string> grid);

int main() {
	char cwd[PATH_MAX];
	std::string dir = getcwd(cwd, sizeof(cwd));
	std::ifstream file(dir + "\\input.txt");

	std::string next;
	std::string s;
	std::getline(file, s);

	int size = split(s).size();
	std::vector<std::vector<unsigned long long>> grid(size, std::vector<unsigned long long>());
	while(std::getline(file, next)) {
		std::vector v = split(s);
		for(int i = 0; i < v.size(); i++) {
			grid[i].push_back(v[i]);
		}
		s = next;
	}

	std::vector<int> indices;
	std::vector<char> ops = split_ops(s, indices);

	partOne(grid, ops);

	file.clear();
	file.seekg(0);
	std::getline(file, s);

	std::vector<std::vector<std::string>> string_grid(size, std::vector<std::string>());
	while(std::getline(file, next)) {
		for(int i = 0; i < indices.size() - 1; i++) {
			std::string num = s.substr(indices[i], indices[i+1]-1-indices[i]);
			string_grid[i].push_back(num);
		}
		s = next;
	}

	partTwo(string_grid, ops);

	return 0;
}

void partOne(std::vector<std::vector<unsigned long long>> grid, std::vector<char> ops) {
	unsigned long long sum = 0;

	for(int i = 0; i < ops.size(); i++) {
		unsigned long long n = ops[i] == '*' ? 1 : 0;
		for(int j = 0; j < grid[i].size(); j++) {
			if(ops[i] == '+') n += grid[i][j];
			else n *= grid[i][j];
		}
		sum += n;
	}

	std::cout << sum << "\n";
}

void partTwo(std::vector<std::vector<std::string>> grid, std::vector<char> ops) {
	std::vector<std::vector<unsigned long long>> new_grid;
	unsigned long long sum = 0;

	for(int i = 0; i < grid.size(); i++) {
		new_grid.push_back(rearrange_digits(grid[i]));
	}

	for(int i = 0; i < ops.size(); i++) {
		unsigned long long n = ops[i] == '*' ? 1 : 0;
		for(int j = 0; j < new_grid[i].size(); j++) {
			if(ops[i] == '+') n += new_grid[i][j];
			else n *= new_grid[i][j];
		}
		sum += n;
	}

	std::cout << sum << "\n";
}

std::vector<unsigned long long> split(std::string s) {
	std::vector<unsigned long long> vector;
	for(unsigned long long i = 0; i < s.length(); i++) {
		while(i < s.length() && s.at(i) == ' ') i++;
		unsigned long long j = i;
		while(j < s.length() && s.at(j) != ' ') j++;
		vector.push_back(std::stoull(s.substr(i, j-i)));
		i = j;
	}
	return vector;
}

std::vector<char> split_ops(std::string s, std::vector<int>& indices) {
	std::vector<char> vector;
	for(unsigned long long i = 0; i < s.length(); i++) {
		while(i < s.length() && s.at(i) == ' ') i++;
		if(i < s.length()) {
			vector.push_back(s.at(i));
			indices.push_back(i);
		}
	}
	indices.push_back(s.length() + 1);
	return vector;
}

std::vector<unsigned long long> rearrange_digits(std::vector<std::string> grid) {
	std::vector<unsigned long long> new_grid;
	
	for(int i = 0; i < grid[0].length(); i++) {
		unsigned long long n = 0;
		for(int j = 0; j < grid.size(); j++) {
			if(grid[j].at(i) == ' ') continue;
			n *= 10;
			n += grid[j].at(i) - '0';
		}
		new_grid.push_back(n);
	}

	return new_grid;
}
