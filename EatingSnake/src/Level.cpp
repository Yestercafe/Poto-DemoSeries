#include "Level.h"

#include <set>

#include "Random.h"

Level::Level(std::pair<uint, uint> levelSize)
{
    m_LevelSize = levelSize;
    Reset();
}
    
void Level::Reset()
{
    m_Snake = Poto::CreateScope<Snake>(m_LevelSize.first, m_LevelSize.second);
    m_Food = {};
}

void Level::TicToc()
{
    bool shouldInc = false;
    if (m_Food.has_value())
    {
        if (m_Food.value() == m_Snake->HeadNextStep())
        {
            shouldInc = true;
            m_Food = {};
        }
    }
    
    m_Snake->m_Age += 1.f / FACTOR;
    m_Snake->MoveByStep(shouldInc);
    
    if (m_Snake->IsDead())
    {
        auto score = m_Snake->GetScore();
    }
}

bool Level::OnUpdate(Poto::Timestep ts)
{
    if (m_Snake->IsDead())
    {
        return false;
    }
    if (!m_Food.has_value())
    {
        std::set<std::pair<uint, uint>> SnakeBlocks(m_Snake->GetSnakeChain().cbegin(), m_Snake->GetSnakeChain().cend());
        auto foodPosIdx = Random::RandomUint(m_LevelSize.first * m_LevelSize.second - SnakeBlocks.size());
        std::pair<uint, uint> foodPos;
        for (uint x = 0; x < m_LevelSize.first; ++x)
        {
            for (uint y = 0; y < m_LevelSize.second; ++y)
            {
                auto p = std::make_pair(x, y);
                if (!SnakeBlocks.contains(p))
                {
                    --foodPosIdx;
                }
                if (!foodPosIdx)
                {
                    foodPos = p;
                    break;
                }
            }
        }
        m_Food = foodPos;
    }

    m_LevelTimer += ts;
    if (FACTOR * m_LevelTimer > m_Snake->m_Age)
    {
        TicToc();
    }

    return true;
}

void Level::OnRender()
{
    const auto [width, height] = m_LevelSize;
    const glm::vec4 white = {1.f, 1.f, 1.f, 1.f};
    const glm::vec4 yellow = {1.f, 1.f, 0.2f, 1.f};
    const glm::vec4 blue = {0.2f, 0.2f, 1.f, 1.f};
    const glm::vec4 green = {0.2f, 1.0f, 0.2f, 1.f};

    const float farX = (int) width / -2.f + m_BlockSide / 2.f;
    const float farY = (int) height / -2.f + m_BlockSide / 2.f;
    glm::vec2 blockSizeWithPadding = {m_BlockSide - 2 * m_BlockPadding, m_BlockSide - 2 * m_BlockPadding};
    
    for (float x = farX - m_BlockSide, xi = 0; xi < width + 2; ++xi, x += m_BlockSide)
    {
        for (float y = farY - m_BlockSide, yi = 0; yi < height + 2; ++yi, y += m_BlockSide)
        {
            if (xi == 0 || xi == width + 1 || yi == 0 || yi == height + 1)
                Poto::Renderer2D::DrawQuad({x, y}, blockSizeWithPadding, white);
        }
    }

    Poto::Renderer2D::DrawQuad({0, 0}, {width - 2 - 2 * (m_BlockPadding - m_BlockSide), height - 2 - 2 * (m_BlockPadding - m_BlockSide)}, white * 0.3f);

    // rendering snake
    const auto& snakeChain = m_Snake->GetSnakeChain();
    auto toRenderPos = [&](const std::pair<uint, uint> i) -> glm::vec3
    {
        auto [x, y] = i;
        return {farX + x * m_BlockSide, farY + y * m_BlockSide, 0.01f};
    };
    auto itr = snakeChain.cbegin();
    Poto::Renderer2D::DrawQuad(toRenderPos(*itr++), blockSizeWithPadding, blue);
    while (itr != snakeChain.cend())
    {
        Poto::Renderer2D::DrawQuad(toRenderPos(*itr), blockSizeWithPadding, yellow);
        ++itr;
    }

    // rendering food
    if (m_Food.has_value())
    {
        Poto::Renderer2D::DrawQuad(toRenderPos(m_Food.value()), blockSizeWithPadding, green);
    }
}

void Level::OnImGuiRender()
{
}

std::pair<uint, uint> Level::HeadNextStep() const
{
    return {};
}
