#include<stdio.h>
#include<conio.h>
#include <fcntl.h>
#include <io.h>
#include<string>

// DANH SÁCH CÁC CHUỖI CẦN TÌM
#define title L"<title>HCMUS - "
#define classFullName L"class=\"Personal_FullName\">"
#define classFaculty L"class=\"Personal_Department\">"
#define classEmail L"class=\"Personal_Phone\">"
#define classLinkImage L"class=\"Personal_HinhcanhanKhung\">\n                    <img src=\""
#define classTextInList L"class=\"TextInList\">"
#define classInfo L"class=\"InfoGroup\">\x54\x68\xC3\xB4\x6E\x67 \x74\x69\x6E \x63\xC3\xA1 \x6E\x68\xC3\xA2\x6E</div>\n                    <div>\n                        <ul class=\"TextInList\">\n"
#define classHobby L"class=\"InfoGroup\">\x53\xE1\xBB\x9F \x74\x68\xC3\xAD\x63\x68</div>\n\n                        <ul class=\"TextInList\">\n"
#define classDescription L"class=\"InfoGroup\">\x4D\xC3\xB4 \x74\xE1\xBA\xA3</div>\n                    <div class=\"Description\">\n"
#define classFooter L"class=\"Layout_Footer\">\n            <div class=\"divCopyright\">\n                <br />\n                <img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\n                <br />\n                @"
#define KTLT L"\x4B\xE1\xBB\xB9 \x74\x68\x75\xE1\xBA\xAD\x74 \x6C\xE1\xBA\xAD\x70 \x74\x72\xC3\xAC\x6E\x68</br>\n"
// DANH SÁCH CÁC CHỦ ĐỀ CỦA DÒNG
#define topicFullName L"Há» vÃ  tÃªn: "
#define topicID L"MSSV: "
#define topicEmail L"Email: "
#define topicBirthDay L"NgÃ y sinh: "
#define topicFaculty L"Sinh viÃªn khoa: "
#define topicYearSchool L"KhÃ³a: "

struct student
{
	char *ID;
	wchar_t *fullName;
	wchar_t *faculty;
	int yearSchool;
	char *birthDay;
	char *Email;
	char *linkImage;
	wchar_t *description;
	wchar_t *hobby[100];

	student();
}; typedef struct student STUDENT;

struct list
{
	STUDENT *student;
	int nStudent;
	int *nHobbyOfOneStudent;

	STUDENT& operator[](int i)
	{
		if (student != NULL && i >= 0 && i < nStudent)
			return *(student + i);
	}

	list();
}; typedef struct list LIST;

void FGETWS(wchar_t *&ws, const int &maxSizeWS, FILE *fileIn, char &mark);
void FGETS(char *&s, const int &maxSizeS, FILE *fileIn, char &mark);
void FSCANF_NUMBER(int &number, FILE *fileIn, char &mark);
bool readFileIn_WriteFileOut_ToWS(FILE *fileOut, FILE *fileIn, wchar_t* ws);
bool readFileIn_ToWS(FILE *fileIn, wchar_t *ws);
void destroyList(LIST &list);
template<typename T> // hàm phát sinh một dòng có dạng " <li>topic: content</li> " trong html và ghi vào fileOuT ==> VD: <li>Ẩm thực: Bánh mì, Bún nước lèo,..<\li>
void addLineInList(wchar_t *topic, T content, FILE *fileOut)
{
	fputs("<li>", fileOut);
	fputws(topic, fileOut);

	if (typeid(T).name() == typeid(int).name())
		fprintf_s(fileOut, "%d", (int)content);
	else if (typeid(T).name() == typeid(char*).name())
		fputs((const char *)content, fileOut);
	else if (typeid(T).name() == typeid(wchar_t*).name())
		fputws((const wchar_t *)content, fileOut);

	fputs("</li>\n\t\t\t\t\t", fileOut);
}

bool isInMenu(int *Menu, const int &nMenu, const int &choose);
void optionMenu(int *&Menu, int &nMenu);
int nStudentOfList(FILE *fileIn);
void readFileCSV(FILE *fileIn, LIST &list);
void writeOneStudentInFileCSV(FILE *fileIn, FILE *fileOut, const STUDENT &student, const int &nHobby, int *Menu, const int &nMenu);