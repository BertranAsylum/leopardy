#include "GameSetLoader.h"

GameSet GameSetLoader::load()
{
    GameSet gameSet;
    for (int k = 0; k < 2; ++k) {
        GameSet::Round round;
        for (int j = 1; j < 7; ++j) {
            GameSet::Category category;
            category.name = L"Cat " + std::to_wstring(j + 10 * k);
            for (int i = 1; i < 6; ++i) {
                GameSet::Card c;
                c.price = (k + 1) * i * 100;
                c.question = L"Question from " + category.name + L" question " + std::to_wstring(c.price) + L"?";
                category.cards.push_back(c);
            }
            round.categories.push_back(category);
        }
        gameSet.rounds.push_back(round);
    }

    return gameSet;
}
