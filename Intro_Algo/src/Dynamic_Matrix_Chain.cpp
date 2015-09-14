/*
 * Dynamic_Matrix_Chain.cpp
 *
 *  Created on: Oct 3, 2014
 *      Author: MHuang1
 */

#include <iostream>

using namespace std;

void print_opt(long s[][10], long i, long j)
{
	if (i == j)
	{
		 cout << "A";
	}
	else
	{
		cout << "(";
		print_opt(s,i, s[i][j]);
		print_opt(s,s[i][j] + 1, j);
		cout << ")";
	}
}

void dynamic_matrix_chain()
{
	long matrix[10];
	long i,len,l,k,q,j;
	long m[10][10];
	long s[10][10];

	memset(matrix, 0, sizeof(matrix));
	memset(m, 0, sizeof(m));
	memset(s, 0, sizeof(s));

	len = sizeof(matrix)/sizeof(int);

	matrix[1] = 30;
	matrix[2] = 35;
	matrix[3] = 35;
	matrix[4] = 15;

	for(i = 1; i < len; i++)
	{
		m[i][i] = 0;
	}

	cout << len << endl;

	for(l = 2; l < len; l++)
	{
		for(i = 1; i < len - l + 1; i++)
		{
			j = i + l + 1;
			cout << "j:"<< j << endl;

			m[i][j] = 100000000;
			for(k = i; k < j - 1; k++)
			{
				cout << m[i][k] <<" "<< m[k + 1][j] <<" "<< matrix[i - 1] <<" "<< matrix[k] <<" "<< matrix[j] << endl;
				q = m[i][k] + m[k + 1][j] + matrix[i - 1]*matrix[k]*matrix[j];
				cout << "q:"<< q << endl;
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}

			}
		}
	}
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			cout << s[i][j];
		}
		cout << endl;
	}

	print_opt(s,1,9);
}


int main()
{
	dynamic_matrix_chain();
	return 0;
}


