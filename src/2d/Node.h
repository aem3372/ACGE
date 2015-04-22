#include "base/BaseStruct.h"

class Node
{
public:
	int getID();
	Vec2 getPosition();	
private:
	Vec2 pos;
	int id;
};