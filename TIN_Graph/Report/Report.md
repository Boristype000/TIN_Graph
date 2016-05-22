# **《数据结构》实验报告**

## 第二次作业

### 1.  实验要求

无向图和最短路径查找，要求如下:

1. 从提供的POI点文件(zhuhai_POIs.csv)中随机选取N个点构建TIN网;
2. 在这N个点中使用者可选择任意M个点，输出M个点的坐标;
3. 输出以最短路径经过这M个点的点位顺序，和最短路径的长度;
4. 要求N>=1000,M>=20 && M<=N, 程序支持输出以上每一步的运行时间;

### 2. 实验过程

#### 2.1 构建TIN网

构建TIN网的方法有很多，例如分治算法、三角网生长算法、逐点插入算法等等，本报告采用的方法为优化的三角网生长算法。



存放每个点信息的容器 `TIN_Point`

```c++
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
	const double &getLat() { return lat; }
	const double &getLng() { return lng; }
	double sortSeed() { return lcDistance; }
};
```

#### 2.2 随机选点



#### 2.3 最短路径









