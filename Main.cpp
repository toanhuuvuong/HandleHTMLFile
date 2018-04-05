#include"fileHTML.h"

// Danh sách tên của các profile xuất ra
wchar_t *nameFileOut[10] = { L"1.htm", L"2.htm", L"3.htm", L"4.htm", L"5.htm", L"6.htm", L"7.htm", L"8.htm", L"9.htm", L"10.htm" };

int main()
{
	int *Menu = NULL;
	int nMenu = 0;
	int choose;

	printf("==================MENU====================\n");
	printf("1. ID\n");
	printf("2. Full Name\n");
	printf("3. Faculty\n");
	printf("4. Year School\n");
	printf("5. Birthday\n");
	printf("6. Link Image\n");
	printf("7. Email\n");
	printf("8. Description\n");
	printf("9. Hobby\n\n");
	printf("Chon cac tuy chon ban muon HIEN THI tren TRANG CA NHAN (Nhan Enter va  Ctr + Z de ket thuc tuy chon): ");
	while (scanf("%d%*c", &choose) > 0)
	{
		Menu = (int*)realloc(Menu, (nMenu + 1)*sizeof(int));
		*(Menu + nMenu) = choose;
		nMenu++;
	}

	LIST list;
	list.nStudent = 10;
	list.student = new STUDENT[list.nStudent];

	FILE *fileIn_CSV = _wfopen(L"TableInfo.csv", L"r");
	if (!fileIn_CSV)
		printf("Error\n");

	readFileCSV(fileIn_CSV, list);

	fclose(fileIn_CSV);
	//==================================================================================================
	FILE *fileIn = _wfopen(L"example.htm", L"r");
	if (!fileIn)
		printf("Error\n");

	FILE *fileOut;
	for (int i = 0; i < list.nStudent; i++)
	{
		fileOut = _wfopen(nameFileOut[i], L"w");

		writeOneStudentInFileCSV(fileIn, fileOut, list[i], Menu, nMenu);

		fclose(fileOut);

		rewind(fileIn); // đưa con trỏ chỉ vị trở về đầu fileIn(HTML) để đọc tiếp sinh viên mới
	}
	fclose(fileIn);
	//==================================================================================================
	if (list.student)
		delete[] list.student;
	free(Menu);

	_getch();
	return 0;
}