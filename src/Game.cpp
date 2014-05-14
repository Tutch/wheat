#include "Game.h"

Game::Game( )
{
    //ctor
}

Game::~Game( )
{
    //dtor
}

bool Game::isRunning( ) {
 return isRunning_;
}

bool Game::init( const char* title, int xpos, int ypos, int width, int height,
                 bool fullscreen ) {
  //check flags
  int flags = 0;
  if ( fullscreen ) {
    flags = SDL_WINDOW_FULLSCREEN;
  }
  //try to initialize SDL
  if ( SDL_Init( SDL_INIT_EVERYTHING ) == 0 ) {
    std::cout << "SDL init success\n";
    //init the window
    window_ = SDL_CreateWindow( title, xpos, ypos, width, height, flags );
    if ( window_ != 0 ) {
      //window init worked
      std::cout << "window success\n";
      renderer_ = SDL_CreateRenderer( window_, -1, 0 );
      if( renderer_ != 0 ) {
        //Render init worked
        std::cout << "render success\n";
        SDL_SetRenderDrawColor( renderer_, 255,255,255,255 );
      } else {
        std::cout << "render failed\n";
        return false; //it failed
      }
    } else {
      std::cout << "window failed\n";
      return false; //if failed, can't you see?
    }
  } else {
    std::cout << "SDL failed, life is suffering\n";
    return false; //SDL failed, it's ogre
  }
  std::cout << "All according to keikaku\n";
  isRunning_ = true; // All good on the front, start the main loop

  //load image
  SDL_Surface* tempSurface = SDL_LoadBMP("linkWalk.BMP");
  texture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
  SDL_FreeSurface(tempSurface);
  sourceRectangle_.x = 0;
  destinationRectangle_.x = 0;
  sourceRectangle_.y = 0;
  destinationRectangle_.y = 0;
  destinationRectangle_.w = sourceRectangle_.w = 100;
  destinationRectangle_.h = sourceRectangle_.h = 120;
  return true;
}

void Game::render( ) {
  SDL_RenderClear( renderer_ ); //clear the renderer to draw
  SDL_RenderCopyEx( renderer_, texture_, &sourceRectangle_,
                    &destinationRectangle_, 0, 0, SDL_FLIP_HORIZONTAL );
  SDL_RenderPresent( renderer_ ); //draw stuff
}

void Game::handleEvents( ) {
  SDL_Event event;
  if ( SDL_PollEvent(&event) ) {
    switch (event.type) {
      case SDL_QUIT:
        isRunning_ = false;
        break;
      default:
        break;
    }
  }
}

void Game::update() {
    sourceRectangle_.x = 120 * ( ( ( SDL_GetTicks( ) / 100 ) % 6 ) );
}

void Game::clean( ) {
  std::cout << "cleaning\n";
  SDL_DestroyWindow( window_ );
  SDL_DestroyRenderer( renderer_ );
  SDL_Quit( );
}
