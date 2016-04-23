#include "Tin.h"
#include <cmath>
using namespace std;

#define EARTH_RADIUS 6378.137
#define PI 3.141592654

//�Ƕ�ת����
double rad(double d)
{
	return d * PI / 180.0;
}
/*******************************************************************
* ���������ص�P1(lng1, lat1)��P2(lng2, lat2)�Ľ��ƴ���߾���(��λ km)
* double lng1: ��һ���ص�ľ���(�Ƕ�)
* double lat1: ��һ���ص��γ��(�Ƕ�)
* double lng2: �ڶ����ص�ľ���(�Ƕ�)
* double lat2: �ڶ����ص��γ��(�Ƕ�)
* ����ֵ: double, ������֮��Ľ��ƴ���߾��룬��λ km
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
