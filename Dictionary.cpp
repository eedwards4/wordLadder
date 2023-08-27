//
// Created by Ali Kooshesh on 8/22/23.
// Completed by Emily Hernandez and Ethan Edwards on 10/1/2021.
//

#include "Dictionary.hpp"

#include <iostream>
#include <fstream>
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
    std::vector<std::string> rVect;
    std::string currWord;
    int currIdx = 0;

    while (positionalDiff(currWord, targetWord) != 1){ // Loop until we find a successor word
        while (currIdx != size()){ // Loop through all words in dictionary looking for an unused match
            if (positionalDiff(currWord, words[currIdx]) == 1 && !used[currIdx]){
                ladder.push(std::make_tuple(words[currIdx], currIdx));
                used[currIdx] = true;
                currWord = words[currIdx];
                currIdx = 0;
                break;
            }
            currIdx++;
        }
        if (currIdx == size()){
            currWord = backtrack(currWord);
        }
    }
    return rVect;
}

// Simple
int Dictionary::member(std::string sTerm) {
    int rVal = 0;
    for (std::string word : words){
        if (word == sTerm){
            return rVal;
        }
    }
    return size();
}

// --------------------------------------------------------Internal-----------------------------------------------------
// Complex
int Dictionary::idxOfSuccessorWordFrom(std::string word, int fromIdx) {
    int idx = fromIdx;
    while (idx < words.size()){
        if (positionalDiff(word, words[idx]) == 1){
            return idx;
        }
        idx++;
    }
    return words.size();
}

std::string Dictionary::backtrack(std::string currWord) {
    int currIdx = member(currWord);
    // Flag the word as used
    used[currIdx] = true;
    return words[currIdx - 1];
}
// Simple
void Dictionary::printDictionary() {
    // print the words in the dictionary.
    for (std::string i : words){
        std::cout << i << "\n";
    }
}

int Dictionary::positionalDiff(std::string word1, std::string word2) {
    int rVal = 0;
    for (int i = 0; i < word1.length(); i++){
        if (word1[i] != word2[i]){
            rVal += 1;
        }
    }
    return rVal;
}

std::vector<std::string> Dictionary::neighborsOf(std::string word) {
    std::vector<std::string> rVct;
    for (std::string i : words){
        if (positionalDiff(word, i) == 1){
            rVct.push_back(i);
        }
    }
    return rVct;
}

void Dictionary::resetPath() {
    for (bool i : used){
        i = false;
    }
}

void Dictionary::printLadder() {
    while(!ladder.empty()){
        std::cout << std::get<0>(ladder.top()) << ", " << std::get<1>(ladder.top()) << "\n";
        ladder.pop();
    }
}
