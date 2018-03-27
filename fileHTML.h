#include<stdio.h>
#include<conio.h>
#include<string>

#define title L"<title>HCMUS - "
#define classFullName L"Personal_FullName\">"
#define classFaculty L"Personal_Department\">"
#define classEmail L"Personal_Phone\">"
#define classLinkImage L"Personal_HinhcanhanKhung\">\n<img src = \""
#define classTextInList L"TextInList\">"
#define classHobby L"InfoGroup\">Sở thích</div>\n<div>\n<ul class = \"TextInList\">"
#define classDescription L"Description\">"

struct student
{
	char ID[11];
	wchar_t fullName[31];
	wchar_t faculty[31];
	int yearSchool;
	char birthDay[11];
	char *linkImage;
	wchar_t description[1000];
	wchar_t hobby[1000];
}; typedef struct student STUDENT;
void readFileStudent(FILE *fileIn, STUDENT &student);
void writeFileStudent(FILE *fileIn, FILE *fileOut, STUDENT student);