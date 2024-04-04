//
// Created by Xuefeng Huang on 2020/1/28.
//
// Revised by Logan on 4/4/2024
// Skrrrrt
#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>
#include <stdexcept>

class Card {
public:
    Card(const std::string& card = "empty", int card_num_in_deck = -1);

    bool isEmpty() const;
    std::string getCard() const;
    int getCardInt() const;
    int getNumberInDeckInt() const;

    static int card2int(const Card& card);
    static int strCard2int(const std::string& card);
    static std::string intCard2Str(int card);
    static uint64_t boardCards2long(const std::vector<std::string>& cards);
    static uint64_t boardCard2long(const Card& card);
    static uint64_t boardCards2long(const std::vector<Card>& cards);
    static std::string boardCards2html(const std::vector<Card>& cards);
    static uint64_t boardInt2long(int board);
    static uint64_t boardInts2long(const std::vector<int>& board);
    static std::vector<int> long2board(uint64_t board_long);
    static std::vector<Card> long2boardCards(uint64_t board_long);

    std::string toString() const;
    std::string toFormattedString() const;

private:
    std::string card;
    int card_int;
    int card_number_in_deck;

    static std::string suitToString(int suit);
    static std::string rankToString(int rank);
    static int rankToInt(char rank);
    static int suitToInt(char suit);

    static constexpr int NUM_CARDS_IN_DECK = 52;
    static constexpr int NUM_SUITS = 4;
};

#endif // CARD_H

// fixing error messages (i don't speak mandarin!)

#include "Card.h"
#include <sstream>
#include <bitset>

Card::Card(const std::string& card, int card_num_in_deck) : card(card), card_int(strCard2int(card)), card_number_in_deck(card_num_in_deck) {}

bool Card::isEmpty() const {
    return card == "empty";
}

std::string Card::getCard() const {
    return card;
}

int Card::getCardInt() const {
    return card_int;
}

int Card::getNumberInDeckInt() const {
    if (card_number_in_deck == -1) {
        throw std::runtime_error("Card number in deck is uninitialized.");
    }
    return card_number_in_deck;
}

int Card::card2int(const Card& card) {
    return strCard2int(card.getCard());
}

int Card::strCard2int(const std::string& card) {
    if (card.length() != 2) {
        throw std::runtime_error("Invalid card format. Expected format: <Rank><Suit>.");
    }

    char rank = card.at(0);
    char suit = card.at(1);

    return (rankToInt(rank) - 2) * NUM_SUITS + suitToInt(suit);
}

std::string Card::intCard2Str(int card) {
    int rank = card / NUM_SUITS + 2;
    int suit = card % NUM_SUITS;
    return rankToString(rank) + suitToString(suit);
}

uint64_t Card::boardCards2long(const std::vector<std::string>& cards) {
    uint64_t board = 0;
    for (const auto& card_str : cards) {
        board |= 1ULL << strCard2int(card_str);
    }
    return board;
}

uint64_t Card::boardCard2long(const Card& card) {
    return 1ULL << card.getCardInt();
}

uint64_t Card::boardCards2long(const std::vector<Card>& cards) {
    uint64_t board = 0;
    for (const auto& card : cards) {
        board |= 1ULL << card.getCardInt();
    }
    return board;
}

std::string Card::boardCards2html(const std::vector<Card>& cards) {
    std::stringstream html;
    for (const auto& card : cards) {
        if (!card.isEmpty()) {
            html << card.toFormattedString();
        }
    }
    return html.str();
}

// Other implementations remain similar, with optimizations and error handling revised as needed.
//Skrrrrrrt

