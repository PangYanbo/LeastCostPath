#pragma once
#ifndef __CHelloWorld__Graph__  
#define __CHelloWorld__Graph__  

#include <iostream>  
#include <list>
#include<vector>

struct vect3d {
	float   x, y, z;
};


struct node {
	int x, y;
	double cost;
	double todes;
	int connected;
	int inList;
	int inPath;
	int xy[2];

	bool operator <(const node& a)const 
	{
		return this->todes < a.todes;
	}

	bool operator == (const node& a)const
	{
		return this->todes == a.todes;
	}

};


struct costsurface {
	node cell[802][802];
};


class surface {
	int i, j;
	costsurface cs;
public:
	surface();
	void creatsurface(float v[802][802]);
	void print();
	void printresult();
	void calcost(int xas, int yas, float xus, float yus, float v1[802][802], float v2[802][802]);
	void dijkstra(int _x, int _y);
	void leastcostpath(int _x, int _y, int _xs, int _ys);
};


#endif 