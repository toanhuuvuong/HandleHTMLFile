#include<stdio.h>
#include<conio.h>
#include<string>

#define title L"<title>HCMUS - "
#define classFullName L"class=\"Personal_FullName\">"
#define classFaculty L"class=\"Personal_Department\">"
#define classEmail L"class=\"Personal_Phone\">\n\t\t\t\t\t\t\t"
#define classLinkImage L"class=\"Personal_HinhcanhanKhung\">\n\t\t\t\t\t\t<img src=\""
#define classTextInList L"class=\"TextInList\">"
#define classInfo L"<div class=\"InfoGroup\">ThÃ´ng tin cÃ¡ nhÃ¢n</div>\n                        <div>\n                            <ul class=\"TextInList\">\n                                "
#define classHobby L"class=\"InfoGroup\">Sá»\x9F thÃ­ch</div>\n\n                            <ul class=\"TextInList\">\n                                "
#define classDescription L"class=\"InfoGroup\">MÃ´ táº£</div>\n\t\t\t\t\t\t<div class=\"Description\">"
#define classFooter L"class=\"Layout_Footer\">\n\t\t\t\t<div class=\"divCopyright\">\n\t\t\t\t\t<br />\n\t\t\t\t\t<img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\n\t\t\t\t\t<br />\n\t\t\t\t\t@"
#define KTLT L"Ká»¹ thuáº­t láº­p trÃ¬nh</br>\n\t\t\t\t"

struct student
{
	char ID[11];
	wchar_t fullName[31];
	wchar_t faculty[31];
	int yearSchool;
	char birthDay[11];
	char Email[31];
	char linkImage[31];
	wchar_t description[1000];
	wchar_t hobby[1000];
}; typedef struct student STUDENT;

struct list
{
	STUDENT *student;
	int nStudent;

	STUDENT& operator[](int i)
	{
		if (i >= 0 && i < nStudent && student != NULL)
			return student[i];
	}
}; typedef struct list LIST;

void FGETWS(wchar_t *ws, int maxSizeWS, FILE *fileIn, wchar_t *mark);
void FGETS(char *s, int maxSizeS, FILE *fileIn, char *mark);
bool readFileIn_WriteFileOut_ToWS(FILE *fileOut, FILE *fileIn, wchar_t* ws);
bool readFileIn_ToWS(FILE *fileIn, wchar_t *ws);
bool isInMenu(int *Menu, int nMenu, int choose);

void readFileCSV(FILE *fileIn, LIST &list);
void writeOneStudentInFileCSV(FILE *fileIn, FILE *fileOut, STUDENT student, int *Menu, int nMenu);