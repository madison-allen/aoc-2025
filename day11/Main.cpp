#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <unordered_map>
#include <queue>

void partOne(std::unordered_map<std::string, std::vector<std::string>> map);
void partTwo(std::unordered_map<std::string, std::vector<std::string>> map);
void buildList(std::string s, std::unordered_map<std::string, std::vector<std::string>>& map);
unsigned long long helper(std::string key,
                          std::string end,
                          std::unordered_map<std::string, std::vector<std::string>>& map);
unsigned long long dfs(std::string key,
                       std::string end,
                       std::unordered_map<std::string, std::vector<std::string>>& map,
                       std::unordered_map<std::string, unsigned long long>& memo);


int main() {
   char cwd[PATH_MAX];
   std::string dir = getcwd(cwd, sizeof(cwd));
   std::ifstream file(dir + "\\input.txt");
   std::string s;

   std::unordered_map<std::string, std::vector<std::string>> map;
   while (std::getline(file, s))
   {
      buildList(s, map);
   }

   partOne(map);
   partTwo(map);

   return 0;
}

void partOne(std::unordered_map<std::string, std::vector<std::string>> map) {
   int count = 0;
   std::queue<std::string> queue;
   queue.push("you");

   while (!queue.empty())
   {
      int n = queue.size();
      for (int i = 0; i < n; i++)
      {
         std::string key = queue.front();
         queue.pop();
         if (key == "out") {
            count++;
            continue;
         }

         std::vector<std::string> v = map[key];
         for (auto j = v.begin(); j != v.end(); j++)
         {
            queue.push(*j);
         }
      }
   }

   std::cout << count << "\n";
}

void partTwo(std::unordered_map<std::string, std::vector<std::string>> map) {
   unsigned long long count = 0;

   count += helper("svr", "dac", map) * helper("dac", "fft", map) * helper("fft", "out", map);
   count += helper("svr", "fft", map) * helper("fft", "dac", map) * helper("dac" ,"out", map);

   std::cout << count << "\n";
}

void buildList(std::string s, std::unordered_map<std::string, std::vector<std::string>>& map) {
   std::vector<std::string> entry;
   std::string key;

   int i = 0;
   while (s.at(i) != ':') i++;
   key = s.substr(0, i);

   i += 2;
   while (i < s.length())
   {
      int j = i;
      while (i < s.length() && s.at(i) != ' ') i++;
      entry.push_back(s.substr(j, i-j));
      i++;
   }

   map.insert({key, entry});
}

unsigned long long helper(std::string key,
                          std::string end,
                          std::unordered_map<std::string, std::vector<std::string>>& map) {
   std::unordered_map<std::string, unsigned long long> memo;
   return dfs(key, end, map, memo);
}

unsigned long long dfs(std::string key,
                       std::string end,
                       std::unordered_map<std::string, std::vector<std::string>>& map,
                       std::unordered_map<std::string, unsigned long long>& memo) {
   if (key == end) return 1;
   if (memo.count(key) == 1) return memo[key];

   unsigned long long count = 0;
   std::vector<std::string> v = map[key];
   for (auto j = v.begin(); j != v.end(); j++)
   {
      count += dfs(*j, end, map, memo);
   }

   memo.insert({key, count});

   return count;
}
