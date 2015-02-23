#ifndef __ACGR_LOGIC_POINTTRANSFORMATOR__
#define __ACGR_LOGIC_POINTTRANSFORMATOR__

template<class T>
class PointTransformator
{
public:
	void init(T xres, T yres);
	void LT2LB(T x, T y, T* newx, T* newy);
	void LB2LT(T x, T y, T* newx, T* newy);	
private:
	T xres;
	T yres;
};

#include "private/point_transformator.cpp"

#endif