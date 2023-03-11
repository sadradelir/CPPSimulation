#include <iostream>
#include <glm.hpp>
#include <vec2.hpp>
#include <SDL.h>


int main()
{
    glm::vec2 v1(1.0f, 2.0f);
    glm::vec2 v2(3.0f, 4.0f);
    glm::vec2 v3 = v1 + v2;
    // print v3
    std::cout << v3.x << " " << v3.y << std::endl;
        
    return 0;
}