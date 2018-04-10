#include<stdio.h>
#include<conio.h>
#include<string>
// DANH SÁCH CÁC CHUỖI CẦN THAY THẾ
#define title L"<title>HCMUS - "
#define classFullName L"class=\"Personal_FullName\">"
#define classFaculty L"class=\"Personal_Department\">"
#define classEmail L"class=\"Personal_Phone\">\n\t\t\t\t\t\t\t"
#define classLinkImage L"class=\"Personal_HinhcanhanKhung\">\n\t\t\t\t\t\t<img src=\""
#define classTextInList L"class=\"TextInList\">"
#define classInfo L"class=\"InfoGroup\">ThÃ´ng tin cÃ¡ nhÃ¢n</div>\n                        <div>\n                            <ul class=\"TextInList\">\n                                "
#define classHobby L"class=\"InfoGroup\">Sá»\x9F thÃ­ch</div>\n\n                            <ul class=\"TextInList\">\n                                "
#define classDescription L"class=\"InfoGroup\">MÃ´ táº£</div>\n\t\t\t\t\t\t<div class=\"Description\">"
#define classFooter L"class=\"Layout_Footer\">\n\t\t\t\t<div class=\"divCopyright\">\n\t\t\t\t\t<br />\n\t\t\t\t\t<img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" /><br />\n\t\t\t\t\t<br />\n\t\t\t\t\t@"
#define KTLT L"Ká»¹ thuáº­t láº­p trÃ¬nh</br>\n\t\t\t\t"
// DANH SÁCH CÁC CHỦ ĐỀ CỦA DÒNG
#define topicFullName L"Há» vÃ  tÃªn: "
#define topicID L"MSSV: "
#define topicEmail L"Email: "
#define topicBirthDay L"NgÃ y sinh: "
#define topicFaculty L"Sinh viÃªn khoa: "
#define topicHobby1 L"\xC3\x82m nháº¡c: "
#define topicHobby2 L"áº¨m thá»±c: "

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
	wchar_t *hobby[2];

	student();
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

void FGETWS(wchar_t *&ws, int maxSizeWS, FILE *fileIn, wchar_t *mark);
void FGETS(char *&s, int maxSizeS, FILE *fileIn, char *mark);
bool readFileIn_WriteFileOut_ToWS(FILE *fileOut, FILE *fileIn, wchar_t* ws);
bool readFileIn_ToWS(FILE *fileIn, wchar_t *ws);
bool isInMenu(int *Menu, int nMenu, int choose);
void destroyList(LIST &list);
// hàm phát sinh một dòng có dạng " <li>topic: content</li> " trong html và ghi vào fileOuT ==> VD: <li>Ẩm thực: Bánh mì, Bún nước lèo,..<\li>
template<typename T>
void addLine(wchar_t *topic, T content, FILE *fileOut)
{
	fputs("<li>", fileOut);
	fputws(topic, fileOut);

	if (typeid(T).name() == typeid(int).name())
		fscanf(fileOut, "%d", (int)content);
	else if (typeid(T).name() == typeid(char*).name())
		fputs((const char *)content, fileOut);
	else if (typeid(T).name() == typeid(wchar_t*).name())
		fputws((const wchar_t *)content, fileOut);

	fputs("</li>\n", fileOut);
}

void readFileCSV(FILE *fileIn, LIST &list);
void writeOneStudentInFileCSV(FILE *fileIn, FILE *fileOut, STUDENT student, int *Menu, int nMenu);