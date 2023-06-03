#include <Poto.h>
#include <Poto/Core/EntryPoint.h>

#include "VideoPlayer.h"

class BadApple : public Poto::Application
{
public:
    BadApple()
    {
        PushLayer(new VideoPlayer(60, 6562));
    }
};

Poto::Application* Poto::CreateApplication()
{
    return new BadApple();
}
