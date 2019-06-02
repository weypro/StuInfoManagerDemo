#include <cstdio>
#include <Windows.h>
#include <time.h>
#include <io.h>
#include <algorithm>
#include "database.h"
#include "generator.h"

void menu();
void GetDataBaseDirectory(char* dir, size_t len);
void gamemain();
void ListFiles(const char * dir);
void input();

//vector<string> wordlist;

int main()
{
	menu();
	gamemain();
	return 0;
}

void menu()
{
	printf("Welcome to play Word Search Puzzle. Please press enter to continue.\n");
	getchar();
	system("cls");
}

void ListFiles(const char * dir)
{
	intptr_t handle;
	_finddata_t findData;

	handle = _findfirst(dir, &findData);    // ����Ŀ¼�еĵ�һ���ļ�
	if (handle == -1)
	{
		cout << "Failed to find lists!\n";
		return;
	}

	do
	{
		if (findData.attrib & _A_SUBDIR
			&& strcmp(findData.name, ".") == 0
			&& strcmp(findData.name, "..") == 0
			)    // �Ƿ�����Ŀ¼���Ҳ�Ϊ"."��".."
			//cout << findData.name << "\t<dir>\n";
			{ }
		else
		{
			cout << findData.name << endl;
		}
	} while (_findnext(handle, &findData) == 0);    // ����Ŀ¼�е���һ���ļ�

	//cout << "Done!\n";
	_findclose(handle);    // �ر��������
}

void GetDataBaseDirectory(char* dir, size_t len)
{
	GetModuleFileName(NULL, dir, len);
	(strrchr(dir, '\\'))[1] = 0;
	strcat(dir, "list\\");
}

void gamemain()
{
	//�������ݿ�
	cout << "Please select one of the following lists by typing the name." << endl;
	char dbDirectory[MAX_PATH] = { 0 };
	GetDataBaseDirectory(dbDirectory, MAX_PATH);
	//printf("%s", dbDirectory);
	char dbDirectorytemp[MAX_PATH] = { 0 };
	strcat(dbDirectorytemp, "*.db");
	//�г����
	ListFiles(dbDirectorytemp);
	//ѡ�����
	char selectdb_name[50] = { 0 };
	cout << "Input the name of the list:";
	cin >> selectdb_name;
	//cout << selectdb_name;
	strcat(dbDirectory, selectdb_name);//"test.db"
	GetWordsFromDatabase(dbDirectory);
	//��̬����grid
	srand(time(NULL));
	Generator gen;
	gen.ClearGrid();
	gen.InsertWordsFromList();
	gen.FillGrid();
	gen.PrintGrid();
	//ѭ������
	input();
	//����������
	cout << "You have won the game!";
}

void input()
{
	size_t number = wordlist.size();
	while (number!=0)
	{
		char playerans[100] = { 0 };
		cout << "Input the word:";
		cin >> playerans;
		vector<string>::iterator result;
		result = find(wordlist.begin(), wordlist.end(), playerans);
		if ((result - wordlist.begin()) == wordlist.size())
		{
			cout << "Try again!" << endl;
		}
		else
		{
			wordlist.erase(result);
			number--;
			cout << "You got one!" << endl;
		}
	}
}