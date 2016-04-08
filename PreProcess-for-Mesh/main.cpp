#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cmath>
using namespace std;

double ** nodelist = NULL;
int ** facelist = NULL;

// ������
double pointProduct(double* a, double* b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

int main()
{
	int number_of_nodes = 0;//�ڵ������
	int number_of_face = 0;//��������γɵ������ε�Ԫ������
	//�ڴ˼����ȡ�ļ�
	ifstream file;
	file.open("InputFile/liver.node", ios::in);//�򿪽ڵ������ļ�
	file >> number_of_nodes;//��ȡ�ڵ������
	//�����ڵ�����
	double ** nodelist = new double*[number_of_nodes];
	for (int i = 0; i < number_of_nodes; i++)
		nodelist[i] = new double[3];
	//��ڵ�����������ݣ������м����temp����������i
	double tempd = 0;
	for (int i = 0; file >> tempd; i++)
	{
		if (i % 4 == 0)
			continue;
		else
			nodelist[i / 4][(i % 4) - 1] = tempd;
	}
	file.close();//�ر��ļ�
	file.open("InputFile/liver.face", ios::in);
	file >> number_of_face;
	int** facelist = new int*[number_of_face];
	for (int i = 0; i < number_of_face; i++)
		facelist[i] = new int[3];
	//��ڵ�����������ݣ��м����temp��ʼ��Ϊ0����������i
	int tempi = 0;
	for (int i = 0; file >> tempi; i++)
	{
		if (i % 4 == 0)
			continue;
		else
			facelist[i / 4][(i % 4) - 1] = tempi - 1;
	}
	file.close();//�ر��ļ�
	vector<int> surfacepoint;
	bool* node_is_selected = new bool[number_of_nodes];
	for (int i = 0; i < number_of_nodes; i++)
	{
		node_is_selected[i] = false;
	}
	for (int i = 0; i < number_of_face; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (!node_is_selected[facelist[i][j]])
			{
				node_is_selected[facelist[i][j]] = true;
			}
		}
	}
	for (int i = 0; i < number_of_nodes; i++)
	{
		if (node_is_selected[i])
		{
			surfacepoint.push_back(i);
		}
	}
	for (int i = 0; i < surfacepoint.size(); i++)
	{
		if (nodelist[surfacepoint[i]][0] > 0.55)
		{
			cout << surfacepoint[i] << " ";
		}
	}
	cout << endl;
}