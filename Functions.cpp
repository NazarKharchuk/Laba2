#include "Functions.h"

/*==== Function to search for csv files in the directory ====*/
string* file_search(int* Num) {
	_finddata_t data;
	intptr_t hendle = _findfirst("C:\\Laba2\\*.csv", &data);
	int N = 0;
	do {
		N++;
	} while (_findnext(hendle, &data) == 0);

	string* str = new string[N];
	*Num = N;

	hendle = _findfirst("C:\\Laba2\\*.csv", &data);
	int i = 0;
	do {
		str[i] = (string)data.name;
		i++;
	} while (_findnext(hendle, &data) == 0);

	_findclose(hendle);

	return str;
}

/*==== Dynamic array delete function ====*/
void delete_mass(string* str, string** str2) {
	delete[] str;
	delete_matrix(str2, 10, 2);
}

/*==== Scoring function ====*/
string** scoring(string* str, int Num) {

	string** top_ten = new string * [10];
	for (int i = 0; i < 10; i++) {
		top_ten[i] = new string[2];
	}

	for (int p = 0; p < Num; p++) {
		ifstream iFile(str[p]);

		int N = 0;
		iFile >> N;
		string** countries = create_matrix(N, 22);






		
		delete_matrix(countries, N, 22);

		iFile.close();
	}

	return top_ten;
}

/*==== Dynamic matrix create function ====*/
string** create_matrix(int row, int col) {
	string** matrix = new string * [row];
	for (int i = 0; i < row; i++) {
		matrix[i] = new string[col];
	}
	return matrix;
}

/*==== Dynamic matrix delete function ====*/
void delete_matrix(string** matrix, int row, int col) {
	for (int i = 0; i < row; i++) {
		delete[] matrix[i];
	}
	delete[]  matrix;
}