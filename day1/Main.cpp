#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <unistd.h>

void partOne(std::ifstream* file);
void partTwo(std::ifstream* file);

int main() {
   char cwd[PATH_MAX];
   std::string dir = getcwd(cwd, sizeof(cwd));
   std::ifstream file(dir + "\\input.txt");

   partOne(&file);

   file.clear();
   file.seekg(0);

   partTwo(&file);

   return 0;
}

void partOne(std::ifstream* file) {
   std::string s;

   std::map<char, int> dir;
   dir['L'] = -1;
   dir['R'] = 1;

   int pos = 50;
   int count = 0;
   while(std::getline(*file, s)) {
      int n = dir[s.at(0)] * std::stoi(s.substr(1, s.length()));
      pos = (pos + n) % 100;
      count += pos == 0 ? 1 : 0;
   }

   std::cout << count << "\n";
}

void partTwo(std::ifstream* file) {
   std::string s;

   std::map<char, int> dir;
   dir['L'] = -1;
   dir['R'] = 1;

   int pos = 50;
   int count = 0;
   while(std::getline(*file, s)) {
      int n = std::stoi(s.substr(1, s.length()));
      while(n != 0) {
         pos += dir[s.at(0)];
         n--;
         pos %= 100;
         count += pos == 0 ? 1 : 0;
      }
   }

   std::cout << count << "\n";
}