#ifndef _WINDOW_
#define _WINDOW_

#include "surface.h"
#include <SDL.h>

class Window
{

public:
    Window();
	Window( const std::string& name, const int w, const int h );
	virtual ~Window();

	inline int width() const;
	inline int height() const;

	void initialize();
	void finalize();

	void draw( const Sprite& sprite, int x, int y );

	void update() const;

    SDL_Surface * get_surface() {
    	return surface_->get_surface();
    }


protected:
    SDL_Window* window_;

	/*La surface associee a la fenetre*/
	Surface* surface_;

	/*taille*/
	int w_;
	int h_;

	/*nom de la fenetre*/
	std::string title_;

private:

};

#include "window.inl"
#endif
