#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * Prints the contents of the questions vector 
 * Just used for testing 
 */
void print_vector(
    const std::vector<std::vector<std::string>>& questions) {
}

/**
 * Parses the csv file and places all of the questions and answers into a 
 * vector of pairs of strings 
 * @param file - a reference to an input file 
 * 
 * @return - a vector of pairs of strings of questions and answers
 */
std::vector<std::vector<std::string>> read_csv(std::ifstream& file) {
  std::vector<std::vector<std::string>> data;

  std::string line; 
  while(std::getline(file, line, '|')) {
    data.push_back({line});
  }

  file.close();
  return data;
}

int main() {
  std::cout << "Welcome to Study CLI" << std::endl;
  std::cout << "Your personal command line flashcards :)" << std::endl;

  std::ifstream file;
  while (true) {
    std::cout << "Enter the file name: ";
    std::string file_name;
    std::getline(std::cin, file_name);

    file.open(file_name);

    if (file_name == "quit" || file_name == "q") {
      return 0;
    }

    if (file.is_open()) {
      break;
    } else {
      std::cout << "Try again." << std::endl;
    }
  }

  std::vector<std::vector<std::string>> questions = read_csv(file);
  print_vector(questions);

  return 0;
}
