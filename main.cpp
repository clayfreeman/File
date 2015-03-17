/**
 * @file  main.cpp
 * @brief File Driver
 *
 * Test driver for File class
 *
 * @author     Clay Freeman
 * @date       March 17, 2015
 */

#include <iostream>
#include "File.h"

int main() {
  std::cout << (File::exists("test.txt") ? "exist\n" : "!exist\n");
  std::cout << (File::readable("test.txt") ? "readable\n" : "!readable\n");
  std::cout << (File::writable("test.txt") ? "writable\n" : "!writable\n");
  File::create("test.txt");
  std::cout << "create?\n";
  std::cout << (File::exists("test.txt") ? "exist\n" : "!exist\n");
  std::cout << (File::readable("test.txt") ? "readable\n" : "!readable\n");
  std::cout << (File::writable("test.txt") ? "writable\n" : "!writable\n");
  std::cout << "\n{put,get}Content?\n";
  File::putContent("test.txt", "hello\n");
  File::putContent("test.txt", "hello\n");
  File::putContent("test.txt", "hello\n", true);
  std::cout << File::getContent("test.txt") << '\n';
  std::cout << "directory: " << File::directory("text.txt") << '\n';
  std::cout << "realPath:  " << File::realPath("test.txt") << '\n';
  std::cout << '\n';
  File::truncate("test.txt");
  std::cout << "truncate? " << File::getContent("test.txt") << '\n';
  std::cout << "remove?\n";
  File::remove("test.txt");
  return 0;
}
