#pragma once
#include"Node.h"
#include"LinkList.h"

using namespace std;

class TIN_Point :public Node
{
private:
	double lat, lng;//ÿ���������ֵ
	myList edgeList;//�߱�ָ��

public:
	double lcDistance;//�������½ǵľ���
	short nSingleEdgeCount;//���߼���

	TIN_Point() :lat(0), lng(0), lcDistance(0) { nSingleEdgeCount = -1; }
	TIN_Point(int _id, double _x, double _y);
	~TIN_Point() {}
	
	//��ȡ���޸�id�ĺ���
	int getID() { return id; }
	void setID(int _id) { id = _id; }


	//��ȡ����ĺ���
	double getLat() { return lat; }
	double getLng () { return lng; }
	//�������Ӻ��������ظ��������������������
	double sortSeed() { return lcDistance; }

	myList &getEdgeList() { return edgeList; }
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
	~TIN_Edge() { delete pPoint; }
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
	//myList lEdge;//�߼�
	myList lTriangle;//���Ǽ�
	bool * visited;//�������飬�����·�㷨�з�������

	void sortPointList();//����ʹ�㼯�������½Ǿ�������ĺ���
	void initTri();//������һ��������


public:
	int * dist;//��ʼ��㵽��������ľ���
	int nPoint;//�ܹ��ĵ���
	int nTri;//�����θ���

	TIN_Graph();
	~TIN_Graph();

	void insertPoint(TIN_Point * _Point);
	void buildTIN();
};