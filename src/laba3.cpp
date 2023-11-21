//============================================================================
// Name        : laba3.cpp
// Author      : andrew
// Version     : 1 variant
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

struct Tovar{
	string name;
	int amount;
	double cost;
};

Tovar tovar_init(list<string> info){
	Tovar out;
	auto it = info.begin();
	out.name = *it;
	it++;
	out.amount = stoi(*it);
	it++;
	out.cost = stod(*it);
	return out;
}

void print_tovar(Tovar Tovar){
	cout<<Tovar.name<<" "<<Tovar.amount<<" "<<Tovar.cost<<endl;
}

list<string> tovar_to_liststr(Tovar Tovar){
	list<string> out;
	out.push_back(Tovar.name);
	out.push_back(to_string(Tovar.amount));
	out.push_back(to_string(Tovar.cost));
	return out;
}

list<string> split_for_delimeter(string line){
	list<string> out;
	string word = "";
	for(const auto& i: line){
		if (i == ' '){
			out.push_back(word);
			word = "";
		}
		else{
			word = word + i;
		}
	}
	out.push_back(word);
	return out;
}

list<Tovar> read_product(){
	list<Tovar> out;
	string line;
	std::ifstream inFile("product.txt");
	if (!inFile.is_open()){
		cerr<<"Ошибка чтения файла"<<endl;
		exit(1);
	}
	while(getline(inFile, line)){
		out.push_back(tovar_init(split_for_delimeter(line)));
	}
	inFile.close();
	return out;
}

void write_product(list<string> line){
	std::ofstream outFile("product.txt", ios::app);
	if (!outFile.is_open()){
		cerr<<"Ошибка записи в файл"<<endl;
		exit(1);
	}
	for(const auto& i: line){
		outFile<<i<<" ";
	}
	outFile<<endl;
	outFile.close();
}

bool comp_name(Tovar first, Tovar second){
	return first.name < second.name;
}
bool comp_amount(Tovar first, Tovar second){
	return first.amount > second.amount;
}
bool comp_cost(Tovar first, Tovar second){
	return first.cost > second.cost;
}

int sort_option(){
	int out;
	cout<<"Выберите категорию сортировки\n1.Наименование\n2.Количество\n3.Стоимость"<<endl;
	cin>>out;
	return out;
}

void sort_product(){
	int option;
	cout<<"Введите параметр сортировки"<<endl;
	option = sort_option();
	ofstream outputFile("output.txt", ios::app);
	if (!outputFile.is_open()){
		cerr<<"Ошибка открытия файла записи действий"<<endl;
		exit(1);
	}
	list<Tovar> database = read_product();
	switch(option){
		case 1:
			database.sort(comp_name);
			break;
		case 2:
			database.sort(comp_amount);
			break;
		case 3:
			database.sort(comp_cost);
			break;
		default:
			cout<<"Неверно введен параметр сортировки"<<endl;
	}
	std::ofstream outFile("product.txt");
	if (outFile.is_open()){
		outFile.close();
	}
	else{
		cerr<<"Ошибка записи в файл"<<endl;
		exit(1);
	}
	for(const auto& i: database){
		write_product(tovar_to_liststr(i));
	}
	if ((option <= 3)&(option >= 1)){
		cout<<"Выполнена сортировка по параметру "<<option<<endl;
		outputFile<<"Выполнена сортировка по параметру "<<option<<endl;
	}
	else{
		outputFile<<"Неверно введен параметр сортировки"<<endl;
	}
	outputFile.close();
}

string find_option(){
	string out;
	cout<<"Введите название для поиска"<<endl;
	cin>>out;
	return out;
}

void find_product(){
	ofstream outputFile("output.txt", ios::app);
	if (!outputFile.is_open()){
		cerr<<"Ошибка открытия файла записи действий"<<endl;
		exit(1);
	}
	string find = find_option();
	list<Tovar> database = read_product();
	bool finded = false;
	for(const auto& i: database){
		if(i.name == find){
			print_tovar(i);
			finded = true;
			break;
		}
	}
	if(!finded){
		cout<<"Такого товара нет в базе"<<endl;
	}
	else{
		outputFile<<"Выполнен поиск по названию "<<find<<endl;
	}
	outputFile.close();
}

double condition_option(){
	double out;
	cout<<"Введите стоимость"<<endl;
	cin>>out;
	return out;
}

void find_product_for_condition(){
	double condition = condition_option();
	ofstream outputFile("output.txt", ios::app);
	if (!outputFile.is_open()){
		cerr<<"Ошибка открытия файла записи действий"<<endl;
		exit(1);
	}
	list<Tovar> database = read_product();
	bool found = false;
	cout<<"Товары стоимостью не более чем "<<condition<<":"<<endl;
	for(const auto& i: database){
		if(i.cost <= condition){
			print_tovar(i);
			found = true;
		}
	}
	if(!found){
		cout<<"Товаров, удовлетворяющих условию, не найдено"<<endl;
	}
	outputFile<<"Выполнен поиск по условию стоимость не более чем "<<condition<<endl;
	outputFile.close();
}

int print_menu(){
	int out;
	cout<<"---------------------\nВыберете действие\n0.Выход из программы\n1.Сортировка базы товаров\n2.Поиск в базе товаров\n3.Ввод данных в базу\n4.Вывод по условию\n---------------------"<<endl;
	(cin>>out).get();
	return out;
}

void new_to_product(){
	ofstream outputFile("output.txt", ios::app);
	if (!outputFile.is_open()){
		cerr<<"Ошибка открытия файла записи действий"<<endl;
		exit(1);
	}
	bool going = true;
	int counter = 0;
	string line;
	outputFile<<"Начало работы программы"<<endl;
	while(going){
		cout<<"Введите наименование колличество и стоимость товара"<<endl;
		getline(cin, line);
		if(line == ""){
			going = false;
			break;
			cout<<"Ввод окончен"<<endl;
		}
		write_product(split_for_delimeter(line));
		counter++;
	}
	outputFile<<"Введено "<<counter<<" строк"<<endl;
	outputFile.close();
}

int main() {
	setlocale(LC_ALL, "ru");
	bool a = true;
	std::ofstream outputFile("output.txt", ios::app);
	if (!outputFile.is_open()){
		cerr<<"Ошибка открытия файла записи действий"<<endl;
		exit(1);
	}
	while(a){
		switch(print_menu()){
		case 0:
			a = false;
			break;
		case 1:
			sort_product();
			break;
		case 2:
			find_product();
			break;
		case 3:
			new_to_product();
			break;
		case 4:
			find_product_for_condition();
			break;
		}
	}
	outputFile<<"Программа завершена"<<endl;
	outputFile.close();
	cout<<"Программа завершена."<<endl;
	return 0;
}
