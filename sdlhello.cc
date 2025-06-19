#include <emscripten.h>
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

class Game
{
public:
    Game();
    ~Game();

public:
    bool init(const char* title, 
        int xpos = 100, int ypos = 100, 
        int width = 640, int height = 480, 
        int flags = 0);
    void handleEvents();
    void update();
    void render();
    void clean();

public:
    bool running() { return m_running; }

private:
    bool m_running;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;

    int iteration;
};

Game::Game()
    : m_running(false), iteration(0)
{ }

Game::~Game()
{ }

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    if (SDL_Init(SDL_INIT_VIDEO) == 0)
    {
        m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (m_window != 0)
        {
            m_renderer = SDL_CreateRenderer(m_window, -1, 0);
            if (m_renderer != 0)
            {
                SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255); // red

                m_running = true;
            }
            else
                cout << "SDL_CreateRenderer failure" << endl;
        }
        else
            cout << "SDL_CreateWindow failure" << endl;
    }
    else
        cout << "SDL_Init failure" << endl;

    cout << "Running!" << endl;
    return m_running;
}
void Game::handleEvents()
{

}
void Game::update()
{
    iteration++;
}
void Game::render()
{
    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    SDL_Rect r;
    r.x = iteration % 255;
    r.y = 50;
    r.w = 50;
    r.h = 50;
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(m_renderer, &r);

    SDL_RenderPresent(m_renderer);
}
void Game::clean()
{
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

// =============================================================

void mainloop(void* arg)
{
    Game* g = static_cast<Game*>(arg);

    if (g->running())
    {
        g->handleEvents();
        g->update();
        g->render();
    }
}
int main(int argc, char* argv[])
{
    Game g;

    if (g.init("Chapter 2"))
    {
        const int fps = -1; // as fast as browser can
        const int simulate_infinite_loop = 1;
        emscripten_set_main_loop_arg(mainloop, &g, fps, simulate_infinite_loop);
    }
    else
    {
        cout << "Initialization failure" << endl;
    }

    g.clean();

    cout << "END" << endl;
    return 0;
}