#include "Snake.h"
#include <cassert>
#include <algorithm>

#include <Poto.h> 

Snake::Snake(uint worldWidth, uint worldHeight)
{
    m_WorldWidth = worldWidth;
    m_WorldHeight = worldHeight;

    PT_ASSERT(worldWidth & 1, "Snake world width is not an odd number.");
    PT_ASSERT(worldWidth > 10, "Snake world width is too small.");
    PT_ASSERT(worldHeight > 10, "Snake world height is too small.");

    auto centerC = worldWidth / 2;
    auto centerR = worldHeight / 2;

    m_SnakeChain = {
        {centerC + 1, centerR},
        {centerC + 0, centerR},
        {centerC - 1, centerR},
    };
    m_Direction = Direction::Right;
    
    m_bDead = false;
    m_Score = 0u;
    m_Age = 0u;
}

void Snake::MoveByStep()
{
    if (m_bDead) return;
    
    m_SnakeChain.pop_back();
    std::pair<uint, uint> newHead = m_SnakeChain.front();
    switch (m_Direction)
    {
    case Direction::Left:
        --newHead.first;
        break;
    case Direction::Right:
        ++newHead.first;
        break;
    case Direction::Up:
        ++newHead.second;
        break;
    case Direction::Down:
        --newHead.second;
        break;
    }

    if (IsCrash(newHead) || IsOutOfWorld(newHead))
    {
        m_bDead = true;
    }

    m_SnakeChain.push_front(newHead);
    ++m_Age;
}

bool Snake::IsOutOfWorld(const std::pair<uint, uint>& pos) const
{
    auto x = pos.first, y = pos.second;
    return x < 0 || x >= m_WorldWidth || y < 0 || y >= m_WorldHeight;
}

bool Snake::IsCrash(const std::pair<uint, uint>& pos) const
{
    return std::ranges::find(m_SnakeChain, pos) != m_SnakeChain.cend();
}

void Snake::SetDirection(Direction d)
{
    if (3 - (int) m_Direction == (int) d)
    {
        return;
    }
    m_Direction = d;
}
