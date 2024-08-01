#pragma once

#include <string>

struct Participant {
    enum class Role {
        Leader,
        Player,
        Observer
    };

    std::wstring nickname;
    virtual Role role() const = 0;
};

struct Leader : Participant {
    Role role() const override { return Role::Leader; }
    friend std::ostream &operator<<(std::ostream &s, const Leader &l);
    friend std::istream &operator>>(std::istream &s, Leader &l);
};

struct Player : Participant {
    int score = 0;

    Role role() const override { return Role::Player; }
    friend std::ostream &operator<<(std::ostream &s, const Player &p);
    friend std::istream &operator>>(std::istream &s, Player &p);
};

struct Observer : Participant {
    Role role() const override { return Role::Observer; }
    friend std::ostream &operator<<(std::ostream &s, const Observer &o);
    friend std::istream &operator>>(std::istream &s, Observer &o);
};
