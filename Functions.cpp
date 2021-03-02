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