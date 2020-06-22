#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::cout << "Welcome to Study CLI" << std::endl;
  std::cout << "Your personal command line flashcards :)" << std::endl;

  std::cout << "Enter the file name: "; 
  std::string file_name;
  std::getline(std::cin, file_name);

  std::ifstream file(file_name);

  if (file.is_open()) {
    std::cout << "File has opened" << std::endl;
  } else {
    std::cout << "The file is not there" << std::endl;
  }

  return 0;
}
