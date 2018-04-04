#include"fileHTML.h"

int main()
{
	wchar_t *nameFileOut[10] = { L"1.htm", L"2.htm", L"3.htm", L"4.htm", L"5.htm", L"6.htm", L"7.htm", L"8.htm", L"9.htm", L"10.htm" };
	LIST list;
	list.nStudent = 10;
	list.student = new STUDENT[list.nStudent];

	FILE *fileIn_CSV = _wfopen(L"TableInfo.csv", L"r");
	if (!fileIn_CSV)
		printf("Error\n");

	readFileStudent(fileIn_CSV, list);

	fclose(fileIn_CSV);

	FILE *fileIn = _wfopen(L"example.htm", L"r");
	if (!fileIn)
		printf("Error\n");

	FILE *fileOut;
	for (int i = 0; i < list.nStudent; i++)
	{
		fileOut = _wfopen(nameFileOut[i], L"w");

		writeFileStudent(fileIn, fileOut, list[i]);

		fclose(fileOut);
	}
	fclose(fileIn);

	delete[] list.student;
	_getch();
	return 0;
}