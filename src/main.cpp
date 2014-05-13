#include "Game.h"

//our Game
Game* g_game = 0;

int main(int argc, char* args[ ]) {
    g_game = new Game( );

    g_game->init( "Ch 1", 100, 100, 1280, 720, false );

    while( g_game->running( ) ) {
        g_game->handleEvents( );
        g_game->update( );
        g_game->render( );
    }
    g_game->clean( );

    return 0;
}
