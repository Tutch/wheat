#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<map>

class TextureManager
{
  public:
    static TextureManager* Instance( );
    virtual ~TextureManager();
    bool load( std::string fileName, std::string id,
        SDL_Renderer* renderer );
    void draw( std::string id, int x, int y, int width, int height,
        SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void drawFrame( std::string id, int x, int y, int width, int height,
        int currentRow, int currentFrame, SDL_Renderer* renderer,
        SDL_RendererFlip flip = SDL_FLIP_NONE );
  protected:
  private:
    TextureManager();
    static TextureManager* instance_;
    std::map<std::string, SDL_Texture*> textureMap_;
};

#endif // TEXTUREMANAGER_H
