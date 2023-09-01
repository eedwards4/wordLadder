//
// Created by Ali Kooshesh on 8/22/23.
// Completed by Emily Hernandez and Ethan Edwards on 10/1/2021.
//

#include "Dictionary.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Dictionary.hpp"

// ------------------------------------------------------Management-----------------------------------------------------
Dictionary::Dictionary(std::string inputFileName) {
    // open inputFileName and store its contents, which is a collection of
    // words, one per line, in vector, "words".
    std::string word;
    std::ifstream inFile(inputFileName);
    while (inFile.is_open() && !inFile.eof()){
        inFile >> word;
        words.push_back(word);
        used.push_back(false); // Prepopulate used vector with false values
    }
    inFile.close();
    std::cout << "Creating an instance of Dictionary with input file: " << inputFileName << std::endl;
    printDictionary();
}

Dictionary::~Dictionary() {
    // close the input stream if it was successfully opened.
    if(dictionaryStream.is_open())
        dictionaryStream.close();
}

// --------------------------------------------------------External-----------------------------------------------------
// Complex
std::vector<std::string> Dictionary::pathFromTo(std::string from, std::string to) {
    string currWord = startWord = from; targetWord = to;
    vector<string> neighbors;
    int tracker = 0;
    // Reset used vector
    resetPath();
    // Push start word onto stack
    ladder.push(make_tuple(currWord, member(currWord)));
    // Mark start word as used
    used[member(currWord)] = true;

    while (!ladder.empty()){
        neighbors = neighborsOf(currWord);
        tracker = 0;
        for (string i : neighbors){
            if (i == targetWord){
                ladder.push(make_tuple(i, member(i)));
                printLadder();
                return {}; // Return blank vector to remain in line with I/O reqs
            }
            if (!used.at(member(i))){
                ladder.push(make_tuple(i, member(i)));
                currWord = i;
                used[member(i)] = true;
                break;
            }
            tracker++;
        }
        if (tracker == neighbors.size()){
            ladder.pop();
            if (!ladder.empty()){
                currWord = get<0>(ladder.top());
            }
        }
    }
    cout << "No ladder for the pair " << from << " and " << to << " exists." << endl;
    return {}; // Return blank vector to remain in line with I/O reqs
}

// Simple
int Dictionary::member(std::string sTerm) { // u
    int rVal = 0;
    for (std::string word : words){
        if (word == sTerm){
            return rVal;
        }
        rVal++;
    }
    return size();
}

// --------------------------------------------------------Internal-----------------------------------------------------
// Complex
int Dictionary::idxOfSuccessorWordFrom(std::string word, int fromIdx) { // u
    int idx = fromIdx;
    while (idx < words.size()){
        if (positionalDiff(word, words[idx]) == 1){
            return idx;
        }
        idx++;
    }
    return words.size();
}

// Simple
void Dictionary::printDictionary() { // i
    // print the words in the dictionary.
    for (std::string i : words){
        std::cout << i << "\n";
    }
}

int Dictionary::positionalDiff(std::string word1, std::string word2) { // u
    int rVal = 0;
    for (int i = 0; i < word1.length(); i++){
        if (word1[i] != word2[i]){
            rVal += 1;
        }
    }
    return rVal;
}

std::vector<std::string> Dictionary::neighborsOf(std::string word) { // u
    std::vector<std::string> rVct;
    for (std::string i : words){
        if (positionalDiff(word, i) == 1){
            rVct.push_back(i);
        }
    }
    return rVct;
}

void Dictionary::resetPath() { // u
    for (auto && i : used){
        i = false;
    }
}

void Dictionary::printLadder() { // i
    vector<string> rVct;
    while(!ladder.empty()){
        rVct.push_back(get<0>(ladder.top()));
        ladder.pop();
    }
    for (int i = rVct.size() - 1; i >= 0; i--){
        cout << rVct[i] << "\n";
    }
}
