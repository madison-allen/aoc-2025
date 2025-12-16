#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>

void partOne(std::vector<std::vector<char>> grid);
void partTwo(std::vector<std::vector<char>> grid);
int checkNeighbors(std::vector<std::vector<char>> grid, int row, int col);

int main() {
   char cwd[PATH_MAX];
   std::string dir = getcwd(cwd, sizeof(cwd));
   std::ifstream file(dir + "\\input.txt");
   std::string s;
   std::vector<std::vector<char>> grid;

   int index = 0;
   while (std::getline(file, s))
   {
      grid.push_back(std::vector<char>());
      for (int i = 0; i < s.length(); i++)
      {
         grid.at(index).push_back(s.at(i));
      }
      index++;
   }

   partOne(grid);
   partTwo(grid);

   return 0;
}

void partOne(std::vector<std::vector<char>> grid) {
   int count = 0;

   for (int i = 0; i < grid.size(); i++)
   {
      for (int j = 0; j < grid.at(0).size(); j++)
      {
         if (grid[i][j] == '@')
         {
            count += checkNeighbors(grid, i, j);
         }
      }
   }

   std::cout << count << "\n";
}

void partTwo(std::vector<std::vector<char>> grid) {
   int count = 0;
   int prev = -1;

   while (count != prev)
   {
      prev = count;

      for (int i = 0; i < grid.size(); i++)
      {
         for (int j = 0; j < grid.at(0).size(); j++)
         {
            if (grid[i][j] == '@')
            {
               if(checkNeighbors(grid, i, j) == 1) {
                  count++;
                  grid[i][j] = '.';
               }
            }
         }
      }
   }

   std::cout << count << "\n";
}

int checkNeighbors(std::vector<std::vector<char>> grid, int row, int col) {
   int count = 0;

   int dirs[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

   for (int i = 0; i < 8; i++)
   {
      int r = dirs[i][0] + row;
      int c = dirs[i][1] + col;
      if (r >= 0 && r < grid.size() && c >= 0 && c < grid.at(0).size() && grid[r][c] == '@')
      {
         count++;
      }
   }

   return count < 4 ? 1 : 0;
}
