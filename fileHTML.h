#include<stdio.h>
#include<conio.h>
#include<string>

#define title L"<title>HCMUS - "
#define classFullName L"class=\"Personal_FullName\">"
#define classFaculty L"class=\"Personal_Department\">"
#define classEmail L"class=\"Personal_Phone\">"
#define classLinkImage L"class=\"Personal_HinhcanhanKhung\">\n\t\t\t\t\t\t<img src=\""
#define classTextInList L"class=\"TextInList\">"
#define classInfo L"<div class=\"InfoGroup\">ThÃ´ng tin cÃ¡ nhÃ¢n</div>\n                        <div>\n                            <ul class=\"TextInList\">\n                                "
#define classHobby L"class=\"InfoGroup\">Sá»Ÿ thÃ­ch</div>\n                        <div>\n                            <ul class=\"TextInList\">\n                                "
#define classDescription L"class=\"InfoGroup\">MÃ´ táº£</div>\n\t\t\t\t\t\t<div class=\"Description\">"
struct student
{
	char ID[11];
	wchar_t fullName[31];
	wchar_t faculty[31];
	int yearSchool;
	char birthDay[11];
	char linkImage[31];
	wchar_t description[1000];
	wchar_t hobby[1000];
}; typedef struct student STUDENT;

void FGETWS(wchar_t *ws, int maxSizeWS, FILE *fileIn, wchar_t *mark);
void FGETS(char *s, int maxSizeS, FILE *fileIn, char *mark);
void readFileIn_WriteFileOut_ToWS(FILE *fileOut, FILE *fileIn, wchar_t* ws);

void readFileStudent(FILE *fileIn, STUDENT &student);
void writeFileStudent(FILE *fileIn, FILE *fileOut, STUDENT student);