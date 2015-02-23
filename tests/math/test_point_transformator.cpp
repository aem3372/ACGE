#include "math/point_transformator.h"
#include "assert.h"
#include "stdio.h"
int main()
{
	PointTransformator<int> trans;
	trans.init(1024,768);
	int x, y;
	
	trans.LB2LT(200,100,&x,&y);
	assert(x==200 && y==668);

	trans.LT2LB(200,100,&x,&y);
	assert(x==200 && y==668);
	return 0;
}