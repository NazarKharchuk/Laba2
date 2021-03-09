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

	for (int i = 0; i < 10; i++) {
		top_ten[i][1] = "0";
	}

	int num_countries = 0;				//Number of all countries


	for (int p = 0; p < Num; p++) {
		ifstream iFile(str[p]);
		if (!iFile.is_open()) {
			cout << "File open error!" << endl;
			return 0;
		}
		int N = 0;
		iFile >> N;
		iFile.close();
		num_countries += N;
	}

	string** countries = create_matrix(num_countries, 22);

	int place = 0;
	for (int q = 0; q < Num; q++) {
		ifstream iFile(str[q]);
		if (!iFile.is_open()) {
			cout << "File open error!" << endl;
			return 0;
		}
		int N = 0;
		iFile >> N;

		files_reading(countries, str[q], place);

		place += N;
		iFile.close();
	}

		

	for (int c = 1; c < 21; c++) {
		sort(countries, num_countries, 22, c);
		give_score(countries, num_countries);
	}


	for (int m = 0; m < num_countries; m++) {
		int min = search_min_element(top_ten);
		if (stoi(countries[m][21]) > stoi(top_ten[min][1])) {
			top_ten[min][1] = countries[m][21];
			top_ten[min][0] = countries[m][0];
		}
	}


	/*for (int i = 0; i < num_countries; i++) {
		for (int j = 0; j < 22; j++) {
			cout << j + 1 << "-->(" << countries[i][j] << ")  ";
		}
		cout << endl;
	}*/


		
	delete_matrix(countries, num_countries, 22);



	sort(top_ten, 10, 2, 1);				//Sorting the top countries

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
void files_reading(string** matr, string name, int place) {
	ifstream iFile(name);
	if (!iFile.is_open()) {
		cout << "File open error!" << endl;
		return;
	}

	int N = 0;
	iFile >> N;

	string str;
	getline(iFile, str);
	for (int i = place; i < N + place; i++) {
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
		matr[i][21] = "0";
	}

	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < 22; j++) {
			cout << j+1 << "-->("<< matr[i][j]<< ")  " ;
		}
		cout << endl;
	}*/

	iFile.close();
}


/*==== Sorting function ====*/
void sort(string** arr, int row, int col, int X) {
	string delta;
	for (int i = 0; i < row - 1; i++) 
	{
		for (int j = 0; j < row - i - 1; j++) 
		{
			if (stoul(arr[j][X]) < stoul(arr[j + 1][X])) 
			{
				for (int n = 0; n < col; n++) 
				{
					delta = arr[j][n];
					arr[j][n] = arr[j + 1][n];
					arr[j + 1][n] = delta;
				}
			}
		}
	}
}


/*==== Function, which hands out the points ====*/
void give_score(string** arr, int number) 
{
	int score;
	if (number > 0) 
	{
		score = stoul(arr[0][21]) + 12;
		arr[0][21] = to_string(score);
	}
	if (number > 1) 
	{
		score = stoul(arr[1][21]) + 10;
		arr[1][21] = to_string(score);
	}
	if (number > 2) 
	{
		score = stoul(arr[2][21]) + 8;
		arr[2][21] = to_string(score);
	}
	if (number > 3) 
	{
		score = stoul(arr[3][21]) + 7;
		arr[3][21] = to_string(score);
	}
	if (number > 4) 
	{
		score = stoul(arr[4][21]) + 6;
		arr[4][21] = to_string(score);
	}
	if (number > 5) 
	{
		score = stoul(arr[5][21]) + 5;
		arr[5][21] = to_string(score);
	}
	if (number > 6) 
	{
		score = stoul(arr[6][21]) + 4;
		arr[6][21] = to_string(score);
	}
	if (number > 7) 
	{
		score = stoul(arr[7][21]) + 3;
		arr[7][21] = to_string(score);
	}
	if (number > 8)
	{
		score = stoul(arr[8][21]) + 2;
		arr[8][21] = to_string(score);
	}
	if (number > 9) 
	{
		score = stoul(arr[9][21]) + 1;
		arr[9][21] = to_string(score);
	}
}

/*==== Function, which returns a min.element ====*/
int search_min_element(string** arr) {
	int min = 0;
	for (int i = 1; i < 10; i++) 
	{
		if (stoi(arr[i][1]) < stoi(arr[min][1])) 
		{
			min = i;
		}
	}
	return min;
}

/*==== Function, which creates a final file ====*/
void file_creation(string** arr) {
	ofstream oFile("results.csv");
	for (int i = 0; i < 9; i++) {
		oFile << arr[i][0] << ",";
	}
	oFile << arr[9][0];
	oFile.close();
}