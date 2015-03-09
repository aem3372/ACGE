template<class T>
void PointTransformator<T>::init(T xres, T yres)
{
	this->xres = xres;
	this->yres = yres;
}

template<class T>
void PointTransformator<T>::LT2LB(T x, T y, T* newx, T* newy)
{
	*newx = x;
	*newy = yres - y;
}

template<class T>
void PointTransformator<T>::LB2LT(T x, T y, T* newx, T* newy)
{
	*newx = x;
	*newy = yres - y;
}
