#include <iostream>
#include <vec2.hpp>
#include <SDL.h>
#include <glm.hpp>
#include <glm/gtc/random.hpp>

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius);

// create a class to represent a particle
class Particle
{
public:
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 acceleration;
    double radius;
    // update function with a time step
    void update(float dt)
    {
        // update the velocity
        velocity += acceleration * dt;
        // update the position
        position += velocity * dt;
    }
};

int main(int argc, char **argv)
{
    // define window size
    const int width = 800;
    const int height = 600;

    // create a glm vec2
    glm::vec2 v1(1.0f, 2.0f);

    // create a sdl window and renderer
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window =
        SDL_CreateWindow("Simulation",
                         SDL_WINDOWPOS_CENTERED,
                         -width,
                         width, height, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // create 10 random particles and store them in an array
    const int numParticles = 10;
    Particle particles[numParticles];
    for (int i = 0; i < numParticles; i++)
    {
        float x = glm::linearRand(-200.0f, 200.0f);
        float y = glm::linearRand(-200.0f, 200.0f);
        particles[i].position = glm::vec2(400, 300);
        particles[i].velocity = glm::vec2(x, y);
        particles[i].acceleration = glm::vec2(0, 0);
        particles[i].radius = 10;
    }

    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        // clear the window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        // draw the particle as a white circle
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // update the particle
        for (int i = 0; i < numParticles; i++)
        {
            // detect collision with the window
            if (particles[i].position.x < 0 || particles[i].position.x > width)
            {
                particles[i].velocity.x *= -1;
            }
            if (particles[i].position.y < 0 || particles[i].position.y > height)
            {
                particles[i].velocity.y *= -1;
            }
        }

        // detect collision with other particles
        for (int i = 0; i < numParticles; i++)
        for (int j = 0; j < numParticles; j++)
        {
            if (i != j)
            {
                glm::vec2 distance = particles[i].position - particles[j].position;
                if (glm::length(distance) < particles[i].radius + particles[j].radius)
                {
                    // static collision
                    // calculate distance between the two particles
                    glm::vec2 distance = particles[i].position - particles[j].position;
                    // calculate overlap
                    float overlap = particles[i].radius + particles[j].radius - glm::length(distance);
                    // move the particles apart
                    particles[i].position += glm::normalize(distance) * overlap * 0.5f;

                    /*
                    // normal
                    glm::vec2 normal = glm::normalize(distance);
                    // tangent
                    glm::vec2 tangent = glm::vec2(-normal.y, normal.x);
                    // dot product of velocity and normal
                    float dpTan1 = glm::dot(particles[i].velocity, tangent);
                    float dpTan2 = glm::dot(particles[j].velocity, tangent);
                    // dot product of velocity and tangent
                    float dpNorm1 = glm::dot(particles[i].velocity, normal);
                    float dpNorm2 = glm::dot(particles[j].velocity, normal);
                    // conservation of momentum in 1d
                    float m1 = 1.0f;
                    float m2 = 1.0f;
                    float m21 = m2 / m1;
                    float newDpNorm1 = (dpNorm1 * (m1 - m21) + 2.0f * m21 * dpNorm2) / (m1 + m2);
                    float newDpNorm2 = (dpNorm2 * (m2 - m21) + 2.0f * m21 * dpNorm1) / (m1 + m2);
                    // update the velocity
                    particles[i].velocity = tangent * dpTan1 + normal * newDpNorm1;
                    particles[j].velocity = tangent * dpTan2 + normal * newDpNorm2;
                    */
                }
            }
        }

        for (int i = 0; i < numParticles; i++)
            particles[i].update(0.01f);

        // draw the particle
        for (int i = 0; i < numParticles; i++)
        {
            drawCircle(renderer, particles[i].position.x,
                       particles[i].position.y, particles[i].radius);
        }

        // update the window
        SDL_RenderPresent(renderer);
        // show the window

        SDL_Delay(20);
    }

    return 0;
}

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius)
{
    for (double angle = 0; angle < 2 * M_PI; angle += 0.01)
    {
        int x = centerX + (int)(radius * cos(angle));
        int y = centerY + (int)(radius * sin(angle));
        SDL_RenderDrawPoint(renderer, x, y);
    }
}
