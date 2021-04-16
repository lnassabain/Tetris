#include "sceneManager.hpp"
#include <iostream>

SceneManager::SceneManager(bool multiplayer)
:	window_( nullptr )
,	sprites_(  )
,	grid_nbRows_( 20 )
,	grid_nbColumns_( 10 )
,	grid_tileSize_( 32 )
{
    if (!multiplayer) //si c'est singleplayer
    {
        const int windowWidth = grid_nbColumns_ * grid_tileSize_ + 235;
        const int windowHeight = grid_nbRows_ * grid_tileSize_;
        const std::string windowTitle = "TETRIS";
        window_ = new Window( windowTitle, windowWidth, windowHeight );
        window_->initialize();
    }
    else
    {
        const int windowWidth = grid_nbColumns_ * grid_tileSize_ + 235 + grid_nbColumns_ * grid_tileSize_;
        const int windowHeight = grid_nbRows_ * grid_tileSize_;
        const std::string windowTitle = "TETRIS";
        window_ = new Window(windowTitle, windowWidth, windowHeight);
        window_->initialize();
    }

    // Squares of color for each piece
    Surface* carre_surf = new Surface ("./tetris_sprites.bmp");
    for (int i = 0 ; i < 9 ; i++)
    {
        sprites_.emplace_back( new Sprite( carre_surf, i*(grid_tileSize_), 0,
                               grid_tileSize_, grid_tileSize_ ) );
    }

    // Score and Level
    Surface* score_surf = new Surface ("./score_level.bmp");
    SDL_SetColorKey( score_surf->getSurface(), true,
                     SDL_MapRGB(score_surf->getSurface()->format, 30, 43, 128));
    sprites_.emplace_back( new Sprite(score_surf, 5, 0, 192, 50) ); //score
    sprites_.emplace_back( new Sprite(score_surf, 5, 100, 196, 50) ); //level

    // Figures
    Surface* figure_surf = new Surface("./chiffre1.bmp");
    SDL_SetColorKey( figure_surf->getSurface(), true,
                     SDL_MapRGB(figure_surf->getSurface()->format, 30, 43, 128));
    sprites_.emplace_back( new Sprite( figure_surf, 0, 0, 34, 60 ) );
    sprites_.emplace_back( new Sprite( figure_surf, 40, 0, 30, 60 ) );
    sprites_.emplace_back( new Sprite( figure_surf, 70, 0, 34, 60 ) );
    sprites_.emplace_back( new Sprite( figure_surf, 106, 0, 34, 60 ) );
    sprites_.emplace_back( new Sprite( figure_surf, 145, 0, 34, 60 ) );
    sprites_.emplace_back( new Sprite( figure_surf, 182, 0, 34, 60 ) );
    sprites_.emplace_back( new Sprite( figure_surf, 219, 0, 34, 60 ) );
    sprites_.emplace_back( new Sprite( figure_surf, 253, 0, 34, 60 ) );
    sprites_.emplace_back( new Sprite( figure_surf, 290, 0, 34, 60 ) );
    sprites_.emplace_back( new Sprite( figure_surf, 328, 0, 34, 60 ) );

    // for (int i = 11 ; i < 22 ; i++ )
    // {
    //     window_->draw(*sprites_[i], ((i-S_FIG)*34)%320, 0);
    //     window_->update();
    //
    //     SDL_Delay(500);
    // }

    // Icon
    Surface* icon_surf = new Surface("./tetris-logo.bmp");
    sprites_.emplace_back( new Sprite( icon_surf, 0, 0, 412, 285 ) );

    // Letters
    Surface* letter_surf = new Surface("./font.bmp");
    SDL_SetColorKey( letter_surf->getSurface(), true,
                     SDL_MapRGB(letter_surf->getSurface()->format, 255, 255, 255));
    for (int y = 23 ; y < 3*84 ; y += 84)
    {
        for (int x = 16 ; x < 9*77 ; x += 77)
        {
            if ( y == 2*84+23 && x == 8*77+16 ) // dernière case vide
                continue;
            sprites_.emplace_back( new Sprite( letter_surf, x, y, 47, 47 ) );
        }
    }
    //std::cout << sprites_.size() << std::endl;

}
SceneManager::~SceneManager()
{
    for ( auto sprite : sprites_ )
    {
        delete sprite;
        sprite = nullptr;
    }
    sprites_.clear();

    delete window_;
    window_ = nullptr;
}

//////////////// GETTER ////////////////

const int SceneManager::get_nbRows() const {
    return grid_nbRows_;
}

const int SceneManager::get_nbCol() const {
    return grid_nbColumns_;
}

const int SceneManager::get_tileSize() const {
    return grid_tileSize_;
}

const int SceneManager::get_windowWidth() const {
    return window_->width();
}

const int SceneManager::get_windowHeight() const {
    return window_->height();
}

//////////////// DRAWER FOR THE PLAYGRID ////////////////

void SceneManager::drawPresMap(std::vector< std::vector< int > > presenceMap_)
{
	int i, j;
	int colID;

	for (i=0; i < grid_nbRows_; i++)
	{
		for (j=0; j<grid_nbColumns_; j++)
		{
			colID = presenceMap_[i][j];

			if (colID != 0)
			{
				window_->draw( *sprites_[colID], X_OFFSET+j*grid_tileSize_,
								Y_OFFSET+i*grid_tileSize_);
			}
		}
	}

	return;
}


void SceneManager::drawShape(Graphics::GraphicsObject* obj)
{
	const int colorID = obj->getColor();
	Sprite* obj_sprite = sprites_[ colorID ];

	for ( const auto& p : obj->tiles_[ obj->getRotation() ] ) //tous les carrés
	{
		const int x = obj->getPositionX();
		const int y = obj->getPositionY();

		window_->draw( *obj_sprite, X_OFFSET + x + p.first * grid_tileSize_,
			 			Y_OFFSET + y + p.second * grid_tileSize_ );
	}
}


/**
 * Draw a certain number of lines of background at a certain position.
 * @param y       y coordinate of the upper left angle -> position of the line (in the grid ref)
 * @param nbLines number of lines of background we want to draw
 */
void SceneManager::drawBg(int y, int nbLines)
{
	Sprite* sfond = sprites_[ S_GRIS ];
	int height = nbLines * grid_tileSize_;
    int width = grid_nbColumns_*grid_tileSize_;

	for ( int j = y+Y_OFFSET; j < height+Y_OFFSET; j += grid_tileSize_ ) // y
    {
        for ( int i = X_OFFSET ; i < width+X_OFFSET; i += grid_tileSize_ )// x
        {
            window_->draw( *sfond, i, j );
        }
    }
}


void SceneManager::drawShadow(Graphics::GraphicsObject& shadow)
{
    Sprite* obj_sprite = sprites_[ S_SHADOW ];
    int x = shadow.getPositionX();
    int y = shadow.getPositionY();
    for ( const auto& p : shadow.tiles_[ shadow.getRotation() ] ) //tous les carrés
        window_->draw( *obj_sprite, X_OFFSET + x + p.first * grid_tileSize_,
                        Y_OFFSET + y + p.second * grid_tileSize_ );
}


/* on prend la surface de tout ce qu'il y a au dessus de cette ligne
et on la copie une ligne plus bas
+ on reaffiche le fond en haut */
void SceneManager::drawEraseLine(int line)
{
    Sprite above ( window_->getSurface(), X_OFFSET, Y_OFFSET,
                   grid_nbColumns_ * grid_tileSize_,
                   grid_tileSize_ * line);
    // On décale cette sprite d'une ligne vers le bas : y = grid_tileSize_
    window_->draw( above, X_OFFSET, grid_tileSize_ );
    drawBg( Y_OFFSET, 1 ); //une ligne de bg en haut de l'écran
}

//////////////// STATS DISPLAY ////////////////

void SceneManager::displayWord(int x, int y, Word word)
{
    for (int i = 0 ; i < word.size() ; i++)
    {
        if (word[i] != -1)
        {
            window_->draw(*sprites_[S_LETTER + word[i] - 1], x, y);
        }
        x += sprites_[S_LETTER]->width();
    }
}


void SceneManager::displayMenu(int mode)
{
    // title
    SDL_Surface* win_surf = window_->getSurface()->getSurface();
    SDL_FillRect(win_surf, NULL, SDL_MapRGB(win_surf->format, 120, 225, 252));
    int x = window_->width() / 2 - sprites_[S_ICON]->width() / 2;
    window_->draw(*sprites_[S_ICON], x, 0);

    // marathon
    Word marathon = { 13, 1, 18, 1, 20, 8, 15, 14 };
    int w_ma = sprites_[S_LETTER]->width() * marathon.size();
    int x_ma = window_->width() / 2 - w_ma / 2;

    // vs cpu
    Word vs_cpu = { 22, 19, -1, 3, 16, 21 };
    int w_vs = sprites_[S_LETTER]->width() * vs_cpu.size();
    int x_vs = window_->width() / 2 - w_vs / 2;

    // quit
    Word quit = { 17, 21, 9, 20 };
    int w_qu = sprites_[S_LETTER]->width() * quit.size();
    int x_qu = window_->width() / 2 - w_qu / 2;

    // selected mode -> filled rectangle
    int x_rect [] = { x_ma, x_vs, x_qu };
    int w_rect [] = { w_ma, w_vs, w_qu };
    int border = 5;
    const SDL_Rect mode_rect = { x_rect[mode]-5, 350 + mode*100 - 5,
                                 w_rect[mode]+10, 50+10 };
    SDL_FillRect(win_surf, &mode_rect,
                 SDL_MapRGB(win_surf->format, 242, 132, 245));


    displayWord(x_ma, 350, marathon);
    displayWord(x_vs, 450, vs_cpu);
    displayWord(x_qu, 550, quit);

    window_->update();
}


void SceneManager::display_1p()
{
    const SDL_Rect fond = { 320, 0, 235, 640 };
    SDL_FillRect(window_->getSurface()->getSurface(), &fond, 0);
    window_->draw(*sprites_[S_SCORE], 330, 15);
    window_->draw(*sprites_[S_LEVEL], 330, 15+80+50);
}

void SceneManager::displayFigure(int figure, int x, int y)
{
    int unite = 0;
    int dizaine = 0;
    int centaine = 0;
    int millier = 0;

    if (figure >= 1000)
    {
        millier = figure / 1000;
        figure %= 1000;
    }
    if (figure >= 100)
    {
        centaine = figure / 100;
        figure %= 100;
    }
    if (figure >= 10)
    {
        dizaine = figure / 10;
        unite = figure % 10;
    }
    else
        unite = figure;

    window_->draw(*sprites_[S_FIG + millier], x-32*2, y);
    window_->draw(*sprites_[S_FIG + centaine], x-32, y);
    window_->draw(*sprites_[S_FIG + dizaine], x, y);
    window_->draw(*sprites_[S_FIG + unite], x+32, y);
}


//////////////// UTILS ////////////////

void SceneManager::update()
{
    window_->update();
}
