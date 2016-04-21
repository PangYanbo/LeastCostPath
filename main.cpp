#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "lcpa.h"

using namespace std;

float	v1[802][802];		//���X�^�[�f�[�^�P
float	v2[802][802];		//���X�^�[�f�[�^�Q

int main(int argc, char *argv[]) {
	int	i, j;
	int x, y,_x,_y;
	char	rn[128];		//�n�於
	char	vn[128];		//�ϐ���
	char	un[128];		//�P�ʖ�
	int	dt;		//�f�[�^�̃^�C�v�i���g�p�j
	int	xas, yas;		//�v�f��
	float	xs, ys;		//���f���̑傫��
	char	str[128];		//�w�b�_�[�ƃf�[�^����؂镶����
	
	float   xus, yus;		//�i�q�P�ʂ̑傫��

			
	for (i = 0; i <= 801; i++) {
		for (j = 0; j <= 801; j++) {
			v1[i][j] = 0;
			v2[i][j] = 0;
		}
	}

	//�R�}���h���C���������Q�łȂ��ꍇ�́A�g�p�@��\�����ďI������B
	if (argc != 2) {
		cerr << "Usage: LeastCostPathAnalysis <filename>\n";
		return 1;
	}


	//�t�@�C�����J���Ȃ������ꍇ�́A���̎|�\�����ďI������B
	ifstream fin(argv[1]);
	if (!fin) {
		cerr << "Cannot open file.\n";
		return 1;
	}

	//�f�[�^�̓ǂݍ��݁B
	fin.getline(rn, 80);
	fin.getline(vn, 80);
	fin.getline(un, 80);
	fin >> dt >> xas >> yas;
	fin >> xs >> ys >> str;
	for (i = 1; i <= 800; i++) {
		for (j = 1; j <= 800; j++) {
			fin >> v1[i][j];
		}
	}
	fin.close();

	//�f�[�^�̊O�}
	for (j = 1; j <= yas; j++) {
		v1[0][j] = v1[1][j] * 2 - v1[2][j];
		v1[xas + 1][j] = v1[xas][j] * 2 - v1[xas - 1][j];
	}

	for (i = 1; i <= xas; i++) {
		v1[i][0] = v1[i][1] * 2 - v1[i][2];
		v1[i][yas + 1] = v1[i][yas] * 2 - v1[i][yas - 1];
	}

	v1[0][0] = v1[1][1] * 2 - v1[2][2];
	v1[xas + 1][0] = v1[xas][1] * 2 - v1[xas - 1][2];
	v1[0][yas + 1] = v1[1][yas] * 2 - v1[2][yas - 1];
	v1[xas + 1][yas + 1] = v1[xas][yas] * 2 - v1[xas - 1][yas - 1];

	//�i�q�P�ʂ̌v�Z

	xus = xs / xas * 1000;
	yus = ys / yas * 1000;

	
	
		surface sf;
		sf.calcost(xas, yas, xus, yus, v1, v2);
		sf.creatsurface(v2);

		cin >> x;

		cin >> y;

		cin >> _x;

		cin >> _y;
		sf.dijkstra(x,y);
		sf.leastcostpath(x, y, _x, _y);

		cout << "path mask" << "\n" << vn << "\n" << un << "\n";
		cout << dt << "\n" << xas << "\n" << yas << "\n";
		cout << xs << "\n" << ys << "\n" << str << "\n";
		sf.print();
		
		return 0;
	}
