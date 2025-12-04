#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>

void partOne(std::string s);
void partTwo(std::string s);
long long idCheck(std::string id);

int main() {
   char cwd[PATH_MAX];
   std::string dir = getcwd(cwd, sizeof(cwd));
   std::ifstream file(dir + "\\input.txt");
   std::string s;
   std::getline(file, s);

   partOne(s);
   partTwo(s);

   return 0;
}

void partOne(std::string s) {
   int startIndex = 0;
   int endIndex = s.find(",", startIndex);
   long long count = 0;

   while (startIndex != s.length() + 1)
   {
      std::string ids = s.substr(startIndex, endIndex - startIndex);
      long long begin = std::stoll(ids.substr(0, ids.find("-")));
      long long end = std::stoll(ids.substr(ids.find("-") + 1, ids.length()));

      for (long long i = begin; i <= end; i++)
      {
         std::string str = std::to_string(i);
         count += str.substr(0, str.length() / 2) == str.substr(str.length() / 2, str.length()) ? i : 0;
      }

      startIndex = endIndex + 1;
      endIndex = s.find(",", startIndex);
      if (endIndex == -1) endIndex = s.length();
   }

   std::cout << count << "\n";
}

void partTwo(std::string s) {
   int startIndex = 0;
   int endIndex = s.find(",", startIndex);
   long long count = 0;

   while (startIndex != s.length() + 1)
   {
      std::string ids = s.substr(startIndex, endIndex - startIndex);
      long long begin = std::stoll(ids.substr(0, ids.find("-")));
      long long end = std::stoll(ids.substr(ids.find("-") + 1, ids.length()));

      for (long long i = begin; i <= end; i++)
      {
         count += idCheck(std::to_string(i));
      }

      startIndex = endIndex + 1;
      endIndex = s.find(",", startIndex);
      if (endIndex == -1) endIndex = s.length();
   }

   std::cout << count;
}

long long idCheck(std::string id) {
   int left = 0;
   int right = 1;
   while (right < id.length())
   {
      int r = right;
      while (right + (right - left) <= id.length() && id.substr(left, right - left) == id.substr(right, right - left))
      {
         int temp = right;
         right += right - left;
         left = temp;
      }
      if (right == id.length()) return std::stoll(id);

      left = 0;
      right = r + 1;
   }

   return 0;
}