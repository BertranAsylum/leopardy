#include "GameSet.h"
#include "serializers/StdWStringSerializer.h"
#include "serializers/StdVectorSerializer.h"

std::ostream &operator<<(std::ostream &s, const GameSet::Card &c)
{
    s << bytes(c.used) << bytes(c.price) << c.question << c.answer;
    return s;
}

std::istream &operator>>(std::istream &s, GameSet::Card &c)
{
    s >> bytes(c.used) >> bytes(c.price) >> c.question >> c.answer;
    return s;
}

std::ostream &operator<<(std::ostream &s, const GameSet::Category &c)
{
    s << c.name << c.cards;
    return s;
}

std::istream &operator>>(std::istream &s, GameSet::Category &c)
{
    s >> c.name >> c.cards;
    return s;
}

std::ostream &operator<<(std::ostream &s, const GameSet::Round &r)
{
    s << r.categories;
    return s;
}

std::istream &operator>>(std::istream &s, GameSet::Round &r)
{
    s >> r.categories;
    return s;
}

std::ostream &operator<<(std::ostream &s, const GameSet &gs)
{
    s << gs.rounds;
    return s;
}

std::istream &operator>>(std::istream &s, GameSet &gs)
{
    s >> gs.rounds;
    return s;
}
