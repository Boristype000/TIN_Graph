#pragma once
#include"Node.h"
#include"LinkList.h"

using namespace std;

class TIN_Point :public Node
{
private:
	double lat, lng;//每个点的坐标值
	myList edgeList;//边表指针

public:
	double lcDistance;//距离左下角的距离
	short nSingleEdgeCount;//单边计数

	TIN_Point()
		:lat(0), lng(0), lcDistance(0)
	{
		nSingleEdgeCount = -1;
	}
	TIN_Point(int _id, double _x, double _y);
	~TIN_Point() {}


	int getID() { return id; }
	void setID(int _id) { id = _id; }


	double getLat() 
	{
		return lat;
	}
	double getLng ()
	{
		return lng;
	}
	
	double sortSeed()
	{ return lcDistance; }//排序种子函数，返回该派生类用于排序的依据

	myList &getEdgeList() 
	{ 
		return edgeList;
	}
	void printData()
	{
		cout << id << " " << lat << " " << lng << endl;
	}
};

class TIN_Edge :public Node
{
private:
	TIN_Point *pPoint;//该边另一点的指针


public:
	short nCount;//同一条边最多被使用两次
	const TIN_Point* getPoint()
	{
		return pPoint;
	}
	TIN_Edge() 
	{
		nCount = 0; pPoint = NULL;
	}
	TIN_Edge(TIN_Point *_Point, int nCO) 
	{
		pPoint = _Point; nCount = nCO; 
	}
	~TIN_Edge()
	{
		if (pPoint != NULL)
		{
			delete pPoint;
		}
		pPoint = NULL;
	}
};

class Triangle :public Node
{
private:
	TIN_Point * pVertexT[3];//三角形顶点指针
public:
	Triangle(TIN_Point*, TIN_Point*, TIN_Point*);
	~Triangle();

	void getVertex(TIN_Point*&, TIN_Point*&, TIN_Point*&);
	double getArea();//计算每个三角形的面积
	void printData();
};


class TIN_Graph
{
private:
	myList lPoint;//点集
	//myList lEdge;//边集
	myList lTriangle;//三角集
	bool * visited;//访问数组，在最短路算法中发挥作用

	bool Delaunay(TIN_Point *, TIN_Point *, TIN_Point *, TIN_Point *);
		//用于判断四点是否满足Delaunay准则
	TIN_Edge * findEdge(TIN_Point * pSource, TIN_Point * _pPoint);
	void addPoint2Edge(TIN_Point *p1,TIN_Point *p2);
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
};