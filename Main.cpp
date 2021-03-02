#include "Functions.h"

int main() {
	setlocale(LC_ALL, "russian");
	int number_of_files;
	string* name_of_files = file_search(&number_of_files);

	cout << number_of_files << endl;
	for (int i = 0; i < number_of_files; i++)
		cout << name_of_files[i] << endl;

	delete_mass(name_of_files);
}