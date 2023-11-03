// Algoritm1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct List
{
	string Word;
	int WordLength;
	List* Next;
};

List* AddToList(List* list, string word) {
	List* q = list;
	int length = word.length();
	if (q == NULL) {
		q = new(List);
		q->Next = NULL;
		q->Word = word;
		q->WordLength= length;
		q->Next = list;
		list = q;
		return (list);
	}
	while (q != NULL)
	{

		if (q->WordLength == length) {
			if (q->Word<word){
				if (q->Next != NULL) {
					q->Next=AddToList(q->Next, word);
					
					return(list);
				}
				else {
					q->Next = new(List);
					q->Next->Next = NULL;
					q->Next->Word = word; // записывает слева
					q->Next->WordLength = length;
					return(list);
				}
			}
			else
			{
				if (q->Word == word) {
					return(list);
				}
				while (q != NULL){
					q = q->Next;
				}
				if (q == NULL)
					q = new(List);
				q->Word = word;
				q->WordLength= length; // записывает справа
				q->Next = list;
				list = q;
				return (list);
			}
		}
		if (q->WordLength > length) {
			if (q->Next != NULL) {
				 AddToList(q->Next, word);
			}
			else {
				q->Next = new(List);
				q->Next->Next = NULL;
				q->Next->Word = word; // записывает слева
				q->Next->WordLength = length;
				return(list);
			}
		}
	if (q->WordLength < length)
		{
			while (q != NULL)
			{
				q = q->Next;
			}
			if (q == NULL) {
				q = new(List);
				q->Next = NULL;
			}
			q->Word = word;
			q->WordLength= length; // записывает справа
			q->Next = list;
			list = q;
			return (list);
		}
		q = q->Next;
	}
	return(list);
}

List Readfile() {
	List* Temp = nullptr;
	ifstream inFile("input.txt", ios::in);
	string word;
	while (getline(inFile, word)) {
		Temp=AddToList(Temp, word);
	}
	return(*Temp);
}

void PrintList(List* list) {
	while (list!=NULL)
	{
		cout << list->Word << endl;
		list = list->Next;
	}
}

void LengthMoreThenN(List* list, int size) {
	while ((list!=NULL)&&(list->WordLength>size))
	{
		cout << list->Word <<endl;
		list = list->Next;
	}
}

void LengthN(List* list, int size) {
	while ((list != NULL) && (list->WordLength >= size))
	{
		if (list->WordLength==size)
			cout << list->Word << endl;
		list = list->Next;
	}
}

void Filter(List* list) {
	int N;
	cout << "Length = ...";
	cin >> N;
	cout << "\nWords with length more then " << N << endl;
	LengthMoreThenN(list, N);
	cout << "\nWords with length " << N << endl;
	LengthN(list, N);
}

void Program() {
	ifstream inFile("input.txt", ios::in);
	if (!inFile.is_open())
	{
		cout << "File didn't open\n";
		inFile.close();
		return;
	}
	List Words{};
	Words=Readfile(); 
	cout << "Would you like to print start list? [Y/n]\n";
	char input;
	cin >> input;
	if (tolower(input) == 'y')
	{
		PrintList(&Words);
	}
	cout << "\nWould you like to print filter list? [Y/n]\n";
	cin >> input;
	if (tolower(input) == 'y') Filter(&Words);
	while (tolower(input) != 'n') {
		cout << "\nWould you like to change length? [Y/n]\n";
		cin >> input;
		if (tolower(input) == 'y') Filter(&Words);
	}
}

int main()
{
	Program();
	return(0);
}

