# Study_CLI
A command line based flashcard application using the vim keybindings

## Installation and Setup
To get this repo just clone it it wherever you want: 
```bash
git clone https://github.com/AshuHK/Study_CLI.git
cd Study_CLI
```
You can create a `.study` file by using whatever text editor you want (vim, emacs, nano, etc.). You will also have to compile it using the Makefile: 
```bash
# to compile 
make 

# to use Study CLI 
./study_cli
```

## Keybindings
  - Main Controls
    - `h` or `H` - go back one card
    - `j` or `J` - flip the current card
    - `k` or `K` - flip the current card (also)
    - `l` or `L` - go forward one card

  - Misc.
    - `?` - help
    - `q` or `Q` - quit Study CLI
