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
#define S_FIG 11
#define S_ICON 21
#define S_LETTER 22


#define X_OFFSET 0
#define Y_OFFSET 0

//Pour la deuxieme fenetre quand on joue en multi
#define X2_OFFSET 555
#define Y2_OFFSET 0
/*Pour toutes les fonction draw, il faudrait rajouter un paremetre "int scene",
si scene == 1 alors on dessine sur la premiere fenetre (on utlise X2, Y2_OFFSET),
si scene == 2 alors on dessine sur le deuxième fenetre (on utilise X, Y_OFFSET)*/

using Word = std::vector< int >; // index of each letter of word in alphabet (-1 = space)

class SceneManager
{
public:
    SceneManager(bool multiplayer);
    ~SceneManager();

    const int get_nbRows() const;
    const int get_nbCol() const ;
    const int get_tileSize() const ;
    const int get_windowWidth() const ;
    const int get_windowHeight() const ;


	void drawShape(Graphics::GraphicsObject* obj, int scene_id);
	void drawBg(int y, int nbLines, int scene_id);
	void drawPresMap(std::vector< std::vector< int > > presenceMap_, int scene_id);
    void drawShadow(Graphics::GraphicsObject& shadow, int scene_id);
    void drawEraseLine(int line, int scene_id);

    void displayWord(int x, int y, Word word);
    void displayMenu(int mode);
    void display_1p();
    void display_2p();
    void displayFigure(int figure, int x, int y);
    void displayNext(Graphics::GraphicsObject* next);

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
