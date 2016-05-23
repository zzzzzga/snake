#include "Body.h"
#include "Util.h"

Body::Body(int x, int y, Node* layer ,bool isHead)
{

	this->X = x;
	this->Y = y;

	if (isHead)
	{
		sp = Sprite::create("head.png");
		layer->addChild(sp, 2);
	}
	else
	{
		sp = Sprite::create("body.png");
		layer->addChild(sp, 1);
	}
	

	this->update();

}

void Body::update()
{
	this->sp->setPosition(Util::Grid2Pos(this->X, this->Y));
}