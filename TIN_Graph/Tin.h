#pragma once
#include"Node.h"
#include"LinkList.h"

using namespace std;

class TIN_Point :public Node
{
private:
	double lat, lng;//每个点的坐标值
	double lcDistance;//距离左下角的距离
	short nSingleEdgeCount;//单边计数
	myList *edgeList;//边表指针

public:
	TIN_Point() :lat(0), lng(0), lcDistance(0) { edgeList = NULL; }
	TIN_Point(int _id, double _x, double _y);

	
	//获取和修改id的函数
	int getID() { return id; }
	void setID(int _id) { id = _id; }


	//获取坐标的函数
	double getLat() { return lat; }
	double getLng () { return lng; }

	double sortSeed() { return lcDistance; }

	myList* getEdgeList() { return edgeList; }
	virtual void printData() { cout << id << " " << lat << " " << lng << endl; }
};

class TIN_Edge :public Node
{
private:
	TIN_Point *pPoint;//该边另一点的指针
	short nCount;//同一条边最多被使用两次
public:
	TIN_Edge() { nCount = 0; pPoint = NULL; }
	TIN_Edge(TIN_Point *_Point, int nCO) { pPoint = _Point; nCount = nCO; }
};

class Triangle :public Node
{
private:
	TIN_Point * pVertexT[3];//三角形顶点指针
public:
	Triangle(int _id, TIN_Point*, TIN_Point*, TIN_Point*);
	~Triangle();
	double getArea();//计算每个三角形的面积
	virtual void printData();
};


class TIN_Graph
{
private:
	myList lPoint;//点集
	myList lEdge;//边集
	myList lTriangle;//三角集

	int nAmount;//总共的点数

	bool * visited;//访问数组，在最短路算法中发挥作用
public:
	int * dist;//起始点点到其它各点的距离
	TIN_Graph();
	~TIN_Graph();
};