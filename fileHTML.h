#include<stdio.h>
#include<conio.h>
#include<string>

#define title L"<title>HCMUS - "
#define classFullName L"class=\"Personal_FullName\">"
#define classFaculty L"class=\"Personal_Department\">"
#define classEmail L"class=\"Personal_Phone\">"
#define classLinkImage L"class=\"Personal_HinhcanhanKhung\">\n<img src = \""
#define classTextInList L"class=\"TextInList\">"
#define classInfo L"class=\"InfoGroup\">Thông tin cá nhân</div>\n<div>\n<ul class = \"TextInList\">"
#define classHobby L"class=\"InfoGroup\">Sở thích</div>\n<div>\n<ul class = \"TextInList\">"
#define classDescription L"class=\"InfoGroup\">Mô tả</div>\n<div class = \"Description\">"

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