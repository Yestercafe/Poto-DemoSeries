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

    std::pair<uint, uint> HeadNextStep() const;
    
private:
    Poto::Scope<Snake> m_Snake;
    std::optional<std::pair<uint, uint>> m_Food;
    float m_LevelTimer = 0.0f;
    std::pair<uint, uint> m_LevelSize;
    
    static constexpr float FACTOR = 3.f;

    float m_BlockSide = 1.f;
    float m_BlockPadding = 10 / 100.f;
};
