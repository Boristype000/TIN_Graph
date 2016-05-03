#pragma once
#include"Node.h"
#include"LinkList.h"

using namespace std;

class TIN_Point :public Node
{
private:
	double lat, lng;//每个点的坐标值
	myList edgeList;//边表
	bool Closed;//是否为闭合点的标志


public:
	double lcDistance;//距离左下角的距离

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

	double sortSeed() { return lcDistance; }//排序种子函数，返回该派生类用于排序的依据

	myList &getEdgeList() { return edgeList; }
	void printData();

	const bool &isClose();
	void Closeit() { Closed = true; }
};

class TIN_Edge :public Node
{
private:
	TIN_Point *oriPoint;
	TIN_Point *pPoint;//该边另一点的指针
	double length;

public:
	short nCount;//同一条边最多被使用两次
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
	double nArea;//该三角形面积
	TIN_Point * pVertexT[3];//三角形顶点指针
	double calArea();//计算每个三角形的面积
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
	myList plPoint;//点集
	myList lTriangle;//三角集
	bool * visited;//访问数组，在最短路算法中发挥作用

	bool Delaunay(TIN_Point *, TIN_Point *, TIN_Point *, TIN_Point *);
	//用于判断四点是否满足Delaunay准则
	TIN_Edge * findEdge(TIN_Point * pSource, int findID);
	void addPoint2EdgeList(TIN_Point *p1, TIN_Point *p2);
	void sortPointList();//用来使点集按到右下角距离排序的函数
	void initTri();//创建第一个三角形
	void triExpand(Triangle *);//三角形拓展函数，传入参数为三角形号
	void edgeExpand(TIN_Point*, TIN_Point*, TIN_Point*);//边拓展函数，p1p2待扩展


public:
	int * dist;//起始点点到其它各点的距离
	int nPoint;//总共的点数
	int nTri;//三角形个数

	TIN_Graph();
	~TIN_Graph();

	void insertPoint(TIN_Point * _Point);
	void buildTIN();

	void printTri();
	void printPoint();
	void printEdgeCount();
	void printUnUsedPoint();
};