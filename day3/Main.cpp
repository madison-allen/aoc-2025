#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>

void partOne(std::ifstream* file);
void partTwo(std::ifstream* file);

int main() {
   char cwd[PATH_MAX];
   std::string dir = getcwd(cwd, sizeof(cwd));
   std::ifstream file = std::ifstream(dir + "\\input.txt");

   partOne(&file);

   file.clear();
   file.seekg(0);

   partTwo(&file);

   return 0;
}

void partOne(std::ifstream* file) {
   std::string s;
   int total = 0;

   while (std::getline(*file, s)) {
      int joltage = 0;
      int index = 0;
      for (int i = 0; i < s.length() - 1; i++)
      {
         if (joltage < s.at(i) - '0') {
            joltage = s.at(i) - '0';
            index = i;
         }
      }
      joltage *= 10;

      int max = 0;
      for (int i = index + 1; i < s.length(); i++)
      {
         if (max < s.at(i) - '0') max = s.at(i) - '0';
      }
      joltage += max;
      total += joltage;
   }

   std::cout << total << "\n";
}

void partTwo(std::ifstream* file) {
   std::string s;
   unsigned long long total = 0;

   while (std::getline(*file, s)) {
      unsigned long long joltage = 0;
      int index = 0;
      for (int i = 0; i < 12; i++)
      {
         int max = 0;
         int maxIndex = s.length() - (12 - i - 1);
         for (int j = index; j < maxIndex; j++)
         {
            if (max < s.at(j) - '0')
            {
               max = s.at(j) - '0';
               index = j + 1;
            }
         }
         joltage *= 10;
         joltage += max;
      }
      total += joltage;
   }

   std::cout << total << "\n";
}