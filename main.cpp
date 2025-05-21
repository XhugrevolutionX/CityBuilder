#include <__msvc_ostream.hpp>
#include <iostream>


#include "game.h"
#include "maths/vec2f.h"

int main()
{
    core::Vec2f v{1,2};
    core::Vec2f v2{0,2};

    core::Vec2f res = v/v2;

    std::cout << res.x << " " << res.y << std::endl;

    Game::Loop();
    return 0;
}
