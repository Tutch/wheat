#include "Game.h"

Game::Game( )
{
    //ctor
}

Game::~Game( )
{
    //dtor
}

bool Game::init( const char* title, int xpos, int ypos, int width, int height, bool fullscreen ) {
    //check flags
    int flags = 0;
    if ( fullscreen ) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    //try to initialize SDL
    if ( SDL_Init( SDL_INIT_EVERYTHING ) == 0 ) {
        std::cout << "SDL init success\n";
        //init the window
        m_pWindow = SDL_CreateWindow( title, xpos, ypos, width, height, flags );
        if ( m_pWindow != 0 ) {
            //window init worked
            std::cout << "window success\n";
            m_pRenderer = SDL_CreateRenderer( m_pWindow, -1, 0 );
            if( m_pRenderer != 0 ) {
                //Render init worked
                std::cout << "render success\n";
                SDL_SetRenderDrawColor( m_pRenderer, 255,255,255,255 );
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
    m_bRunning = true; // All good on the front, start the main loop

    //load image
    SDL_Surface* pTempSurface = SDL_LoadBMP("linkWalk.BMP");
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);
    m_sourceRectangle.x = 0;
    m_destinationRectangle.x = 0;
    m_sourceRectangle.y = 0;
    m_destinationRectangle.y = 0;
    m_destinationRectangle.w = m_sourceRectangle.w = 100;
    m_destinationRectangle.h = m_sourceRectangle.h = 120;

    return true;
}

void Game::render( ) {
    SDL_RenderClear( m_pRenderer ); //clear the renderer to draw
    SDL_RenderCopyEx( m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0, 0, SDL_FLIP_HORIZONTAL );
    SDL_RenderPresent( m_pRenderer ); //draw stuff
}

void Game::handleEvents( ) {
    SDL_Event event;
    if ( SDL_PollEvent(&event) ) {
        switch (event.type) {
            case SDL_QUIT:
                m_bRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::update() {
    m_sourceRectangle.x = 120 * ( ( ( SDL_GetTicks( ) / 100 ) % 6 ) );
}

void Game::clean( ) {
    std::cout << "cleaning\n";
    SDL_DestroyWindow( m_pWindow );
    SDL_DestroyRenderer( m_pRenderer );
    SDL_Quit( );
}
