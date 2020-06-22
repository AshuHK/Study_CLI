#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Item {
  std::string question;
  std::string answer;
};

/**
 * Prints the contents of the questions vector
 * Just used for testing
 */
void print_vector(const std::vector<Item>& questions) {
  for (const Item& item : questions) {
    std::cout << item.question << " : " << item.answer << std::endl;
  }
}

std::vector<Item> read_csv(std::ifstream& file) {
  std::vector<Item> data;

  std::string line, temp;
  while (std::getline(file, temp, '|')) {
    Item new_item;
    new_item.question = temp;

    std::getline(file, temp, '\n');
    new_item.answer = temp;

    data.push_back(new_item);
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

  std::vector<Item> questions = read_csv(file);
  print_vector(questions);

  return 0;
}
