#include <iostream>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>

// a class called GObject with a position and a velocity both of type glm::vec2
class GObject
{
public:    
    GObject() : pos(glm::vec2(0.0f, 0.0f)), vel(glm::vec2(0.0f, 0.0f)) {}
    GObject(glm::vec2 pos, glm::vec2 vel) : pos(pos), vel(vel) {}
    glm::vec2 pos;
    glm::vec2 vel;
};

int main()
{
    // create 10 objects with random positions and velocities
    GObject objects[10];
    for (int i = 0; i < 10; ++i)
    {
        // print the position and velocity of each object
        std::cout << "Object " << i << " position: " << objects[i].pos.x << ", " << objects[i].pos.y << std::endl;
    }    
    return 0;
}