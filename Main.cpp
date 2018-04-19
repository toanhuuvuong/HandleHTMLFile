#include"fileHTML.h"

// Danh sách tên của các profile xuất ra
wchar_t *nameFileOut[10] = { L"1.htm", L"2.htm", L"3.htm", L"4.htm", L"5.htm", L"6.htm", L"7.htm", L"8.htm", L"9.htm", L"10.htm" };

int main()
{
	_setmode(_fileno(stdout), _O_U8TEXT); // in ra tiếng Việt

	int *Menu;
	int nMenu;

	LIST list;

	FILE *fileIn_CSV;
	_wfopen_s(&fileIn_CSV, L"TableInfo.csv", L"r");

	if (!fileIn_CSV)
		wprintf(L"Error open file\n");

	list.nStudent = nStudentOfList(fileIn_CSV);
	list.student = new STUDENT[list.nStudent];

	rewind(fileIn_CSV);

	readFileCSV(fileIn_CSV, list);

	fclose(fileIn_CSV); //----------------------------------------------------------------------------------------------------------
	FILE *fileIn;
	_wfopen_s(&fileIn, L"example.htm", L"r");

	if (!fileIn)
		wprintf(L"Error open file\n");

	FILE *fileOut;
	for (int i = 0; i < list.nStudent; i++)
	{
		wprintf(L"================STUDENT %d================\n", i + 1);
		_wfopen_s(&fileOut, nameFileOut[i], L"w");

		optionMenu(Menu, nMenu);

		writeOneStudentInFileCSV(fileIn, fileOut, list[i], list.nHobbyOfOneStudent[i], Menu, nMenu);

		fclose(fileOut);

		free(Menu);

		rewind(fileIn); // đưa con trỏ chỉ vị trở về đầu fileIn(HTML) để đọc tiếp sinh viên mới
	}
	fclose(fileIn); //----------------------------------------------------------------------------------------------------------------
	destroyList(list);

	_getch();
	return 0;
}
