#include "Tin.h"
#include <cmath>
#include<cassert>
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
	double radLat2 = rad(Point2->getLat());
	double radLon1 = rad(Point1->getLng());
	double radLon2 = rad(Point2->getLng());
	double a = radLat1 - radLat2;
	double b = radLon1 - radLon2;

	double s = 2 * asinf(sqrtf(sin(a / 2)*sin(a / 2) + cos(radLat1)*cos(radLat2)*sin(b / 2)*sin(b / 2)));
	s = s * EARTH_RADIUS;

	return s;

	/*double dY = Point1->getLng() - Point2->getLng();
	double dX = Point1->getLat() - Point2->getLat();
	double s = sqrt(pow(dY, 2) + pow(dX, 2));
	return s;*/
}


double getCos3Pts(TIN_Point *p1, TIN_Point *p2, TIN_Point *p3)
//���p2�Ƕȵ�cosֵ
{
	double s1 = getPtsDist_s(p2, p3);
	double s2 = getPtsDist_s(p1, p3);
	double s3 = getPtsDist_s(p1, p2);

	double co2 = (pow(s1, 2) + pow(s3, 2) - pow(s2, 2)) / (2 * s1*s3);

	return co2;
}

Triangle::Triangle(TIN_Point *_point1, TIN_Point *_point2, TIN_Point *_point3)
{
	pVertexT[0] = _point1;
	pVertexT[1] = _point2;
	pVertexT[2] = _point3;
}

Triangle::~Triangle()
{
	for (int i = 0; i < 3; i++)
	{
		if (pVertexT[i] != NULL)
		{
			delete pVertexT[i];
			pVertexT[i] = NULL;
		}
	}
}

void Triangle::getVertex(TIN_Point *&_p1, TIN_Point *&_p2, TIN_Point *&_p3)
{
	_p1 = pVertexT[0];
	_p2 = pVertexT[1];
	_p3 = pVertexT[2];
}

double Triangle::getArea()
{
	return 0.0;
}

void Triangle::printData()
{
	cout << "Point1(" << pVertexT[0]->getLat() << "," << pVertexT[0]->getLng() << ")"<<"["<<pVertexT[0]->getID()<<"] "
		<< "Point2(" << pVertexT[1]->getLat() << "," << pVertexT[1]->getLng() << ")"<<"[" << pVertexT[1]->getID() << "] "
		"Point3(" << pVertexT[2]->getLat() << "," << pVertexT[2]->getLng() << ")" <<"[" << pVertexT[2]->getID() << "] " << endl;
}

bool TIN_Graph::Delaunay(TIN_Point *_p1, TIN_Point *_p2, TIN_Point *_p3, TIN_Point *_p4)
{
	//׼��1��p4���ڱ�p1p2�ϣ��þ�γ�ȹ��ɵ�б�����ж�
	{
		double k1 = (_p4->getLat() - _p1->getLat()) / (_p4->getLng() - _p1->getLng());
		double k2 = (_p2->getLat() - _p1->getLat()) / (_p2->getLng() - _p1->getLng());
		if (k1 == k2)
		{
			return false;
		}
	}
	//׼��2��p4��p3�ڱ�p1p2������
	{
		double k = (_p2->getLng() - _p1->getLng())
				 / (_p2->getLat() - _p1->getLat());
		double b = _p1->getLng() - k*_p1->getLat();
		double r3 = k*_p3->getLat() - _p3->getLng() + b;
		double r4 = k*_p4->getLat() - _p4->getLng() + b;
		if (r3*r4 > 0)
		{
			return false;
		}

	}
	//׼��3��p4��p1,p2���ɱ�ʹ�ô���С��2
	{
		Node* pMove_n1 = _p1->getEdgeList().front();
		while (pMove_n1)
		{
			TIN_Edge * pMove = dynamic_cast<TIN_Edge*>(pMove_n1);
			if (pMove->getPoint() == _p4&&pMove->nCount >= 2)
			{
				return false;
			}
			pMove_n1 = pMove_n1->next;
		}

		Node *pMove_n2 = _p2->getEdgeList().front();
		while (pMove_n2)
		{
			TIN_Edge * pMove = dynamic_cast<TIN_Edge*>(pMove_n2);
			if (pMove->getPoint() == _p4&&pMove->nCount >= 2)
			{
				return false;
			}
			pMove_n2 = pMove_n2->next;
		}
	}
	//׼��4����p1p4p2���(��buildTIN�����б���ʵ�֣�
	return true;
}

TIN_Edge * TIN_Graph::findEdge(TIN_Point * pSource, TIN_Point * _pFind)
//��pSourceָ��ĵ�ı߱����ҵ���һ��ΪpFind�ıߣ������ظñ�
{
	Node* pMove_n = pSource->getEdgeList().front();
	while (pMove_n)
	{
		TIN_Edge* pMove = dynamic_cast<TIN_Edge*>(pMove_n);
		if (pMove->getPoint() == _pFind)
		{
			return pMove;
		}
		pMove_n = pMove_n->next;
	}
	return NULL;
}

void TIN_Graph::addPoint2EdgeList(TIN_Point *_p1, TIN_Point *_p2)
//��p2��ӽ�p1�ı߱���
{
	TIN_Edge* edge1 = findEdge(_p1, _p2);
	if (edge1 != NULL)
	{
		edge1->nCount++; return;
	}
	else
	{
		TIN_Edge *pInsert = new TIN_Edge(_p2, 1);
		_p1->getEdgeList().push_back(pInsert); 
	}

	Node *pMove_n = _p1->getEdgeList().front();
	while (pMove_n)
	{
		TIN_Edge* pMove = dynamic_cast<TIN_Edge*>(pMove_n);
		if (pMove->nCount != 2)
		{
			return;
		}
		else
		{
			pMove_n = pMove_n->next;
		}
	}
	_p1->isClose = true;
}

void TIN_Graph::sortPointList()
{
	plPoint.sort();
}

void TIN_Graph::initTri()
{
	//sortPointList();
	//�������½�����ĵ㣬��������ͷΪp1
	TIN_Point * p1 = dynamic_cast<TIN_Point*>(plPoint.front());
	//ʹ��dynamic_castת��ָ��


	//����������������p2;
	Node * pMove_n = plPoint.front()->next;
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
	pMove_n = plPoint.front()->next;
	TIN_Point *p3 = NULL;
	double dCosMin = 1.0;
	while (pMove_n != NULL)
	{
		TIN_Point * pMove = dynamic_cast<TIN_Point*>(pMove_n);
		if (pMove == p2)
		{
			pMove_n = pMove_n->next;
			continue;
		}
		if (getCos3Pts(p1, pMove, p2) <= dCosMin)
		{
			dCosMin = getCos3Pts(p1, pMove, p2);
			p3 = pMove;
		}
		pMove_n = pMove_n->next;
	}
	addPoint2EdgeList(p1, p2);
	addPoint2EdgeList(p2, p1);
	addPoint2EdgeList(p1, p3);
	addPoint2EdgeList(p3, p1);
	addPoint2EdgeList(p2, p3);
	addPoint2EdgeList(p3, p2);

	//��������push�����Ǽ���
	Triangle * pTri = new Triangle(p1, p2, p3);
	lTriangle.push_back(pTri);
	nTri++;

	edgeExpand(p1, p2, p3);
}

void TIN_Graph::triExpand(Triangle * _pTri)
{
	
	TIN_Point* p1, *p2, *p3;
	_pTri->getVertex(p1, p2, p3);
	edgeExpand(p2, p3, p1);
	edgeExpand(p3, p1, p2);
}

void TIN_Graph::edgeExpand(TIN_Point *_p1, TIN_Point *_p2, TIN_Point *_p3)
{
	TIN_Edge* pR = findEdge(_p1, _p2);
	if (pR->nCount >= 2)return;


	Node *pMove_n = plPoint.front();
	double dCosMin = 1.0;
	TIN_Point * _p4 = NULL;
	while (pMove_n)
	{
		TIN_Point * pMove = dynamic_cast<TIN_Point*>(pMove_n);

		if (pMove == _p1 || pMove == _p2 || pMove == _p3 || pMove->isClose)
		{
			pMove_n = pMove_n->next; continue;
		}
		if (Delaunay(_p1, _p2, _p3, pMove))
		{
			if (getCos3Pts(_p1, pMove, _p2) <= dCosMin)
			{
				_p4 = pMove;
				dCosMin = getCos3Pts(_p1, _p4, _p2);
			}
		}
		pMove_n = pMove_n->next;
	}
	if (_p4 == NULL)return;//���p4��Ϊ��ָ�룬Ҳ���ǲ�δ�ҵ����õ�p4��ֱ�ӷ���
	
	Triangle * newTri = new Triangle(_p1, _p2, _p4);
	lTriangle.push_back(newTri);
	nTri++;

	addPoint2EdgeList(_p1, _p2);
	addPoint2EdgeList(_p1, _p4);
	addPoint2EdgeList(_p2, _p1);
	addPoint2EdgeList(_p2, _p4);
	addPoint2EdgeList(_p4, _p1);
	addPoint2EdgeList(_p4, _p2);

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
	plPoint.push_back(_Point);
	//lPoint.push_back(_Point);
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
	Node * pMove_n = lTriangle.front();
	while (pMove_n)
	{
		Triangle* pMove = dynamic_cast<Triangle*>(pMove_n);
		triExpand(pMove);
		pMove_n = pMove_n->next;
	}


}

void TIN_Graph::printTri()
{
	Node *pMove_n = lTriangle.front();
	while (pMove_n)
	{
		Triangle *pMove = dynamic_cast<Triangle*>(pMove_n);
		pMove->printData();
		pMove_n = pMove_n->next;
	}
}

void TIN_Graph::printPoint()
{
	Node *pMove_n = plPoint.front();
	while (pMove_n)
	{
		TIN_Point *pMove = dynamic_cast<TIN_Point*>(pMove_n);
		pMove->printData();
		pMove_n = pMove_n->next;
	}
}

void TIN_Graph::printEdgeCount()
{
	Node *pMove_n = plPoint.front();
	while (pMove_n)
	{
		TIN_Point * pMove = dynamic_cast<TIN_Point*>(pMove_n);
		Node* pMove_ef = pMove->getEdgeList().front();
		while (pMove_ef)
		{
			TIN_Edge* pMove_e = dynamic_cast<TIN_Edge*>(pMove_ef);
			if (pMove_e->nCount)
			{
				cout << "(" << pMove->getID() << " -- ";
				cout << pMove_e->getPoint()->getID() << ")" << "[" << pMove_e->nCount << "] ";
			}
			pMove_ef = pMove_ef->next;
		}
		cout << endl;
		pMove_n = pMove_n->next;
	}
}

TIN_Point::TIN_Point(double _x, double _y)
{
	lat = _x;
	lng = _y;
	lcDistance = getPtsDist(0, 0, lat, lng);
	isClose = false;
}
