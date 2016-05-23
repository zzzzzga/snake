#include "AppleFactory.h"
#include "Util.h"

Sprite* AppleFactory::apple = NULL;
int AppleFactory::x = 0;
int AppleFactory::y = 0;

void AppleFactory::createApple(Layer* layer)
{
	if (apple==NULL)
	{
		apple = Sprite::create("apple.png");
		layer->addChild(apple, 0);
	}

	x = rand()%(GRIDSUM*2-1) - GRIDSUM + 1; //-6, 6
	y = rand()%(GRIDSUM*2-1) - GRIDSUM + 1; //-6, 6

	apple->setPosition(Util::Grid2Pos(x, y));
	//apple->setPosition(Util::Grid2Pos(-6, -6));
	
}