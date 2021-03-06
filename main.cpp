#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// a struct to contain the questions, answers, and a boolean flag
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

  std::size_t pos = 0;
  while (pos < str.size() && std::isspace(str[pos])) {
    ++pos;
  }
  return str.substr(pos);
}

/**
 * Gets the file from the user input
 * @param None
 *
 * @return - an input file stream
 */
std::ifstream get_file() {
  std::ifstream file;
  clear_screen();

  while (true) {
    std::cout << "Enter the .study file name: ";
    std::string file_name;
    std::getline(std::cin, file_name);

    if (file_name == "q") {
      exit(EXIT_SUCCESS);
    }

    file_name = trim(file_name);
    file_name += ".study";

    file.open(file_name);

    if (file.is_open()) {
      break;
    } else {
      std::cout << "File not found. Try again." << std::endl;
    }
  }
  return file;
}

/**
 * Parses the .study file and creates a vector of Items
 * @param file - a reference to a input file stream
 *
 * @return - a vector of Items
 */
std::vector<Item> read_study_file(std::ifstream& file) {
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
    - a or A - go back one card
    - w or W - flip the current card
    - s or S - flip the current card (also)
    - d or D - go forward one card

  - Misc.
    - ? - help
    - q or Q - quit Study CLI
  )";
  std::cout << keybindings << std::endl;
}

int main() {
  std::ifstream file = get_file();
  std::vector<Item> questions = read_study_file(file);

  // create a time based seed for shuffling questions
  unsigned long long seed =
      std::chrono::system_clock::now().time_since_epoch().count();

  // shuffle the questions based on the seed
  std::shuffle(std::begin(questions), std::end(questions),
               std::default_random_engine(seed));

  const int last_index = questions.size() - 1;
  int current = 0;

  show_item(questions, current);
  while (true) {
    std::cout << ">> ";
    std::string input;
    std::getline(std::cin, input);
    input = trim(input);

    if (!input.empty()) {
      switch (input[0]) {
        case 'A':
        case 'a':

          // handles underflow of current
          current--;
          current < 0 ? current = last_index : false;
          show_item(questions, current);
          break;

        case 'S':
        case 's':

          // flips the boolean for the current question
          questions[current].show_answer == false
              ? questions[current].show_answer = true
              : questions[current].show_answer = false;
          show_item(questions, current);
          break;

        case 'W':
        case 'w':

          // flips the boolean for the current question
          questions[current].show_answer == false
              ? questions[current].show_answer = true
              : questions[current].show_answer = false;
          show_item(questions, current);
          break;

        case 'D':
        case 'd':

          // handles overflow of current
          current++;
          current > last_index ? current = 0 : false;
          show_item(questions, current);
          break;

        case 'Q':
        case 'q':
          return 0;

        case '?':
          cout_help();
          break;

        default:
          std::cout << "Try again. You can type '?' for help." << std::endl;
          break;
      }
    } else {
      std::cout << "Try again. You can type '?' for help." << std::endl;
    }

    input.clear();
  }

  return 0;
}
