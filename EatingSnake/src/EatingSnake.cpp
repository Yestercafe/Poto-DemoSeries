#include <Poto.h>
#include <Poto/Core/EntryPoint.h>

#include "Gameplay.h"

class EatingSnake : public Poto::Application
{
public:
    EatingSnake()
    {
        PushLayer(new Gameplay());
    }

    ~EatingSnake() {}
};

Poto::Application* Poto::CreateApplication()
{
    return new EatingSnake();
}

