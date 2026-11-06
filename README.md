# Boogle Trie

A small command-line slang-word dictionary made for a university Data Structures course (Semester 2). The project demonstrates how a **trie (prefix tree)** can store and search words.

## Features

The menu lets you:

1. Add a slang word and its description. If the word already exists, its description is updated.
2. Search for a word and display its description.
3. List words that start with a given prefix.
4. List all words in alphabetical order.
5. Exit the program.

Words are converted to lowercase when added or searched. The program expects words made of lowercase English letters after conversion, with no spaces. Descriptions must contain at least three words.

## Data structure

Each trie node has 26 child pointers, one for each letter `a` through `z`. A node also stores a description and a flag indicating whether the path to that node forms a complete word. This lets the program follow letters to find a word or prefix, and traverse the tree to list matching words.

## Build and run

The source is `Boogle Trie.cpp`. It uses C-style I/O and memory management, but includes C++ features such as `bool` and `true`, so compile it as C++ with a compiler that supports the source's syntax. For example, with g++:

```sh
g++ -std=c++11 "Boogle Trie.cpp" -o boogle-trie
./boogle-trie
```

On Windows, run the resulting `boogle-trie.exe` from Command Prompt or PowerShell. The screen-clearing command in the source uses `cls`, so the interface is intended for Windows terminals.

## Notes

The dictionary is kept in memory and starts empty each time the program runs; words are not saved between runs. This is an educational assignment project rather than a production dictionary.
