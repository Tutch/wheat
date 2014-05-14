#include "Game.h"

//our Game
Game* game = 0;

int main(int argc, char* args[ ]) {
  game = new Game( );

  game->init( "Ch 1", 100, 100, 1280, 720, false );
  while( game->isRunning( ) ) {
    game->handleEvents( );
    game->update( );
    game->render( );
  }
  game->clean( );
  return 0;
}
