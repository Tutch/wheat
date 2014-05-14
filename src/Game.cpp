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
    mainWindow_ = SDL_CreateWindow( title, xpos, ypos, width, height, flags );
    if ( mainWindow_ != 0 ) {
      //window init worked
      std::cout << "window success\n";
      renderer_ = SDL_CreateRenderer( mainWindow_, -1, 0 );
      if( renderer_ != 0 ) {
        //Render init worked
        std::cout << "render success\n";
        SDL_SetRenderDrawColor( renderer_, 255, 0, 0,255 );
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
  TextureManager::Instance( )->load( "linkWalk.png","playerWalk", renderer_ );
  return true;
}

void Game::render( ) {
  SDL_RenderClear( renderer_ ); //clear the renderer to draw
  TextureManager::Instance( )->draw("playerWalk", 0, 0, 120, 120, renderer_);
  TextureManager::Instance( )->drawFrame("playerWalk", 120, 0, 120, 120, 1, currentFrame_,
      renderer_);
  SDL_RenderPresent( renderer_ ); //draw stuff
}

void Game::handleEvents( ) {
  SDL_Event event;
  if ( SDL_PollEvent( &event ) ) {
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
  currentFrame_ = int( ( SDL_GetTicks( ) / 100 ) % 6 );
}

void Game::clean( ) {
  std::cout << "cleaning\n";
  SDL_DestroyWindow( mainWindow_ );
  SDL_DestroyRenderer( renderer_ );
  SDL_Quit( );
}
