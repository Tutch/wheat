#include "TextureManager.h"

TextureManager* TextureManager::instance_ = 0;

TextureManager::TextureManager()
{
    //ctor
}

TextureManager::~TextureManager()
{
    //dtor
}

TextureManager* TextureManager::Instance( ) {
  if ( instance_ == 0 ) {
    instance_ = new TextureManager();
    return instance_;
  }
  return instance_;
}

bool TextureManager::load( std::string fileName, std::string id,
    SDL_Renderer* renderer ) {
  SDL_Surface* tempSurface = IMG_Load( fileName.c_str( ) );
  //Check if the surface was properly loaded
  if ( tempSurface == 0 ) {
    return false;
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, tempSurface );
  SDL_FreeSurface( tempSurface );

  //add the texture to the list
  if (texture != 0) {
    textureMap_[id] = texture;
    return true;
  }
  //if it got here, something bad happened
  return false;
}

void TextureManager::draw( std::string id, int x, int y, int width, int height,
    SDL_Renderer* renderer, SDL_RendererFlip flip ) {

  SDL_Rect sourceRect;
  SDL_Rect destinationRect;

  sourceRect.x = 0;
  sourceRect.y = 1;
  sourceRect.w = destinationRect.w = width;
  sourceRect.h = destinationRect.h = height;
  destinationRect.x = x;
  destinationRect.y = y;

  SDL_RenderCopyEx(renderer, textureMap_[id], &sourceRect, &destinationRect, 0, 0, flip);
}

void TextureManager::drawFrame( std::string id, int x, int y, int width,
    int height, int currentRow, int currentFrame, SDL_Renderer* renderer,
    SDL_RendererFlip flip ) {

  SDL_Rect sourceRect;
  SDL_Rect destinationRect;

  sourceRect.x = width * currentFrame;
  sourceRect.y = height * (currentRow - 1);
  sourceRect.w = destinationRect.w = width;
  sourceRect.h = destinationRect.h = height;
  destinationRect.x = x;
  destinationRect.y = y;

  SDL_RenderCopyEx(renderer, textureMap_[id], &sourceRect, &destinationRect, 0, 0, flip);
}
