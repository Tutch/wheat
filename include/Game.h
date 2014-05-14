#ifndef GAME_H
#define GAME_H

#include<SDL.h>
#include<iostream>

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
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Texture* texture_;
    SDL_Rect sourceRectangle_;
    SDL_Rect destinationRectangle_;
    bool isRunning_;
};

#endif // GAME_H
