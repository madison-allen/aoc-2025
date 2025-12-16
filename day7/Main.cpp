#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

void partOne(std::vector<std::vector<char>> grid);
void partTwo(std::vector<std::vector<char>> grid);
unsigned long long traversal(std::vector<std::vector<char>> grid,
              std::pair<int, int> pair,
              std::unordered_map<std::pair<int, int>, unsigned long long, pair_hash>& cache);


int main() {
   char cwd[PATH_MAX];
   std::string dir = getcwd(cwd, sizeof(cwd));
   std::ifstream file(dir + "\\input.txt");
   std::string s;

   std::vector<std::vector<char>> grid;

   while (std::getline(file, s))
   {
      std::vector<char> v;
      for (int i = 0; i < s.length(); i++)
      {
         v.push_back(s.at(i));
      }
      grid.push_back(v);
   }

   partOne(grid);
   partTwo(grid);

   return 0;
}

void partOne(std::vector<std::vector<char>> grid) {
   unsigned long long count = 0;

   std::unordered_set<std::pair<int, int>, pair_hash> set;
   for (int i = 0; i < grid[0].size(); i++)
   {
      if (grid[0][i] == 'S')
      {
         set.insert(std::pair<int, int>{1, i});
         break;
      }
   }

   while (!set.empty())
   {
      std::unordered_set<std::pair<int, int>, pair_hash> next;

      for (auto i = set.begin(); i != set.end(); i++)
      {
         int row = std::get<0>(*i);
         int col = std::get<1>(*i);
         if (col < 0 || col >= grid[0].size()) continue;

         while (row < grid.size())
         {
            if (grid[row][col] == '^')
            {
               grid[row][col] = '-';
               count++;
               next.insert({row, col-1});
               next.insert({row, col+1});
               break;
            }
            else if (grid[row][col] == '-') break;

            row++;
         }
      }

      set = next;
   }

   std::cout << count << "\n";
}

void partTwo(std::vector<std::vector<char>> grid) {
   std::unordered_map<std::pair<int, int>, unsigned long long, pair_hash> cache;
   std::pair<int, int> pair;
   for (int i = 0; i < grid[0].size(); i++)
   {
      if (grid[0][i] == 'S')
      {
         pair = {1, i};
         break;
      }
   }

   std::cout << traversal(grid, pair, cache) << "\n";
}

unsigned long long traversal(std::vector<std::vector<char>> grid,
   std::pair<int, int> pair,
   std::unordered_map<std::pair<int, int>, unsigned long long, pair_hash>& cache) {
   unsigned long long count = 0;

   int row = std::get<0>(pair);
   int col = std::get<1>(pair);
   if (col < 0 || col >= grid[0].size()) return 1;

   while (row < grid.size())
   {
      if (cache.count({row, col}) == 1)
      {
         return cache.at({row, col});
      }
      else if (grid[row][col] == '^')
      {
         unsigned long long left = traversal(grid, {row, col-1}, cache);
         unsigned long long right = traversal(grid, {row, col+1}, cache);
         cache[{row, col-1}] = left;
         cache[{row, col+1}] = right;
         count += left + right;
         break;
      }

      row++;
   }

   if (row == grid.size()) return 1;
   return count;
}
