#include "ACO.h"
#include<fstream>
#include<cassert>
#include<ctime>


void Ant::init()
{
	int from, to, ant;

	ifstream f1;

	f1.open("TSP.txt");

	//creating cities

	for (from = 0; from < MAX_CITIES; from++)
	{
		//randomly place cities
		/*
		cities[from].x = rand()%MAX_DIST;

		cities[from].y = rand()%MAX_DIST;
		*/
		f1 >> cities[from].x;
		f1 >> cities[from].y;

		cout << cities[from].x << " " << cities[from].y << endl;
		//printf("\n %d %d",cities[from].x, cities[from].y);
		for (to = 0; to<MAX_CITIES; to++)
		{
			dist[from][to] = 0.0;
			phero[from][to] = INIT_PHER;
		}
	}

	//computing distance

	for (from = 0; from < MAX_CITIES; from++)
	{
		for (to = 0; to < MAX_CITIES; to++)
		{
			if (to != from && dist[from][to] == 0.0)
			{
				//int xd = pow( abs(cities[from].x - cities[to].x), 2);
				//int yd = pow( abs(cities[from].y - cities[to].y), 2);
				//
				//dist[from][to] = sqrt(xd + yd);
				dist[from][to] = getPtsDist(cities[from].x, cities[from].y, cities[to].x, cities[to].y);
				dist[to][from] = dist[from][to];

			}
		}
	}


	//initializing the ANTs

	to = 0;
	for (ant = 0; ant < MAX_ANTS; ant++)
	{
		if (to == MAX_CITIES)
			to = 0;

		ants[ant].curCity = to++;

		for (from = 0; from < MAX_CITIES; from++)
		{
			ants[ant].tabu[from] = 0;
			ants[ant].path[from] = -1;
		}

		ants[ant].pathIndex = 1;
		ants[ant].path[0] = ants[ant].curCity;
		ants[ant].nextCity = -1;
		ants[ant].tourLength = 0;

		//loading first city into tabu list

		ants[ant].tabu[ants[ant].curCity] = 1;


	}
}

void Ant::restartAnts()
{
	int ant, i, to = 0;

	for (ant = 0; ant<MAX_ANTS; ant++)
	{
		if (ants[ant].tourLength < best)
		{
			best = ants[ant].tourLength;
			bestIndex = ant;
		}

		ants[ant].nextCity = -1;
		ants[ant].tourLength = 0.0;

		for (i = 0; i<MAX_CITIES; i++)
		{
			ants[ant].tabu[i] = 0;
			ants[ant].path[i] = -1;
		}

		if (to == MAX_CITIES)
			to = 0;

		ants[ant].curCity = to++;

		ants[ant].pathIndex = 1;
		ants[ant].path[0] = ants[ant].curCity;

		ants[ant].tabu[ants[ant].curCity] = 1;
	}
}

double Ant::antProduct(int from, int to)
{
	return((pow(phero[from][to], ALPHA) * pow((1.0 / dist[from][to]), BETA)));
}

int Ant::selectNextCity(int ant)
{
	int from, to;
	double denom = 0.0;

	from = ants[ant].curCity;

	for (to = 0; to<MAX_CITIES; to++)
	{
		if (ants[ant].tabu[to] == 0)
		{
			denom += antProduct(from, to);
		}
	}

	assert(denom != 0.0);

	do
	{
		double p;
		to++;

		if (to >= MAX_CITIES)
			to = 0;
		if (ants[ant].tabu[to] == 0)
		{
			p = antProduct(from, to) / denom;

			//printf("\n%lf %lf", (double)rand()/RAND_MAX,p);
			double x = ((double)rand() / RAND_MAX);
			if (x < p)
			{
				//printf("%lf %lf Yo!",p,x);

				break;
			}
		}
	} while (1);

	return to;
}

int Ant::simulateAnts()
{
	int k;
	int moving = 0;

	for (k = 0; k<MAX_ANTS; k++)
	{
		//checking if there are any more cities to visit

		if (ants[k].pathIndex < MAX_CITIES)
		{
			ants[k].nextCity = selectNextCity(k);
			ants[k].tabu[ants[k].nextCity] = 1;
			ants[k].path[ants[k].pathIndex++] = ants[k].nextCity;

			ants[k].tourLength += dist[ants[k].curCity][ants[k].nextCity];

			//handle last case->last city to first

			if (ants[k].pathIndex == MAX_CITIES)
			{
				ants[k].tourLength += dist[ants[k].path[MAX_CITIES - 1]][ants[k].path[0]];
			}

			ants[k].curCity = ants[k].nextCity;
			moving++;

		}
	}

	return moving;
}

void Ant::updateTrails()
{
	int from, to, i, ant;

	//Pheromone Evaporation

	for (from = 0; from<MAX_CITIES; from++)
	{
		for (to = 0; to<MAX_CITIES; to++)
		{
			if (from != to)
			{
				phero[from][to] *= (1.0 - RHO);

				if (phero[from][to]<0.0)
				{
					phero[from][to] = INIT_PHER;
				}
			}
		}
	}

	//Add new pheromone to the trails

	for (ant = 0; ant<MAX_ANTS; ant++)
	{
		for (i = 0; i<MAX_CITIES; i++)
		{
			if (i < MAX_CITIES - 1)
			{
				from = ants[ant].path[i];
				to = ants[ant].path[i + 1];
			}
			else
			{
				from = ants[ant].path[i];
				to = ants[ant].path[0];
			}

			phero[from][to] += (QVAL / ants[ant].tourLength);
			phero[to][from] = phero[from][to];

		}
	}

	for (from = 0; from < MAX_CITIES; from++)
	{
		for (to = 0; to<MAX_CITIES; to++)
		{
			phero[from][to] *= RHO;
		}
	}
}

void Ant::emitDataFile(int bestIndex)
{
	ofstream f1;
	f1.open("Data.txt");
	antType antBest(MAX_CITIES);
	antBest = ants[bestIndex];
	//f1<<antBest.curCity<<" "<<antBest.tourLength<<"\n";
	int i;
	for (i = 0; i<MAX_CITIES; i++)
	{
		f1 << antBest.path[i] << " ";
	}

	f1.close();

	f1.open("city_data.txt");
	for (i = 0; i<MAX_CITIES; i++)
	{
		f1 << cities[i].x << " " << cities[i].y << "\n";
	}
	f1.close();
}

void Ant::begin()
{
	int curTime = 0;

	cout << "S-ACO:";
	cout << "MaxTime=" << MAX_TIME;

	srand(time(NULL));

	init();

	while (curTime++ < MAX_TIME)
	{
		if (simulateAnts() == 0)
		{
			updateTrails();

			if (curTime != MAX_TIME)
				restartAnts();

			cout << "\n Time is " << curTime << "(" << best << ")";

		}
	}

	cout << "\nSACO: Best tour = " << best << endl << endl << endl;

	emitDataFile(bestIndex);
}
