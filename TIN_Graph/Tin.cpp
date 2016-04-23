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


TIN_Edge::TIN_Edge()
{
	pVertexE[0] = pVertexE[1] = NULL; 
	pTri = NULL; 
	nTri = -1;
	length = -1;
}

TIN_Edge::TIN_Edge(int _id, TIN_Point *_Point1, TIN_Point *_Point2)
{
	id = _id;
	pVertexE[0] = _Point1;
	pVertexE[1] = _Point2;
	length = getPtsDist(pVertexE[0]->getLat(), pVertexE[0]->getLng, pVertexE[1]->getLat(), pVertexE[1]->getLng);
}



TIN_Edge::~TIN_Edge()
{
	if (pVertexE[0] != NULL)
	{
		delete pVertexE[0];
		delete pVertexE[1];
	}
	if (pTri != NULL)
	{
		delete pTri;
	}
}

void TIN_Edge::printData()
{
	cout << "�˵�һ\t" << "id:" << pVertexE[0]->getID() << "\t" << "X����Ϊ�� "
		<< pVertexE[0]->getLat() << "\t" << "Y����Ϊ�� " << pVertexE[0]->getLng() << endl;
	cout << "�˵�һ\t" << "id:" << pVertexE[1]->getID() << "\t" << "X����Ϊ�� "
		<< pVertexE[1]->getLat() << "\t" << "Y����Ϊ�� " << pVertexE[1]->getLng() << endl;

}

Triangle::Triangle()
{
	pVertexT[0] = pVertexT[1] = pVertexT[2] = NULL;
	pEdgeT[0] = pEdgeT[1] = pEdgeT[2] = NULL;
}

Triangle::Triangle(int _id, TIN_Edge * _edge1, TIN_Edge * _edge2, TIN_Edge * _edge3)
{
	id = _id;

	pEdgeT[0] = _edge1;
	pEdgeT[1] = _edge2;
	pEdgeT[2] = _edge3;

	pVertexT[0] = pEdgeT[0]->getVertex1();
	pVertexT[1] = pEdgeT[0]->getVertex2();
	pVertexT[2] = 
		(	
			pEdgeT[1]->getVertex1() == pVertexT[0] ||
			pEdgeT[1]->getVertex1() == pVertexT[1]?
			pEdgeT[1]->getVertex2():
			pEdgeT[1]->getVertex1()
		);



	
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

TIN_Point::TIN_Point(int _id, double _x, double _y)
{
	id = _id;
	lat = _x;
	lng = _y;
	lcDistance = getPtsDist(0, 0, lat, lng);
}
