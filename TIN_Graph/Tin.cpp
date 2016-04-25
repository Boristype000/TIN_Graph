#include "Tin.h"
#include <cmath>
using namespace std;

#define EARTH_RADIUS 6378.137
#define PI 3.141592654

const int INF = 0x3f3f3f3f;

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

double getPtsDist_s(TIN_Point *Point1,TIN_Point *Point2)
{
	double radLat1 = rad(Point1->getLat());
	double radLat2 = rad(Point1->getLng());
	double radLon1 = rad(Point2->getLat());
	double radLon2 = rad(Point2->getLng());
	double a = radLat1 - radLat2;
	double b = radLon1 - radLon2;

	double s = 2 * asinf(sqrtf(sin(a / 2)*sin(a / 2) + cos(radLat1)*cos(radLat2)*sin(b / 2)*sin(b / 2)));
	s = s * EARTH_RADIUS;

	return s;
}

double getCos3Pts(TIN_Point *p1, TIN_Point *p2, TIN_Point *p3)
{
	double s1 = getPtsDist_s(p2, p3);
	double s2 = getPtsDist_s(p1, p3);
	double s3 = getPtsDist_s(p1, p2);

	double co2 = (pow(s1, 2) + pow(s3, 2) - pow(s2, 2)) / (2 * s1*s3);

	return co2;
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
	for (int i = 0; i < 3; i++)
	{
		delete pVertexT[i];
	}
}

double Triangle::getArea()
{
	return 0.0;
}

void Triangle::printData()
{
}

void TIN_Graph::sortPointList()
{
	lPoint.sort();
}

void TIN_Graph::initTri()
{
	//�������½�����ĵ㣬��������ͷΪp1
	TIN_Point * p1 = dynamic_cast<TIN_Point*>(lPoint.front());
	//ʹ��dynamic_castת��ָ��


	//����������������p2;
	Node * pMove_n = lPoint.front()->next;
	TIN_Point * p2 = NULL;
	double dMin = INF;
	while (pMove_n != NULL)
	{
		TIN_Point * pMove = dynamic_cast<TIN_Point*>(pMove_n);
		if (getPtsDist_s(p1, pMove) < dMin)
		{
			p2 = pMove;
			dMin = getPtsDist_s(p1, pMove);
		}
		pMove_n = pMove_n->next;
	}

	//�ҵ�p3,���ݽ�p1p3p2���Ҳ���Ǹý�����ֵ��С
	pMove_n = lPoint.front()->next;
	TIN_Point *p3 = NULL;
	double dCosMin = 1.0;
	while (pMove_n != NULL)
	{
		TIN_Point * pMove = dynamic_cast<TIN_Point*>(pMove_n);
		if (pMove == p2)pMove_n = pMove_n->next;
		if (getCos3Pts(p1, pMove, p2) < dCosMin)
		{
			dCosMin = getCos3Pts(p1, pMove, p2);
			p3 = pMove;
		}
		pMove_n = pMove_n->next;
	}
	//��������ı߱����µĿռ�
	p1->getEdgeList = new myList;
	p2->getEdgeList = new myList;
	p3->getEdgeList = new myList;
	//��ʼ�������ߣ���������push��������ı߱��С�
	//�Ƿ���Ҫidֵ��
	TIN_Edge *s1 = new TIN_Edge(p1, 1);
	TIN_Edge *s2 = new TIN_Edge(p2, 1);
	TIN_Edge *s3 = new TIN_Edge(p3, 1);

	p1->getEdgeList()->push_back(s2);
	p1->getEdgeList()->push_back(s3);

	p2->getEdgeList()->push_back(s1);
	p2->getEdgeList()->push_back(s3);

	p3->getEdgeList()->push_back(s1);
	p3->getEdgeList()->push_back(s2);
	//��������push�����Ǽ���
	Triangle * pTri = new Triangle(nTri, p1, p2, p3);
	lTriangle.push_back(pTri);



	

}

TIN_Graph::TIN_Graph()
{
	visited = NULL;
	dist = NULL;
}

TIN_Graph::~TIN_Graph()
{
	delete[] visited;
	delete[] dist;
	nPoint = 0;
	nTri = 0;
}

void TIN_Graph::insertPoint(TIN_Point * _Point)
{
	lPoint.push_back(_Point);
	nPoint++;//��ʱ��Ϊû�������ظ��ĵ�
}

void TIN_Graph::buildTIN()
{
	if (nPoint < 3)
	{
		cout << "Point number is less than 3!" << endl;
		return;
	}
	initTri();

}

TIN_Point::TIN_Point(int _id, double _x, double _y)
{
	id = _id;
	lat = _x;
	lng = _y;
	lcDistance = getPtsDist(0, 0, lat, lng);
}
