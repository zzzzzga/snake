#include "Snake.h"
#include "AppleFactory.h"

Snake::Snake(Node* node)
{
	this->node = node;
	this->bodyArray.clear();

	for (int i = 0; i < initLen; i++)
	{
		grow(i == 0);
	}
}

void Snake::grow(bool isHead)
{
	Point tailPos = getTailGrid();

	//分配内存,在kill中释放
	Body* body = new Body(tailPos.x, tailPos.y, node, isHead);

	bodyArray.push_back(body);
}

Point Snake::getTailGrid()
{
	if (bodyArray.empty())
	{
		return Point::ZERO;
	}
	auto body = bodyArray.at(bodyArray.size() - 1);

	return Vec2(body->getX(), body->getY());
}

//判断位置是否在蛇的上面
bool Snake::posInSnake(Point pos)
{
	for (unsigned int i = 0; i < bodyArray.size(); i++)
	{
		auto body = bodyArray.at(i);
		if (pos == Util::Grid2Pos(body->getX(), body->getY()))
		{
			return true;
		}
	}
	
	return false;
}

void Snake::Update()
{
	if (bodyArray.empty())
	{
		return;
	}

	for (int i = bodyArray.size() - 1; i >= 0; i--)
	{
		auto body = bodyArray.at(i);
		if (i==0)
		{
			body->sp->setRotation(getRotation());
			body->setY(OffSetGridByDir(body->getX(), body->getY(), direction).y);
			body->setX(OffSetGridByDir(body->getX(), body->getY(), direction).x);
		}
		else
		{
			auto front = bodyArray.at(i - 1);
			body->setY(front->getY());
			body->setX(front->getX());
		}

		//修改显示时的位置
		body->update();
	}
}

float Snake::getRotation()
{
	if (direction == RIGHT)
	{
		return RIGHT_ANGLE;
	}
	if (direction == LEFT)
	{
		return LEFT_ANGLE;
	}
	if (direction == UP)
	{
		return UP;
	}
	if (direction == DOWN)
	{
		return DOWN_ANGLE;
	}

	return 0;
}

Point Snake::OffSetGridByDir(int x, int y, Direction direction)
{
	if (direction==RIGHT)
	{
		return Vec2(x + 1, y);
	}
	if (direction == LEFT)
	{
		return Vec2(x - 1, y);
	}
	if (direction == UP)
	{
		return Vec2(x , y +1 );
	}
	if (direction == DOWN)
	{
		return Vec2(x , y-1);
	}

	return Point::ZERO;
}


bool Snake::collideApple()
{
	Rect r2(Util::Grid2Pos(this->bodyArray.at(0)->getX(), this->bodyArray.at(0)->getY()) - Point(GRIDSIZE / 2, GRIDSIZE / 2), Size(GRIDSIZE, GRIDSIZE));
	if (r2.containsPoint(AppleFactory::apple->getPosition()))
	{
		this->grow(false);
		return true;
	}
	return false;
}

bool Snake::collideSelf()
{
	if (bodyArray.size()==2)
	{
		return false;
	}
	auto head = bodyArray.at(0);
	for (unsigned int i = 1; i < bodyArray.size(); i++)
	{
		auto body = bodyArray.at(i);
		if (head->getX()==body->getX()&&head->getY()==body->getY())
		{
			return true;
		}
	}
	return false;
}

bool Snake::collideWall()
{
	Point headPos = Vec2(bodyArray.at(0)->getX(), bodyArray.at(0)->getY());

	if (headPos.x >= GRIDSUM|| headPos.x <= -GRIDSUM||headPos.y >= GRIDSUM||headPos.y <= -GRIDSUM)
	{
		return true;
	}
	return false;
}

void Snake::kill()
{
	//删除所有body节点
	for (unsigned int i = 0; i < bodyArray.size(); i++)
	{
		node->removeChild(bodyArray.at(i)->sp);
		//释放内存
		CC_SAFE_DELETE(bodyArray.at(i));
	}
	bodyArray.clear();
}

void Snake::Blink(std::function<void()> callback)
{
	for (unsigned int i = 0; i < bodyArray.size(); i++)
	{
		auto blink = Blink::create(3, 5);

		if (i==0)
		{
			auto seq = Sequence::create(blink, CallFunc::create(callback), NULL);
			bodyArray.at(i)->sp->runAction(seq);
		}
		else
		{
			bodyArray.at(i)->sp->runAction(blink);
		}
	}

}

void Snake::changeDirection(Direction dir)
{
	if ((dir == RIGHT || dir == LEFT) && (direction == RIGHT || direction == LEFT))
	{
		return;
	}
	if ((direction == UP || direction == DOWN) && (dir == UP || dir == DOWN))
	{
		return;
	}
	direction = dir;
}