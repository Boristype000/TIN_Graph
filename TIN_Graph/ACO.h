#pragma once
#include"Tin.h"
using namespace std;

struct cityType {
	int x,y;
};

class antType
{
public:
	int curCity, nextCity, pathIndex;
	int *tabu;
	int *path;
	double tourLength;
	antType(int max_cities)
	{
		curCity = -1; nextCity = -1; pathIndex = -1;
		tabu = new int[max_cities]; 
		path = new int[max_cities];
		tourLength = -1.0;
	}
	~antType()
	{
		if (tabu != nullptr)
		{
			delete[] tabu;
		}
		if (path != nullptr)
		{
			delete[] path;
		}
	}
};

class Ant
{
private:
	int MAX_CITIES;
	int MAX_DIST;
	int MAX_TOUR;
	int MAX_ANTS;

	double ALPHA;
	double BETA;
	double RHO;
	double QVAL;
	int MAX_TOURS;
	int MAX_TIME;
	double INIT_PHER;

	double **dist;
	double **phero;

	cityType *cities;
	antType *ants;

	double best = (double)MAX_TOUR;//!!
	int bestIndex;

	void init();
	void restartAnts();
	double antProduct(int from, int to);
	int selectNextCity(int ant);
	int simulateAnts();
	void updateTrails();
	void emitDataFile(int bestIndex);

public:
	Ant(int _alpha, int _beta, int _rho, int _qval);

	void inputDistMatrix(double **);

	void begin();
};