#ifndef GAME_H
#define GAME_H

#include"TextureManager.h"

class Game
{
  public:
    Game( );
    ~Game( );
    bool init( const char* title, int xpos, int ypos, int width, int height,
        bool fullscreen );
    void render( );
    void update( );
    void handleEvents( );
    void clean( );
    bool isRunning( );
  protected:
  private:
    SDL_Window* mainWindow_;
    SDL_Renderer* renderer_;
    int currentFrame_;
    bool isRunning_;
};

#endif // GAME_H
