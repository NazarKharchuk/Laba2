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
void delete_mass(string* str) {
	delete[] str;
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
		string** countries = new string * [N];
		for (int i = 0; i < N; i++) {
			countries[i] = new string[22];
		}





		
		for (int i = 0; i < N; i++) {
			delete [] countries[i];
		}
		delete []  countries;

		iFile.close();
	}

	return top_ten;
}