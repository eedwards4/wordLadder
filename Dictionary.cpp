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
    std::cout << "Creating an instance of Dictionary with input file: " << inputFileName << std::endl;
}

Dictionary::~Dictionary() {
    // close the input stream if it was successfully opened.
    if(dictionaryStream.is_open())
        dictionaryStream.close();
}
