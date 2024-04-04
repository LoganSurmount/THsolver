//
// Created by bytedance on 7.6.21.
// ^ lol wild if true. Those guys build everything!
// Skrrrrt... modernizing...
//
#ifndef COMMANDLINETOOL_H
#define COMMANDLINETOOL_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "PokerSolver.h" // Assuming PokerSolver is a class you have defined

class CommandLineTool {
public:
    explicit CommandLineTool(const std::string& mode, const std::string& resource_dir);

    void startWorking();
    void execFromFile(const std::string& input_file);

private:
    std::string resource_dir;
    PokerSolver ps;
    // Other member variables...

    void processCommand(const std::string& input);
    static void split(const std::string& s, char delimiter, std::vector<std::string>& elements);
};

#endif // COMMANDLINETOOL_H

// down with the .cc?pp yea you know me

#include "CommandLineTool.h"

CommandLineTool::CommandLineTool(const std::string& mode, const std::string& resource_dir) : resource_dir(resource_dir) {
    std::string suits = "c,d,h,s";
    std::string ranks;
    std::string compairer_file, compairer_file_bin;
    int lines;

    if (mode == "holdem") {
        ranks = "2,3,4,5,6,7,8,9,T,J,Q,K,A";
        compairer_file = resource_dir + "/compairer/card5_dic_sorted.txt";
        compairer_file_bin = resource_dir + "/compairer/card5_dic_zipped.bin";
        lines = 2598960; // Assuming this is the correct number of lines
    } else if (mode == "shortdeck") {
        ranks = "6,7,8,9,T,J,Q,K,A";
        compairer_file = resource_dir + "/compairer/card5_dic_sorted_shortdeck.txt";
        compairer_file_bin = resource_dir + "/compairer/card5_dic_zipped_shortdeck.bin";
        lines = 376992; // Assuming this is the correct number of lines
    } else {
        throw std::runtime_error("Mode not recognized: " + mode);
    }

    // Initialize PokerSolver with the parsed configuration
    this->ps = PokerSolver(ranks, suits, compairer_file, lines, compairer_file_bin);
    // Further initialization...
}

void CommandLineTool::startWorking() {
    std::string input_line;
    while (std::getline(std::cin, input_line)) {
        processCommand(input_line);
    }
}

void CommandLineTool::execFromFile(const std::string& input_file) {
    std::ifstream infile(input_file);
    std::string input_line;
    while (std::getline(infile, input_line)) {
        processCommand(input_line);
    }
}

void CommandLineTool::split(const std::string& s, char delimiter, std::vector<std::string>& elements) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        elements.push_back(item);
    }
}

void CommandLineTool::processCommand(const std::string& input) {
    std::vector<std::string> contents;
    split(input, ' ', contents);

    if (contents.empty()) {
        std::cout << "Empty command received." << std::endl;
        return;
    }

    const std::string& command = contents[0];
    std::string paramstr = contents.size() > 1 ? contents[1] : "";

    // Process commands...
    // Example:
    if (command == "set_pot") {
        // Handle set_pot command
    } else {
        std::cout << "Command not recognized: " << command << std::endl;
    }
    // Continue with other commands...
}
