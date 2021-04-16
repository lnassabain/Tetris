#include "sceneManager.hpp"
#include <iostream>

SceneManager::SceneManager()
:	window_( nullptr )
,	sprites_()
,	grid_nbRows_( 20 )
,	grid_nbColumns_( 10 )
,	grid_tileSize_( 32 )
{
    const int windowWidth = grid_nbColumns_ * grid_tileSize_ ;
    const int windowHeight = grid_nbRows_ * grid_tileSize_;
    const std::string windowTitle = "TETRIS";
    window_ = new Window( windowTitle, windowWidth, windowHeight );
    window_->initialize();

    Surface carre_surf ("./tetris_sprites.bmp");

    for (int i = 0 ; i < 9 ; i++)
    {
        sprites_.emplace_back( new Sprite( &carre_surf, i*(grid_tileSize_), 0,
                               grid_tileSize_, grid_tileSize_ ) );
    }

    Surface score_surf ("./score_level.bmp");
    SDL_SetColorKey( score_surf.getSurface(), true, SDL_MapRGB(score_surf.getSurface()->format, 30, 43, 128) );
    sprites_.emplace_back( new Sprite(&score_surf, 5, 0, 192, 50) ); //score
    sprites_.emplace_back( new Sprite(&score_surf, 5, 100, 196, 50) ); //level
    window_->draw(*sprites_[S_SCORE], 0, 0);
    window_->draw(*sprites_[S_LEVEL], 0, 100);
    window_->update();
    SDL_Delay(5000);

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

//////////////// DRAWER ////////////////

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

    std::cout << sfond << height << width << std::endl;


	for ( int j = y+Y_OFFSET; j < height; j += grid_tileSize_ ) // y
		for ( int i = X_OFFSET ; i <= width; i += grid_tileSize_ )// x
			window_->draw( *sfond, i, j );
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
    // On décale cette sprite d'une ligne vers le bas : y = manager_->get_tileSize()
    window_->draw( above, Y_OFFSET, grid_tileSize_ );
    drawBg( Y_OFFSET, 1 ); //une ligne de bg en haut de l'écran
}

void SceneManager::update()
{
    window_->update();
}
