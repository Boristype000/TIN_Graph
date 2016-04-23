#pragma once
#include"Node.h"
#include"LinkList.h"

using namespace std;

class TIN_Point :public Node
{
private:
	double lat, lng;//ÿ���������ֵ
	double lcDistance;//�������½ǵľ���
	short nSingleEdgeCount;//���߼���
	myList *edgeList;//�߱�ָ��

public:
	TIN_Point() :lat(0), lng(0), lcDistance(0) { edgeList = NULL; }
	TIN_Point(int _id, double _x, double _y);

	
	//��ȡ���޸�id�ĺ���
	int getID() { return id; }
	void setID(int _id) { id = _id; }


	//��ȡ����ĺ���
	double getLat() { return lat; }
	double getLng () { return lng; }

	double sortSeed() { return lcDistance; }

	myList* getEdgeList() { return edgeList; }
	virtual void printData() { cout << id << " " << lat << " " << lng << endl; }
};

class TIN_Edge :public Node
{
private:
	TIN_Point *pPoint;//�ñ���һ���ָ��
	short nCount;//ͬһ������౻ʹ������
public:
	TIN_Edge() { nCount = 0; pPoint = NULL; }
	TIN_Edge(TIN_Point *_Point, int nCO) { pPoint = _Point; nCount = nCO; }
};

class Triangle :public Node
{
private:
	TIN_Point * pVertexT[3];//�����ζ���ָ��
public:
	Triangle(int _id, TIN_Point*, TIN_Point*, TIN_Point*);
	~Triangle();
	double getArea();//����ÿ�������ε����
	virtual void printData();
};


class TIN_Graph
{
private:
	myList lPoint;//�㼯
	myList lEdge;//�߼�
	myList lTriangle;//���Ǽ�

	int nAmount;//�ܹ��ĵ���

	bool * visited;//�������飬�����·�㷨�з�������
public:
	int * dist;//��ʼ��㵽��������ľ���
	TIN_Graph();
	~TIN_Graph();
};