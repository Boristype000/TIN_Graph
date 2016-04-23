#include "Tin.h"
#include <cmath>
using namespace std;

#define EARTH_RADIUS 6378.137
#define PI 3.141592654

//角度转弧度
double rad(double d)
{
	return d * PI / 180.0;
}
/*******************************************************************
* 返回两个地点P1(lng1, lat1)和P2(lng2, lat2)的近似大地线距离(单位 km)
* double lng1: 第一个地点的经度(角度)
* double lat1: 第一个地点的纬度(角度)
* double lng2: 第二个地点的经度(角度)
* double lat2: 第二个地点的纬度(角度)
* 返回值: double, 两个点之间的近似大地线距离，单位 km
*******************************************************************/
double getPtsDist(double lat1, double lng1, double lat2, double lng2)
{
	double radLat1 = rad(lat1);
	double radLat2 = rad(lat2);
	double radLon1 = rad(lng1);
	double radLon2 = rad(lng2);
	double a = radLat1 - radLat2;
	double b = radLon1 - radLon2;

	double s = 2 * asinf(sqrtf(sin(a / 2)*sin(a / 2) + cos(radLat1)*cos(radLat2)*sin(b / 2)*sin(b / 2)));
	s = s * EARTH_RADIUS;

	return s;
}


Triangle::Triangle(int _id, TIN_Point *_point1, TIN_Point *_point2, TIN_Point *_point3)
{
	id = _id;
	pVertexT[0] = _point1;
	pVertexT[1] = _point2;
	pVertexT[2] = _point3;
}

Triangle::~Triangle()
{

}

double Triangle::getArea()
{
	return 0.0;
}

void Triangle::printData()
{
}

TIN_Graph::TIN_Graph()
{
}

TIN_Graph::~TIN_Graph()
{

}

TIN_Point::TIN_Point(int _id, double _x, double _y)
{
	id = _id;
	lat = _x;
	lng = _y;
	lcDistance = getPtsDist(0, 0, lat, lng);
}
