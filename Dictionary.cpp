//
// Created by Ali Kooshesh on 8/22/23.
// Completed by Emily Hernandez and Ethan Edwards on 10/1/2021.
//

#include "Dictionary.hpp"

#include <iostream>
#include <fstream>
#include "Dictionary.hpp"

using namespace std;

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
    std::vector<std::string> rVect;
    std::string currWord = from; startWord = from;
    targetWord = to;
    int currIdx = 0;
    cout << "Entered pathFromTo\n";
    while (positionalDiff(currWord, targetWord) != 0){ // Loop until we find a successor word
        cout << "Entered iteration of while loop on word: " << currWord << "\n";
        int tracker = 0;
        for (int i = 0; i < words.size(); i++){
            cout << "Comparing" << currWord << " and " << words[i] << "\n";
            if (positionalDiff(currWord, words[i]) == 1 && used[i] == false){
                cout << "Found a successor word: " << words[i] << "\n";
                ladder.push(std::make_tuple(currWord, i));
                currWord = words[i];
                currIdx = i;
                used[i] = true;
                break;
            }
        }
        if (tracker == size()){
            cout << "No successor word found. Backtracking...\n";
            currWord = ladder.top();
        }
        cout << "Current word is: " << currWord << "\n";
    }
    printLadder();
    return rVect;
}

// Simple
int Dictionary::member(std::string sTerm) { // u
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

std::string Dictionary::backtrack(std::string currWord) { // i

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
    for (bool i : used){
        i = false;
    }
}

void Dictionary::printLadder() { // i
    while(!ladder.empty()){
        std::cout << std::get<0>(ladder.top()) << ", " << std::get<1>(ladder.top()) << "\n";
        ladder.pop();
    }
}
