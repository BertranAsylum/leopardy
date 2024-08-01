#include "Participant.h"
#include "StdWStringSerializer.h"

std::ostream &operator<<(std::ostream &s, const Leader &l)
{
    s << l.nickname;
    return s;
}

std::istream &operator>>(std::istream &s, Leader &l)
{
    s >> l.nickname;
    return s;
}

std::ostream &operator<<(std::ostream &s, const Player &p)
{
    s << p.nickname << p.score;
    return s;
}

std::istream &operator>>(std::istream &s, Player &p)
{
    s >> p.nickname >> p.score;
    return s;
}

std::ostream &operator<<(std::ostream &s, const Observer &o)
{
    s << o.nickname;
    return s;
}

std::istream &operator>>(std::istream &s, Observer &o)
{
    s >> o.nickname;
    return s;
}
