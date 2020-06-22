#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// a struct to contain the questions and answers
struct Item {
  std::string question;
  std::string answer;
  bool show_answer = false;
};

/**
 * Clears the screen and prints the splash text
 * @param None
 *
 * @return - None
 */
void clear_screen() {
  std::cout << std::string(100, '\n');
  // make splash text
}

/**
 * Prints the contents of the questions vector
 * Just used for testing
 */
void print_vector(const std::vector<Item>& questions) {
  for (const Item& item : questions) {
    std::cout << item.question << "  " << item.answer << std::endl;
  }
}

/**
 * Parses the .study file and creates a vector of Items
 * @param file - a reference to a input file stream
 *
 * @return - a vector of Items
 */
std::vector<Item> read_csv(std::ifstream& file) {
  std::vector<Item> data;

  std::string temp;
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

void show_item(const std::vector<Item>& questions, const int& current) {
  if (questions[current].show_answer == false) {
    std::cout << questions[current].question << std::endl;
  } else {
    std::cout << questions[current].answer << std::endl;
  }
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
  const int item_count = questions.size();
  int current = 0;

  while (true) {
    show_item(questions, current);

    std::cout << ">> ";
    std::string input;
    std::getline(std::cin, input);

    if (!input.empty()) {
      switch (input[0]) {
        // go back one item
        case 'h':
          break;

        // show opposite side of the item
        case 'j':
          break;

        // show opposite sode of the item
        case 'k':
          break;

        // go forward one item
        case 'l':
          break;

        case 'q':
          return 0;

        case '?':
          std::cout << "This should print the help" << std::endl;
          break;

        default:
          std::cout << "Try again. You can type '?' for help" << std::endl;
          break;
      }
    } else {
      std::cout << "Try again. You can type '?' for help" << std::endl;
    }

    input.clear();
  }

  return 0;
}
