#pragma once

#include <vector>
#include <string>

struct GameSet {
    struct Card {
        bool used = false;
        int price = 0;
        std::wstring question;
        std::wstring answer;

        friend std::ostream &operator<<(std::ostream &s, const Card &c);
        friend std::istream &operator>>(std::istream &s, Card &c);
    };

    struct Category {
        std::wstring name;
        std::vector<Card> cards;

        friend std::ostream &operator<<(std::ostream &s, const Category &c);
        friend std::istream &operator>>(std::istream &s, Category &c);
    };

    struct Round {
        std::vector<Category> categories;
        bool hasUnusedCards() const;

        friend std::ostream &operator<<(std::ostream &s, const Round &r);
        friend std::istream &operator>>(std::istream &s, Round &r);
    };

    std::vector<Round> rounds;

    friend std::ostream &operator<<(std::ostream &s, const GameSet &gs);
    friend std::istream &operator>>(std::istream &s, GameSet &gs);
};

inline bool GameSet::Round::hasUnusedCards() const
{
    for (const auto &category : categories) {
        for (const auto &card : category.cards) {
            if (!card.used) {
                return true;
            }
        }
    }
    return false;
}
