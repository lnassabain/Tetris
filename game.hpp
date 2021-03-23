#ifndef _GAME_H_
#define _GAME_H_

#include <cstdint>
#include <vector>
#include <list>

class Window;
class Surface;
class Sprite;



class Game
{
public:
	Game();
	virtual ~Game();

	void initialize();
	void finalize();
    void loop();

protected:
	/*Graphics window*/
	Window* window_;

	void draw( double dt );

    /*Keyboard management*/
	void keyboard( const std::uint8_t* keys );

private:
	Surface* planche_;
	std::vector< Sprite* > sprites_;

	std::list< std::vector< bool > > presenceMap_;

	void drawMap();

};

#endif
