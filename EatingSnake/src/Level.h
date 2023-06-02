#pragma once
#include <Poto.h>
#include <optional>
#include "Snake.h"

class Level
{
public:
    Level(std::pair<uint, uint> levelSize);
    void Reset();

    void TicToc();
    
    bool OnUpdate(Poto::Timestep ts);
    void OnRender();
    void OnImGuiRender();

    bool IsSnakeDead() const
    {
        return m_Snake->IsDead();
    }
    void SetSnakeDirection(Snake::Direction d)
    {
        m_Snake->SetDirection(d);
    }
    auto GetScore() const
    {
        return m_Snake->GetScore();
    }

    std::pair<uint, uint> HeadNextStep() const;
    
private:
    Poto::Scope<Snake> m_Snake;
    std::optional<std::pair<uint, uint>> m_Food;
    float m_LevelTimer = 0.0f;
    std::pair<uint, uint> m_LevelSize;

    static constexpr float INITIAL_FACTOR = 1.5f;
    static constexpr float FACTOR = 1.f;
    float GetFactor() const
    {
        return INITIAL_FACTOR + FACTOR * 0.1f * m_Snake->GetScore();
    }
    float GetNextFactor() const
    {
        return GetFactor() + FACTOR * 0.1f;
    }

    float m_BlockSide = 1.f;
    float m_BlockPadding = 10 / 100.f;
};
