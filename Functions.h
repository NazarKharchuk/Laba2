#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <io.h>

using namespace std;

string* file_search(int*);
void delete_mass(string*, string**);
string** scoring(string*, int);
string** create_matrix(int, int);
void delete_matrix(string**, int, int);
void files_reading(string**, string);
void sort(string**, int, int, int);
void give_score(string**, int);
int search_min_element(string**);
void file_creation(string**);