#include <cstring>
#include <cstdlib>
#include <cmath>
#include <list>
#include <iostream>
#include "lcpa.h"
#include<vector>
#include<algorithm>

using namespace std;


list<node> near(costsurface cs, int _x, int _y) {
	list<node>near;
	near.push_front(cs.cell[_x - 1][_y - 1]);
	near.push_front(cs.cell[_x - 1][_y]);
	near.push_front(cs.cell[_x - 1][_y + 1]);
	near.push_front(cs.cell[_x][_y + 1]);
	near.push_front(cs.cell[_x][_y - 1]);
	near.push_front(cs.cell[_x + 1][_y]);
	near.push_front(cs.cell[_x + 1][_y - 1]);
	near.push_front(cs.cell[_x + 1][_y + 1]);
	return near;
}
vector<int> toDes(node centre, list<node>_near) {
	list<node>::iterator it;
	vector<int> A;
	float temp;
	int dis = 100000000000;
	int m, n;
	node temporal;
	for (it = _near.begin(); it != _near.end(); it++)
	{
		temporal = *it;
		if (it->inList > 0 && (it->x - centre.x)*(it->y - centre.y) == 0)
		{
			temp = centre.cost*0.5 + it->cost*0.5 + it->todes;
			if (dis > temp) 
			{
				dis = temp;
				m = it->x;
				n = it->y;
			}
		}
		else if (it->inList >0  && abs((it->x - centre.x)*(it->y - centre.y == 1)))
		{
			temp = centre.cost*0.707 + it->cost*0.707 + it->todes;
			if (dis > temp)
			{
				dis = temp;
				m = it->x;
				n = it->y;
            }
		}
	}
	A.push_back(dis);
	A.push_back(m);
	A.push_back(n);
	return A;
}

node LeastCostNode(vector<node>_near) {
	vector<node>::iterator it;
	float min = 1000000000000;
	node temp;
	for (it = _near.begin(); it != _near.end(); it++) {
		temp = *it;
		if (min > temp.todes)min = temp.todes;
	}
	for (it = _near.begin(); it != _near.end(); it++) {
		temp = *it;
		if (min == temp.todes)break;
	}
	return temp;

}


vect3d normv(vect3d tri[3]) {

	float   vlen;
	vect3d   nv;

	nv.x = (tri[0].y - tri[1].y) * (tri[0].z + tri[1].z) + (tri[1].y - tri[2].y) * (tri[1].z + tri[2].z) + (tri[2].y - tri[0].y) * (tri[2].z + tri[0].z);
	nv.y = (tri[0].z - tri[1].z) * (tri[0].x + tri[1].x) + (tri[1].z - tri[2].z) * (tri[1].x + tri[2].x) + (tri[2].z - tri[0].z) * (tri[2].x + tri[0].x);
	nv.z = (tri[0].x - tri[1].x) * (tri[0].y + tri[1].y) + (tri[1].x - tri[2].x) * (tri[1].y + tri[2].y) + (tri[2].x - tri[0].x) * (tri[2].y + tri[0].y);
	vlen = sqrt(nv.x * nv.x + nv.y * nv.y + nv.z * nv.z);
	nv.x = nv.x / vlen;
	nv.y = nv.y / vlen;
	nv.z = nv.z / vlen;

	return nv;
}


surface::surface(){
		for (i = 1; i < 801; i++) {
			for (j = 1; j < 801; j++) {
				cs.cell[i][j].x = i;
				cs.cell[i][j].y = j;
				cs.cell[i][j].cost = 0;
				cs.cell[i][j].connected = 0;
				cs.cell[i][j].inList = 0;
				cs.cell[i][j].inPath = 0;
				cs.cell[i][j].todes = 10000000000000000;
			}
		}
	}


void  surface::creatsurface(float v[802][802]){
	for (i = 1; i < 801; i++) {
		for (j = 1; j < 801; j++) {

			cs.cell[i][j].cost = v[i][j];
			
		}
	}
	for (j = 1; j <= 800; j++) {
		cs.cell[0][j].cost = 1000000000000000;
		cs.cell[801][j].cost = 1000000000000000;
	}

	for (i = 1; i <= 800; i++) {
		cs.cell[i][0].cost = 1000000000000000;
		cs.cell[i][801].cost = 1000000000000000;
	}

	cs.cell[0][0].cost = 1000000000000000;
	cs.cell[801][0].cost = 1000000000000000;
	cs.cell[0][801].cost = 1000000000000000;
	cs.cell[801][801].cost = 1000000000000000;
}

void surface::calcost(int xas, int yas, float xus, float yus, float _v1[802][802], float _v2[802][802]) {
	vect3d  slopev;		
	vect3d  tri[3];		
	vect3d  nv[5];		
	float   vlen;		
	for (int i = 1; i <= xas; i++) {
		for (int j = 1; j <= yas; j++) {
			tri[0].x = 0;
			tri[0].y = 0;
			tri[0].z = _v1[i][j];

			tri[1].x = 0;
			tri[1].y = -yus;
			tri[1].z = _v1[i][j - 1];
			tri[2].x = -xus;
			tri[2].y = 0;
			tri[2].z = _v1[i - 1][j];
			nv[1] = normv(tri);

			tri[1].x = xus;
			tri[1].y = 0;
			tri[1].z = _v1[i + 1][j];
			tri[2].x = 0;
			tri[2].y = -yus;
			tri[2].z = _v1[i][j - 1];
			nv[2] = normv(tri);

			tri[1].x = 0;
			tri[1].y = yus;
			tri[1].z = _v1[i][j + 1];
			tri[2].x = xus;
			tri[2].y = 0;
			tri[2].z = _v1[i + 1][j];
			nv[3] = normv(tri);

			tri[1].x = -xus;
			tri[1].y = 0;
			tri[1].z = _v1[i - 1][j];
			tri[2].x = 0;
			tri[2].y = yus;
			tri[2].z = _v1[i][j + 1];
			nv[4] = normv(tri);

			nv[0].x = nv[1].x + nv[2].x + nv[3].x + nv[4].x;
			nv[0].y = nv[1].y + nv[2].y + nv[3].y + nv[4].y;
			nv[0].z = nv[1].z + nv[2].z + nv[3].z + nv[4].z;

			vlen = sqrt(nv[0].x * nv[0].x + nv[0].y * nv[0].y + nv[0].z * nv[0].z);

			if (vlen == 0) {
				slopev.x = 0;
				slopev.y = 0;
				slopev.z = -1;
			}
			else {
				slopev.x = nv[0].x / vlen;
				slopev.y = nv[0].y / vlen;
				slopev.z = nv[0].z / vlen;
			}

			_v2[i][j] = 1.39/exp(abs((-slopev.z)+0.05)*(-3.5));

		}
	}
}


void surface::print(){
	for (i = 1; i < 801; i++) {
		for (j = 1; j < 801; j++) {

		cout << cs.cell[i][j].inPath << "\n";

		}
	}
}

void surface::printresult() {
	for (i = 1; i < 801; i++) {
		for (j = 1; j < 801; j++) {

		std::cout << cs.cell[i][j].connected << "\n";

		}
	}
}


void surface::dijkstra(int _x, int _y) {
	int _i, _j;
	int k = 1;
	node incon;
	list<node>connected;
	vector<node>::iterator it;
	vector<node>inconnect;
	vector<int>A;
	vector<int>::iterator ts;
	
	cs.cell[_x][_y].inList = 1;
	cs.cell[_x][_y].todes = 0;
	cs.cell[_x - 1][_y - 1].connected = 1;
	cs.cell[_x - 1][_y].connected = 1;
	cs.cell[_x - 1][_y + 1].connected = 1;
	cs.cell[_x][_y - 1].connected = 1;
	cs.cell[_x][_y + 1].connected = 1;
	cs.cell[_x + 1][_y - 1].connected = 1;
	cs.cell[_x + 1][_y].connected = 1;
	cs.cell[_x + 1][_y + 1].connected = 1;
	
	while (k <= 640000)
	{
		for (int i = 1; i <= 800; i++) {
			for (int j = 1; j <= 800; j++) {
				if (cs.cell[i][j].connected == 1 && cs.cell[i][j].inList == 0) {
					connected = near(cs, i, j);
					 A = toDes(cs.cell[i][j], connected);
					 ts = A.begin();
					 cs.cell[i][j].todes = *ts;
					 ts++;
					 cs.cell[i][j].xy[0] = *ts;
					 ts++;
					 cs.cell[i][j].xy[1] = *ts;
					inconnect.push_back(cs.cell[i][j]);
				}
			}
		}

		sort(inconnect.begin(), inconnect.end());
		inconnect.erase(unique(inconnect.begin(), inconnect.end()), inconnect.end());
		it = inconnect.begin();
		
		_i = it->x;
		_j = it->y;
		cs.cell[_i][_j].inList = k;
		cs.cell[_i - 1][_j - 1].connected = 1;
		cs.cell[_i - 1][_j].connected = 1;
		cs.cell[_i - 1][_j + 1].connected = 1;
		cs.cell[_i][_j - 1].connected = 1;
		cs.cell[_i][_j + 1].connected = 1;
		cs.cell[_i + 1][_j - 1].connected = 1;
		cs.cell[_i + 1][_j].connected = 1;
		cs.cell[_i + 1][_j + 1].connected = 1;
	//	cout << incon.x <<"."<< incon.y<<","<<incon.todes << "\n";
		/*for (it = inconnect.begin(); it != inconnect.end(); ) {

			if (it->todes == cs.cell[_i][_j].todes) {
				it = inconnect.erase(it);
			}
			else
			{
				it++;
			}
		}*/
		inconnect.erase(inconnect.begin());
		k++;
	}
}

void surface::leastcostpath(int _x, int _y, int _xs, int _ys) {
	int x, y;
	node temp;
	temp = cs.cell[_xs][_ys];
	cs.cell[_xs][_ys].inPath = 1;
	while (temp.x!=_x&&temp.y !=_y)
	{
		x = temp.xy[0];
		y = temp.xy[1];
		cs.cell[x][y].inPath = 1;
		temp = cs.cell[x][y];
	}
}