#include"fileHTML.h"

int main()
{
	STUDENT student;
	FILE *fileIn_CSV = _wfopen(L"TableInfo.csv", L"r");
	if (!fileIn_CSV)
		printf("Error\n");
	readFileStudent(fileIn_CSV, student);
	fclose(fileIn_CSV);


	FILE *fileIn = _wfopen(L"example.htm", L"r");
	if (!fileIn)
		printf("Error\n");
	FILE *fileOut = _wfopen(L"1712825.htm", L"w");
	writeFileStudent(fileIn, fileOut, student);

	fclose(fileOut);
	fclose(fileIn);

	_getch();
	return 0;
}