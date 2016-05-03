#pragma once
#include"Node.h"
#include"LinkList.h"

using namespace std;

class TIN_Point :public Node
{
private:
	double lat, lng;//ÿ���������ֵ
	myList edgeList;//�߱�
	bool Closed;//�Ƿ�Ϊ�պϵ�ı�־


public:
	double lcDistance;//�������½ǵľ���

	TIN_Point()
		:lat(0), lng(0), lcDistance(0)
	{
		Closed = false;
	}
	TIN_Point(double _x, double _y);
	~TIN_Point() {}

	const int &getID() { return id; }
	void setID(int _id) { id = _id; }

	const double &getLat() { return lat; }
	const double &getLng() { return lng; }

	double sortSeed() { return lcDistance; }//�������Ӻ��������ظ��������������������

	myList &getEdgeList() { return edgeList; }
	void printData();

	const bool &isClose();
	void Closeit() { Closed = true; }
};

class TIN_Edge :public Node
{
private:
	TIN_Point *oriPoint;
	TIN_Point *pPoint;//�ñ���һ���ָ��
	double length;

public:
	short nCount;//ͬһ������౻ʹ������
	TIN_Point* getPoint()
	{
		return pPoint;
	}
	TIN_Edge();
	TIN_Edge(TIN_Point* _ori, TIN_Point *_Point);
	~TIN_Edge();
};

class Triangle :public Node
{
private:
	double nArea;//�����������
	TIN_Point * pVertexT[3];//�����ζ���ָ��
	double calArea();//����ÿ�������ε����
public:
	Triangle(TIN_Point*, TIN_Point*, TIN_Point*);
	~Triangle();
	double getArea() { return nArea; }
	void getVertex(TIN_Point*&, TIN_Point*&, TIN_Point*&);
	void printData();
};


class TIN_Graph
{
private:
	myList plPoint;//�㼯
	myList lTriangle;//���Ǽ�
	bool * visited;//�������飬�����·�㷨�з�������

	bool Delaunay(TIN_Point *, TIN_Point *, TIN_Point *, TIN_Point *);
	//�����ж��ĵ��Ƿ�����Delaunay׼��
	TIN_Edge * findEdge(TIN_Point * pSource, int findID);
	void addPoint2EdgeList(TIN_Point *p1, TIN_Point *p2);
	void sortPointList();//����ʹ�㼯�������½Ǿ�������ĺ���
	void initTri();//������һ��������
	void triExpand(Triangle *);//��������չ�������������Ϊ�����κ�
	void edgeExpand(TIN_Point*, TIN_Point*, TIN_Point*);//����չ������p1p2����չ


public:
	int * dist;//��ʼ��㵽��������ľ���
	int nPoint;//�ܹ��ĵ���
	int nTri;//�����θ���

	TIN_Graph();
	~TIN_Graph();

	void insertPoint(TIN_Point * _Point);
	void buildTIN();

	void printTri();
	void printPoint();
	void printEdgeCount();
	void printUnUsedPoint();
};