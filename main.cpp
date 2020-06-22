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

  std::string intro = R"(
 ________  _________  ___  ___  ________      ___    ___      ________  ___       ___
|\   ____\|\___   ___\\  \|\  \|\   ___ \    |\  \  /  /|    |\   ____\|\  \     |\  \
\ \  \___|\|___ \  \_\ \  \\\  \ \  \_|\ \   \ \  \/  / /    \ \  \___|\ \  \    \ \  \
 \ \_____  \   \ \  \ \ \  \\\  \ \  \ \\ \   \ \    / /      \ \  \    \ \  \    \ \  \
  \|____|\  \   \ \  \ \ \  \\\  \ \  \_\\ \   \/  /  /        \ \  \____\ \  \____\ \  \
    ____\_\  \   \ \__\ \ \_______\ \_______\__/  / /           \ \_______\ \_______\ \__\
   |\_________\   \|__|  \|_______|\|_______|\___/ /             \|_______|\|_______|\|__|
   \|_________|                             \|___|/

  )";
  std::cout << intro << std::endl;
}

/**
 * Trims whitespace and returns the new string
 * @param str - the string to be trimmed
 *
 * @return - the trimmed string
 */
std::string trim(std::string str) {
  while (!str.empty() && std::isspace(str.back())) {
    str.pop_back();
  }

  size_t pos = 0;
  while (pos < str.size() && std::isspace(str[pos])) {
    ++pos;
  }
  return str.substr(pos);
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
    new_item.question = trim(temp);

    std::getline(file, temp, '\n');
    new_item.answer = trim(temp);

    data.push_back(new_item);
  }

  file.close();
  return data;
}

/**
 * Outputs the item at the current index
 * @param questions - a constant reference to a vector of Items
 * @param current - a constant reference to an int for the index in questions
 *                  to output
 *
 * @return - None
 */
void show_item(const std::vector<Item>& questions, const int& current) {
  clear_screen();
  if (questions[current].show_answer == false) {
    std::cout << questions[current].question << std::endl;
  } else {
    std::cout << questions[current].answer << std::endl;
  }
}

/**
 * Outputs the keybindings
 * @param None
 *
 * @return - None
 */
void cout_help() {
  clear_screen();
  std::string keybindings = R"(
Keybindings:
  - Main Controls
    - h/H - go back one card
    - j/J - flip the current card
    - k/K - flip the current card (also)
    - l/L - go forward one card

  - Misc.
    - ? - help
    - q/Q - quit Study CLI
  )";
  std::cout << keybindings << std::endl;
}

int main() {
  std::ifstream file;
  clear_screen();

  while (true) {
    std::cout << "Enter the file name: ";
    std::string file_name;
    std::getline(std::cin, file_name);

    if (file_name == "q") {
      return 0;
    }

    file_name = trim(file_name);
    file_name += ".study";

    file.open(file_name);

    if (file.is_open()) {
      break;
    } else {
      std::cout << "Try again." << std::endl;
    }
  }

  std::vector<Item> questions = read_csv(file);
  const int item_count = questions.size();
  int current = 0;

  show_item(questions, current);
  while (true) {
    std::cout << ">> ";
    std::string input;
    std::getline(std::cin, input);

    if (!input.empty()) {
      switch (input[0]) {
        // go back one item
        case 'H':
        case 'h':
          break;

        case 'J':
        case 'j':
          if (questions[current].show_answer == false) {
            questions[current].show_answer = true;
          } else {
            questions[current].show_answer = false;
          }
          show_item(questions, current);
          break;

        case 'K':
        case 'k':
          if (questions[current].show_answer == false) {
            questions[current].show_answer = true;
          } else {
            questions[current].show_answer = false;
          }
          show_item(questions, current);
          break;

        // go forward one item
        case 'L':
        case 'l':
          break;

        case 'Q':
        case 'q':
          return 0;

        case '?':
          cout_help();
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
