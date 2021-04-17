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
    std::cout << sprites_.size() << std::endl;

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

void SceneManager::drawPresMap(std::vector< std::vector< int > > presenceMap_, int scene_id)
{
	int i, j;
	int colID;
    int x_offset, y_offset;

    switch (scene_id)
    {
        case 1:
            x_offset = X_OFFSET;
            y_offset = Y_OFFSET;
            break;
        case 2:
            x_offset = X2_OFFSET;
            y_offset = Y2_OFFSET;
            break;
        default:
            std::cerr << "Numero de grid non valide" << std::endl;
            exit(1);
            break;
    }


	for (i=0; i < grid_nbRows_; i++)
	{
		for (j=0; j<grid_nbColumns_; j++)
		{
			colID = presenceMap_[i][j];

			if (colID != 0)
			{
				window_->draw( *sprites_[colID], x_offset+j*grid_tileSize_,
								y_offset+i*grid_tileSize_);
			}
		}
	}

	return;
}


void SceneManager::drawShape(Graphics::GraphicsObject* obj, int scene_id)
{
	const int colorID = obj->getColor();
	Sprite* obj_sprite = sprites_[ colorID ];
    int x_offset, y_offset;
    switch(scene_id)
    {
        case 1:
            x_offset = X_OFFSET;
            y_offset = Y_OFFSET;
            break;
        case 2:
            x_offset = X2_OFFSET;
            y_offset = Y2_OFFSET;
            break;
        default:
            std::cerr << "Numero de grid non valide" << std::endl;
            exit(1);
            break;
    }

	for ( const auto& p : obj->tiles_[ obj->getRotation() ] ) //tous les carrés
	{
		const int x = obj->getPositionX();
		const int y = obj->getPositionY();

		window_->draw( *obj_sprite, x + p.first * grid_tileSize_,
			 			y + p.second * grid_tileSize_ );
	}
}


/**
 * Draw a certain number of lines of background at a certain position.
 * @param y       y coordinate of the upper left angle -> position of the line (in the grid ref)
 * @param nbLines number of lines of background we want to draw
 */
void SceneManager::drawBg(int y, int nbLines, int scene_id)
{
	Sprite* sfond = sprites_[ S_GRIS ];
	int height = nbLines * grid_tileSize_;
    int width = grid_nbColumns_*grid_tileSize_;
    int x_offset, y_offset;

    switch(scene_id)
    {
        case 1:
            x_offset = X_OFFSET;
            y_offset = Y_OFFSET;
            break;
        case 2:
            x_offset = X2_OFFSET;
            y_offset = Y2_OFFSET;
            break;
        default:
            std::cerr << "Numero de grid non valide" << std::endl;
            exit(1);
            break;
    }

	for ( int j = y+y_offset; j < height+y_offset; j += grid_tileSize_ ) // y
    {
        for ( int i = x_offset ; i < width+x_offset; i += grid_tileSize_ )// x
        {
            window_->draw( *sfond, i, j );
        }
    }
}


void SceneManager::drawShadow(Graphics::GraphicsObject& shadow, int scene_id)
{
    Sprite* obj_sprite = sprites_[ S_SHADOW ];
    int x = shadow.getPositionX();
    int y = shadow.getPositionY();
    int x_offset, y_offset;
    switch(scene_id)
    {
        case 1:
            x_offset = X_OFFSET;
            y_offset = Y_OFFSET;
            break;
        case 2:
            x_offset = X2_OFFSET;
            y_offset = Y2_OFFSET;
            break;
        default:
            std::cerr << "Numero de grid non valide" << std::endl;
            exit(1);
            break;
    }

    for ( const auto& p : shadow.tiles_[ shadow.getRotation() ] ) //tous les carrés
        window_->draw( *obj_sprite, x_offset + x + p.first * grid_tileSize_,
                        y_offset + y + p.second * grid_tileSize_ );
}


/* on prend la surface de tout ce qu'il y a au dessus de cette ligne
et on la copie une ligne plus bas
+ on reaffiche le fond en haut */
void SceneManager::drawEraseLine(int line, int scene_id)
{
    int x_offset, y_offset;
    switch (scene_id)
    {
        case 1:
            x_offset = X_OFFSET;
            y_offset = Y_OFFSET;
            break;
        case 2:
            x_offset = X2_OFFSET;
            y_offset = Y2_OFFSET;
            break;
        default:
            std::cerr << "Numero de grid non valide" << std::endl;
            exit(1);
            break;
    }

    Sprite above ( window_->getSurface(), x_offset, y_offset,
                   grid_nbColumns_ * grid_tileSize_,
                   grid_tileSize_ * line);
    // On décale cette sprite d'une ligne vers le bas : y = grid_tileSize_
    window_->draw( above, x_offset, grid_tileSize_ );
    drawBg( y_offset, 1 , 1); //une ligne de bg en haut de l'écran
}

//////////////// GAME DISPLAY ////////////////

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


void SceneManager::display_2p()
{
    display_1p();

    // Affichage écriture CPU :
    int y = 295;
    int h = sprites_[S_LETTER]->height() + 10;
    SDL_Surface* win_surf = window_->getSurface()->getSurface();

    Word cpu = { 3, 16, 21 };
    rectWord(cpu, y, SDL_MapRGB(win_surf->format, 0, 255, 251));

    // Affiche sprite score :
    window_->draw(*sprites_[S_SCORE], 235/2 - sprites_[S_SCORE]->width()/2 + 320,
                  y + h + 5);
}


void SceneManager::displayGO()
{
    Word game = { 7, 1, 13, 5 };
    Word over = { 15, 22, 5, 18 };
    int y = window_->height()/2 - sprites_[S_LETTER]->height()/2;
    rectWord(game, y, SDL_MapRGB(window_->getSurface()->getSurface()->format, 255, 0, 0));
    rectWord(over, y + sprites_[S_LETTER]->height(),
             SDL_MapRGB(window_->getSurface()->getSurface()->format, 255, 0, 0));

    window_->update();
    SDL_Delay(5000);
}



//////////////// STATS DISPLAY ////////////////


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


void SceneManager::displayNext(Graphics::GraphicsObject* next)
{
    // Affichage écriture :
    int y = 500;
    int h = sprites_[S_LETTER]->height() + 10;
    SDL_Surface* win_surf = window_->getSurface()->getSurface();

    Word next_w = { 14, 5, 24, 20 };
    rectWord(next_w, y, SDL_MapRGB(win_surf->format, 0, 255, 251));

    // Affichage piece :
    const int colorID = next->getColor();
	Sprite* next_sprite = sprites_[ colorID ];
    int y_offset =  y + h + 10 ;

    int x_offset = 390;
    if (next->getColor() == S_CYAN) // le I
        x_offset = 375;
    else if (next->getColor() == S_JAUNE) // le carré
        x_offset = 405;

    for ( const auto& p : next->tiles_[ next->getRotation() ] ) //tous les carrés
    {
        window_->draw( *next_sprite, x_offset + p.first * grid_tileSize_,
                        y_offset + p.second * grid_tileSize_ );
    }
}


//////////////// UTILS ////////////////

void SceneManager::update()
{
    window_->update();
}

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

//x est centré dans le rectangle noir
void SceneManager::rectWord(Word word, int y, Uint32 color)
{
    int w = sprites_[S_LETTER]->width() * word.size() + 10;
    int h = sprites_[S_LETTER]->height() + 10;
    int x = 235 / 2 - w / 2 + 320;
    SDL_Surface* win_surf = window_->getSurface()->getSurface();

    const SDL_Rect fond = { x, y, w, h };
    SDL_FillRect(win_surf, &fond, color);

    displayWord(x+5, y+5, word);
}
