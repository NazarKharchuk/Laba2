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
		if (!iFile.is_open()) {
			cout << "File open error!" << endl;
			return 0;
		}
		int N = 0;
		iFile >> N;
		iFile.close();

		string** countries = create_matrix(N, 22);

		files_reading(countries, str[p]);




		
		delete_matrix(countries, N, 22);


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

/*==== File read function ====*/
void files_reading(string** matr, string name) {
	ifstream iFile(name);
	if (!iFile.is_open()) {
		cout << "File open error!" << endl;
		return;
	}

	int N = 0;
	iFile >> N;

	string str;
	getline(iFile, str);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 20; j++) {
			getline(iFile, str, ',');
			matr[i][j] = str;
		}
		/*int X;
		iFile >> X;
		matr[i][20] = X;
		getline(iFile, str);*/
		getline(iFile, str);
		matr[i][20] = str;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 22; j++) {
			cout << j+1 << "-->("<< matr[i][j]<< ")  " ;
		}
		cout << endl;
	}

	iFile.close();
}