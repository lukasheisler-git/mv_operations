#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

void read_matrix(vector<vector<double>>& matrix, string filename){
	ifstream infile(filename.c_str()); //Open file
	string line, value;
	stringstream ss;
	vector<double> temp;
	
	if (infile.is_open())
	{
		while ( getline (infile,line) ) //iterate trough all lines
		{
			ss << line;
			while (!ss.eof()) { 
				ss >> value; 
				temp.push_back(stold(value)); //push value into vector and parse string to int with stold()
				
			} 
			ss.clear();
			matrix.push_back(temp);
			temp.clear();
		}
	}
	else{cout << "Unable to open file input : " << filename << endl;}
}

void read_vector(vector<double>& vector, string filename)
{
	ifstream infile(filename.c_str()); //Open file
	string line;
	
	if (infile.is_open())
	{
		while ( getline (infile,line) ) //iterate trough all lines
		{
			vector.push_back(stold(line)); //push value into vector and parse string to int with stold()
		}
	}
	else{cout << "Unable to open file input : " << filename << endl;}
}

vector<vector<double>> mm_multiplikation(vector<vector<double>> A, vector<vector<double>> B)
{
	vector<vector<double>> result;
	vector<double> temp_;
	double temp = 0.0;
	
	for(int i = 0; i < A.size(); i++)
	{
		for(int j = 0; j < A[0].size(); j++)
		{
			for(int k = 0; k < A[0].size(); k++)
			{
				temp = temp + A[i][k] * B[k][j];
			}
			temp_.push_back(temp);
			temp = 0.0;
		}
		result.push_back(temp_);
		temp_.clear();
	}
	return result;
}
vector<double> mv_multiplikation(vector<vector<double>> A, vector<double> v)
{
	vector<double> result;
	double temp = 0.0;
	
	if(v.size() == A.size())
	{
		for(int i = 0; i < A[0].size(); i++)
		{
			for(int j = 0; j < v.size(); j++)
			{
				temp = temp + v[j]*A[j][i];
			}
			result.push_back(temp);
			temp = 0.0;
		}
	}
	else
	{
		cout << "Die Spaltenzahl des Vektors entspricht nicht der Zeilenzahl der Matrix. Multiplikation nicht möglich." << endl;
	}
	return result;
}
vector<vector<double>> m_transpose(vector<vector<double>> A)
{
	vector<vector<double>> result;
	vector<double> temp;
	for(int i = 0; i < A[0].size(); i++)
	{
		for(int j = 0; j < A.size(); j++)
		{
			temp.push_back(A[j][i]);
		}
		result.push_back(temp);
		temp.clear();
	}
	return result;
}

void matrix_out(vector<vector<double>> matrix, string filename)
{
	ofstream outfile(filename);
	string temp;
	if(outfile.is_open())
    {
		for(int i = 0; i < matrix.size(); i++)
		{
			for(int j = 0; j < matrix[0].size(); j++)
			{
				outfile << scientific << setprecision(18) << matrix[i][j];
				outfile << " ";
			} //
			outfile << endl;
		}
	}
	else{ cout << "Unable to open file output : " << filename << endl;}
	
}

void vector_out(vector<double> vector, string filename)
{
	ofstream outfile(filename);
	if(outfile.is_open())
    {
		for(int i = 0; i < vector.size(); i++)
		{
			outfile << scientific << setprecision(18) << vector[i] << endl;
		}
	}
	else{ cout << "Unable to open file output : " << filename << endl;}
}

int main(){
	vector<vector<double>> matrixA;
	vector<vector<double>> matrixB;
	vector<vector<double>> matrixC;
	vector<double> vectorV;
	
	
	read_matrix(matrixA, "Inputs/MatrixA.txt");
	read_matrix(matrixB, "Inputs/MatrixB.txt");
	read_matrix(matrixC, "Inputs/MatrixC.txt");
	read_vector(vectorV, "Inputs/VectorV.txt");
	
	
	matrix_out(mm_multiplikation(matrixA, matrixC), "AC.txt");
	vector_out(mv_multiplikation(matrixB, vectorV), "vB.txt");
	vector_out(mv_multiplikation(mm_multiplikation(m_transpose(matrixC),matrixB), vectorV),"vCtB.txt");
	matrix_out(mm_multiplikation(m_transpose(matrixB),mm_multiplikation(matrixA,matrixB)),"BtAB.txt");
}

