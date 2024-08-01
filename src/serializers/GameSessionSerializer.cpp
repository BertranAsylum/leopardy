#include "GameSession.h"
#include "StdVectorSerializer.h"

std::ostream &operator<<(std::ostream &s, const GameSession::State &st)
{
    s << bytes(st.currentStage) << bytes(st.currentRound) << bytes(st.questionCategoryNum) << bytes(st.questionPriceNum)
        << bytes(st.playerNum);
    return s;
}

std::istream &operator>>(std::istream &s, GameSession::State &st)
{
    s >> bytes(st.currentStage) >> bytes(st.currentRound) >> bytes(st.questionCategoryNum) >> bytes(st.questionPriceNum)
        >> bytes(st.playerNum);
    return s;
}

std::ostream &operator<<(std::ostream &s, const GameSession &ss)
{
    s << ss.m_gameSet << ss.m_leader << ss.m_players << ss.m_observers << ss.m_state;
    return s;
}

std::istream &operator>>(std::istream &s, GameSession &ss)
{
    s >> ss.m_gameSet >> ss.m_leader >> ss.m_players >> ss.m_observers >> ss.m_state;
    return s;
}
