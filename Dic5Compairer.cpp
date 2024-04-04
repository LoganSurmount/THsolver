//
// Created by Xuefeng Huang on 2020/1/29.
//
// [probably] wrecked by Logan on 4/4/2024
// Skrrrrt
//

#ifndef DIC5COMPAIRER_H
#define DIC5COMPAIRER_H

#include <unordered_map>
#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "Card.h" 

class Dic5Compairer {
public:
    Dic5Compairer(const std::string& dic_dir, int lines, const std::string& dic_dir_bin);
    enum class CompairResult { LARGER, SMALLER, EQUAL };
    CompairResult compairRanks(int rank_former, int rank_latter);
    CompairResult compair(const std::vector<Card>& private_former, const std::vector<Card>& private_latter, const std::vector<Card>& public_board);
    CompairResult compair(const std::vector<int>& private_former, const std::vector<int>& private_latter, const std::vector<int>& public_board);
    int getRank(const std::vector<Card>& cards);
    int getRank(const std::vector<int>& cards);
    int getRank(uint64_t private_hand, uint64_t public_board);

private:
    std::unordered_map<uint64_t, int> flush_map;
    std::unordered_map<uint64_t, int> other_map;
    bool load(const std::string& file_path);
    bool save(const std::string& file_path);
    int operator[](uint64_t hash);
    bool check(const std::unordered_map<uint64_t, int>& strength_map);
    static uint64_t ranksHash(uint64_t cards_hash);
    static bool isFlush(uint64_t hash);
};

#endif // DIC5COMPAIRER_H

#include "Dic5Compairer.h"
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <limits>

constexpr uint64_t SUIT_0_MASK = 0x1111111111111;
constexpr uint64_t SUIT_1_MASK = 0x2222222222222;
constexpr uint64_t SUIT_2_MASK = 0x4444444444444;
constexpr uint64_t SUIT_3_MASK = 0x8888888888888;
constexpr uint64_t BIT_SUM_0 = 0x5555555555555;
constexpr uint64_t BIT_SUM_1 = 0x3333333333333;

uint64_t Dic5Compairer::ranksHash(uint64_t cards_hash) {
    cards_hash = (cards_hash & BIT_SUM_0) + ((cards_hash >> 1) & BIT_SUM_0);
    cards_hash = (cards_hash & BIT_SUM_1) + ((cards_hash >> 2) & BIT_SUM_1);
    return cards_hash;
}

bool Dic5Compairer::isFlush(uint64_t hash) {
    int cnt = (hash & SUIT_0_MASK) != 0;
    cnt += (hash & SUIT_1_MASK) != 0;
    if (cnt > 1) return false;
    cnt += (hash & SUIT_2_MASK) != 0;
    if (cnt > 1) return false;
    cnt += (hash & SUIT_3_MASK) != 0;
    return cnt <= 1;
}

// Constructor and other member functions...

bool Dic5Compairer::load(const std::string& file_path) {
    QFile file(QString::fromStdString(file_path));
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::runtime_error("Unable to load comparer file: " + file_path);
    }
    // Load logic...
    return true;
}

bool Dic5Compairer::save(const std::string& file_path) {
    std::ofstream file(file_path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file for saving: " + file_path);
    }
    // Save logic...
    return true;
}

int Dic5Compairer::operator[](uint64_t hash) {
    // Access logic...
    return 0; // Placeholder return
}

bool Dic5Compairer::check(const std::unordered_map<uint64_t, int>& strength_map) {
    // Check logic...
    return true; // Placeholder return
}

// Implementation of other member functions...

// skrrt

#include "Dic5Compairer.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <QString>
#include <QTextStream>

Dic5Compairer::Dic5Compairer(const std::string& dic_dir, int lines, const std::string& dic_dir_bin) {
    if (!load(dic_dir_bin)) {
        // Load from text file and convert if binary file is not available
        QFile infile(QString::fromStdString(dic_dir));
        if (!infile.open(QIODevice::ReadOnly)) {
            throw std::runtime_error("Unable to load comparer file: " + dic_dir);
        }
        QTextStream in(&infile);
        std::unordered_map<uint64_t, int> strength_map;
        while (!in.atEnd()) {
            QString line = in.readLine();
            auto lineParts = line.split(',');
            if (lineParts.size() != 2) {
                throw std::runtime_error("Invalid line format in comparer file.");
            }
            uint64_t cards_hash = Card::boardCards2long(lineParts[0].toStdString());
            int rank = lineParts[1].toInt();
            strength_map[cards_hash] = rank;
        }
        convert(strength_map);
        if (!check(strength_map)) {
            throw std::runtime_error("Consistency check failed after loading comparer data.");
        }
        // Optionally save the loaded data to a binary file for faster future loads
        // save(dic_dir_bin);
    }
}

Dic5Compairer::CompairResult Dic5Compairer::compair(const std::vector<Card>& private_former, const std::vector<Card>& private_latter, const std::vector<Card>& public_board) {
    if (private_former.size() != 2 || private_latter.size() != 2 || public_board.size() != 5) {
        throw std::runtime_error("Invalid card count for comparison.");
    }
    std::vector<Card> former_cards = private_former;
    former_cards.insert(former_cards.end(), public_board.begin(), public_board.end());
    int rank_former = getRank(former_cards);

    std::vector<Card> latter_cards = private_latter;
    latter_cards.insert(latter_cards.end(), public_board.begin(), public_board.end());
    int rank_latter = getRank(latter_cards);

    return compairRanks(rank_former, rank_latter);
}

Dic5Compairer::CompairResult Dic5Compairer::compair(const std::vector<int>& private_former, const std::vector<int>& private_latter, const std::vector<int>& public_board) {
    if (private_former.size() != 2 || private_latter.size() != 2 || public_board.size() != 5) {
        throw std::runtime_error("Invalid card count for comparison.");
    }
    std::vector<int> former_cards = private_former;
    former_cards.insert(former_cards.end(), public_board.begin(), public_board.end());
    int rank_former = getRank(former_cards);

    std::vector<int> latter_cards = private_latter;
    latter_cards.insert(latter_cards.end(), public_board.begin(), public_board.end());
    int rank_latter = getRank(latter_cards);

    return compairRanks(rank_former, rank_latter);
}

int Dic5Compairer::getRank(const std::vector<Card>& cards) {
    std::vector<int> cardInts;
    std::transform(cards.begin(), cards.end(), std::back_inserter(cardInts),
                   [](const Card& card) { return card.getCardInt(); });
    return getRank(cardInts);
}

int Dic5Compairer::getRank(const std::vector<int>& cards) {
    if (cards.size() != 7) {
        throw std::runtime_error("Invalid number of cards for rank calculation.");
    }
    std::vector<int> combination;
    int min_rank = std::numeric_limits<int>::max();
    // Generate all 5-card combinations from the 7 cards and find the minimum rank
    // Assuming Combinations is a utility class you have for generating combinations
    Combinations<int> combinations(cards, 5);
    for (const auto& combo : combinations) {
        uint64_t combo_hash = Card::boardInts2long(combo);
        int rank = (*this)[combo_hash];
        min_rank = std::min(min_rank, rank);
    }
    return min_rank;
}

Dic5Compairer::CompairResult Dic5Compairer::compairRanks(int rank_former, int rank_latter) {
    if (rank_former < rank_latter) {
        return CompairResult::LARGER;
    } else if (rank_former > rank_latter) {
        return CompairResult::SMALLER;
    } else {
        return CompairResult::EQUAL;
    }
}

// prob just wrecked this


