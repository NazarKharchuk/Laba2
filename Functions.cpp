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

	int* arr1 = points();

	for (int c = 1; c < 21; c++) {
		sort(countries, num_countries, 22, c);
		give_score(countries, num_countries, arr1);
	}

	delete_mass(arr1);

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
void give_score(string** arr, int number, int* arr1) 
{
	int score;

	for (int j = 0; j < 10; j++)
	{
		if (number > j)
		{
			score = stoul(arr[j][21]) + arr1[j];
			arr[j][21] = to_string(score);
		}
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

int* points() {
	int  num_prizes;
	cout << "Enter number of prizes:";
	cin >> num_prizes;
	int points;
	int* arr1 = new int[10];

	for (int i = 0; i < 10; i++)
	{
		arr1[i] = 0;
	}

	for (int i = 0; i < num_prizes; i++)
	{
		cout << "Enter " << i + 1 << " point : ";
		cin >> points;
		arr1[i] = points;
	}
	return arr1;
}

void delete_mass(int* arr) {
	delete[] arr;
}