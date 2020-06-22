#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void print_vector(
    const std::vector<std::pair<std::string, std::string>>& questions) {}

int main() {
  std::cout << "Welcome to Study CLI" << std::endl;
  std::cout << "Your personal command line flashcards :)" << std::endl;

  while (true) {
    std::cout << "Enter the file name: ";
    std::string file_name;
    std::getline(std::cin, file_name);

    std::ifstream file(file_name);

    if (file_name == "quit" || file_name == "q") {
      return 0;
    }

    if (file.is_open()) {
      break;
    } else {
      std::cout << "Try again." << std::endl;
    }
  }

  std::vector<std::pair<std::string, std::string>> questions;

  return 0;
}
