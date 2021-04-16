#include "window.h"
#include "GraphicsObject.h"
#include "sprite.h"

#define S_GRIS 0
#define S_ROUGE 1
#define S_JAUNE 2
#define S_VERT 3
#define S_BLEU 4
#define S_VIOLET 5
#define S_ORANGE 6
#define S_CYAN 7
#define S_SHADOW 8
#define S_SCORE 9
#define S_LEVEL 10

#define X_OFFSET 0
#define Y_OFFSET 0

class SceneManager
{
public:
    SceneManager();
    ~SceneManager();

    const int get_nbRows() const;
    const int get_nbCol() const ;
    const int get_tileSize() const ;
    const int get_windowWidth() const ;
    const int get_windowHeight() const ;


	void drawShape(Graphics::GraphicsObject* obj);
	void drawBg(int y, int nbLines);
	void drawPresMap(std::vector< std::vector< int > > presenceMap_);
    void drawShadow(Graphics::GraphicsObject& shadow);
    void drawEraseLine(int line);

    void display_1p();

    void update();


private:
    // Grid
    int grid_nbRows_;
    int grid_nbColumns_;
    int grid_tileSize_;

    Window* window_;

    Surface* planche_;
    std::vector< Sprite* > sprites_;

};
