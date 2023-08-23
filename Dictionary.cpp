//
// Created by Ali Kooshesh on 8/22/23.
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

void Dictionary::printDictionary() {
    // print the words in the dictionary.
    for (std::string i : words){
        std::cout << i << "\n";
    }
}

int Dictionary::member(std::string sTerm) {
    int rVal = 0;
    for (std::string word : words){
        if (word == sTerm){
            return rVal;
        }
    }
    return size();
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
        if (positionalDiff(word, i) <= 1){
            rVct.push_back(i);
        }
    }
    return rVct;
}
