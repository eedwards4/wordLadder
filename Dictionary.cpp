//
// Created by Ali Kooshesh on 8/22/23.
// Completed by Ethan Edwards on 9/1/2021.
//

#include "Dictionary.hpp"

#include <iostream>
#include <fstream>
#include "Dictionary.hpp"

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

std::vector<std::string> Dictionary::pathFromTo(std::string from, std::string to) {
    startWord = from; targetWord = to;
    std::vector<std::string> neighbors, rVct;
    int iter = 0;
    resetPath();
    ladder.emplace(from, member(from));
    used[member(from)] = true;

    while (!ladder.empty()){
        neighbors = neighborsOf(from);
        iter = 0;
        for (const std::string& i : neighbors){
            if (i == targetWord){
                ladder.emplace(i, member(i));
                printLadder(rVct);
                return rVct; // Return the ladder
            }
            if (!used.at(member(i))){
                ladder.emplace(i, member(i));
                from = i;
                used[member(i)] = true;
                break;
            }
            iter++;
        }
        if (iter == neighbors.size()){
            ladder.pop();
            if (!ladder.empty()){
                from = std::get<0>(ladder.top());
            }
        }
    }
    std::cout << "No ladder for the pair " << from << " and " << to << " exists.\n";
    return {};
}

int Dictionary::member(std::string sTerm) { // u
    int rVal = 0;
    for (const std::string& word : words){
        if (word == sTerm){
            return rVal;
        }
        rVal++;
    }
    return size();
}

int Dictionary::idxOfSuccessorWordFrom(const std::string& word, int fromIdx) { // u
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

std::vector<std::string> Dictionary::neighborsOf(const std::string& word) { // u
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

void Dictionary::printLadder(std::vector<std::string>& rVct) { // i
    if (ladder.empty()){
        for (int i = rVct.size() - 1; i >= 0; i--){
            std::cout << rVct[i] << "\n";
        }
        return;
    }
    rVct.push_back(std::get<0>(ladder.top()));
    ladder.pop();
    printLadder(rVct);
}
