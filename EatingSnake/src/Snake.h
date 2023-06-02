#pragma once
#include <list>
#include "Prologue.h"

class Snake
{
public:
    Snake(uint worldWidth, uint worldHeight);
    void MoveByStep();
    bool IsOutOfWorld(const std::pair<uint, uint>& pos) const;
    bool IsCrash(const std::pair<uint, uint>& pos) const;

    const auto& GetSnakeChain() const
    {
        return m_SnakeChain;
    }
    auto IsDead() const {
        return m_bDead;
    }
    auto GetScore() const
    {
        return m_Score;
    }

    void IncScore()
    {
        ++m_Score;
    }
    
    enum class Direction
    {
        Left,
        Up,
        Down,
        Right,
    };
    void SetDirection(Direction d);

    float m_Age;
private:
    uint m_Score;
    std::list<std::pair<uint, uint>> m_SnakeChain;
    bool m_bDead;
    uint m_WorldWidth, m_WorldHeight;
    Direction m_Direction;
};
