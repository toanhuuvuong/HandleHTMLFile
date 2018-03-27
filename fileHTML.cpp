#include"fileHTML.h"

void readFileStudent(FILE *fileIn, STUDENT &student)
{
	int index;
	// read ID
	index = 0;
	char c;
	while (true)
	{
		c = fgetc(fileIn);
		if (c != ',')
		{
			*(student.ID + index) = c;
			index++;
		}
		else
		{
			*(student.ID + index) = '\0';
			break;
		}
	}
	// read fullName
	index = 0;
	wchar_t wc;
	while (true)
	{
		wc = fgetwc(fileIn);
		if (wc != ',')
		{
			*(student.fullName + index) = wc;
			index++;
		}
		else
		{
			*(student.fullName + index) = '\0';
			break;
		}
	}
	// read faculty
	index = 0;
	while (true)
	{
		wc = fgetwc(fileIn);
		if (wc != ',')
		{
			*(student.faculty + index) = wc;
			index++;
		}
		else
		{
			*(student.faculty + index) = '\0';
			break;
		}
	}
}

void writeFileStudent(FILE *fileIn, FILE *fileOut, STUDENT student)
{
	wchar_t *stringClassFullName = classFullName;
	wchar_t *stringTitle = title;
	wchar_t *stringClassFaculty = classFaculty;

	int isMatchClassFullName = 0, isMatchTitle = 0, isMatchClassFaculty = 0;
	wchar_t wc;

	while (!feof(fileIn))
	{
		wc = fgetwc(fileIn);
		fputwc(wc, fileOut);
		// tim <title>
		if (wc == '<' && isMatchTitle == 0) // tim 1 lan duy nhat
		{
			isMatchTitle = 1;
			for (int i = 1; i < wcslen(stringTitle); i++)
			{
				wc = fgetwc(fileIn);
				wc = fputc(wc, fileOut);
				if (*(stringTitle + i) != wc)
				{
					isMatchTitle = 0;
					break;
				}
			}
			if (isMatchTitle)
			{
				fputws(student.fullName, fileOut);
				while (wc != '<')
					wc = fgetwc(fileIn);
				fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
				continue;
			}
		}
		// tim cac class bat dau bang ki tu 'P'
		if (wc == 'P' && isMatchClassFullName == 0)
		{
			// kiem tra chuoi dang xet tiep theo co = stringClassFullName
			isMatchClassFullName = 1;
			for (int i = 1; i < wcslen(stringClassFullName); i++)
			{
				wc = fgetwc(fileIn);
				wc = fputc(wc, fileOut);
				if (*(stringClassFullName + i) != wc)
				{
					isMatchClassFullName = 0;
					break;
				}
			}
			if (isMatchClassFullName)
			{
				// Viet hoa tat ca cac ki tu trong fullName
				for (int i = 0; i < wcslen(student.fullName); i++)
					*(student.fullName + i) = towupper(*(student.fullName + i));

				fputws(student.fullName, fileOut);
				fputwc('-', fileOut);
				fputs(student.ID, fileOut);
				while (wc != '<')
					wc = fgetwc(fileIn);
				fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
				continue;
			}
		}
		if (wc == 'P' && isMatchClassFaculty == 0)
		{	// 
			isMatchClassFaculty = 1;
			for (int i = 1; i < wcslen(stringClassFaculty); i++)
			{
				wc = fgetwc(fileIn);
				wc = fputc(wc, fileOut);
				if (*(stringClassFaculty + i) != wc)
				{
					isMatchClassFaculty = 0;
					break;
				}
			}
			if (isMatchClassFaculty)
			{
				// Viet hoa tat ca cac ki tu trong Faculty
				for (int i = 0; i < wcslen(student.faculty); i++)
					*(student.faculty + i) = towupper(*(student.faculty + i));

				fputws(student.faculty, fileOut);
				while (wc != '<')
					wc = fgetwc(fileIn);
				fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
				continue;
			}
		}
	}
}