#include"fileHTML.h"

// MY FUNCTION
void FGETWS(wchar_t *ws, int maxSizeWS, FILE *fileIn, wchar_t *mark) // hàm đọc chuỗi wchar_t đến các dấu ngắt câu của chuỗi mark thì dừng
{
	int lengthMark = wcslen(mark); // độ dài chuỗi chứa các dấu ngắt câu
	int isMatchMark; // cờ kiểm tra kí tự wc có trùng với mark[i] hay không 
	int indexWS = 0; // chỉ số của chuỗi ws
	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn

	while (true)
	{
		wc = fgetwc(fileIn);
		for (int i = 0; i < lengthMark; i++)
		{
			isMatchMark = 0;
			if (wc == *(mark + i))
			{
				isMatchMark = 1;
				break;
			}
		}
		if (indexWS == 0 && isMatchMark == 1) // kí tự đầu là dấu ngắt câu thì đọc bỏ
			continue;
		if (isMatchMark || indexWS == maxSizeWS - 1) // trùng hoặc chỉ số indexWS vượt quá maxSizeWS
		{
			*(ws + indexWS) = 0; // kết thúc chuỗi ws
			break;
		}
		else
		{
			*(ws + indexWS) = wc; // thêm kí tự wc vào cuối chuỗi ws
			indexWS++;
		}
	}
}
void FGETS(char *s, int maxSizeS, FILE *fileIn, char *mark) // hàm đọc chuỗi char đến các dấu ngắt câu của chuỗi mark thì dừng
{
	int lengthMark = strlen(mark); // độ dài chuỗi chứa các dấu ngắt câu
	int isMatchMark; // cờ kiểm tra kí tự c có trùng với mark[i] hay không 
	int indexS = 0; // chỉ số của chuỗi s
	char c; // biến tạm để lữu từng kí tự đọc ra từ fileIn

	while (true)
	{
		c = fgetc(fileIn);
		for (int i = 0; i < lengthMark; i++)
		{
			isMatchMark = 0;
			if (c == *(mark + i))
			{
				isMatchMark = 1;
				break;
			}
		}
		if (indexS == 0 && isMatchMark == 1) // kí tự đầu là dấu ngắt câu thì đọc bỏ
			continue;
		if (isMatchMark || indexS == maxSizeS - 1) // trùng hoặc chỉ số indexS vượt quá maxSizeS
		{
			*(s + indexS) = 0; // kết thúc chuỗi s
			break;
		}
		else
		{
			*(s + indexS) = c; // thêm kí tự wc vào cuối chuỗi ws
			indexS++;
		}
	}
}
void readFileIn_WriteFileOut_ToWS(FILE *fileOut, FILE *fileIn, wchar_t* ws) // hàm đọc fileIn và ghi fileOut cho đến lúc phát hiện chuỗi ws thì ghi luôn chuỗi ws và dừng
{
	int lengthWS = wcslen(ws);
	int isMatchWS = 0; // cờ kiểm tra kí tự wc có trùng với ws[i] hay không 

	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn
	while (true)
	{
		wc = fgetwc(fileIn);
		fputwc(wc, fileOut); // thêm kí tự wc vào fileOut

		if (wc == *ws) // kí tự wc = kí tự đầu tiên của chuỗi ws
		{
			for (int i = 1; i < lengthWS; i++) // kiểm tra các kí tự tiếp theo của chuỗi ws có bằng các wc tiếp theo của fileIn hay không
			{
				isMatchWS = 1; // giả sử trùng 

				wc = fgetwc(fileIn);
				fputwc(wc, fileOut);

				if (wc != *(ws + i))
				{
					isMatchWS = 0;
					break;
				}
			}
		}
		if (isMatchWS) // nếu trùng
			break;
	}
}

void readFileStudent(FILE *fileIn, STUDENT &student)
{
	// đọc bỏ 3 kí tự rác đầu file CSV
	for (int i = 1; i <= 3; i++)
		fgetc(fileIn);
	// đọc ID sinh viên 
	FGETS(student.ID, 11, fileIn, ",");
	// đọc Họ và Tên sinh viên
	FGETWS(student.fullName, 31, fileIn, L",");
	// đọc Khoa đang học của sinh viên
	FGETWS(student.faculty, 31, fileIn, L",");
	// đọc Niên Khóa vào trường
	fscanf(fileIn, "%d", &student.yearSchool);
	// đọc Ngày Sinh của sinh viên
	FGETS(student.birthDay, 11, fileIn, ",");
	// đọc Link hình ảnh cá nhân của sinh viên
	FGETS(student.linkImage, 31, fileIn, ",");
	// đọc Mô Tả bản thân của sinh viên
	FGETWS(student.description, 1000, fileIn, L"\"");
	// đọc bỏ kí tự ,
	fgetwc(fileIn);
	// đọc Sở Thich cá nhân của sinh viên
	FGETWS(student.hobby, 1000, fileIn, L"\"");

}
void writeFileStudent(FILE *fileIn, FILE *fileOut, STUDENT student)
{
	wchar_t *stringTitle = title;
	wchar_t *stringClassFullName = classFullName;
	wchar_t *stringClassFaculty = classFaculty;
	wchar_t *stringClassLinkImage = classLinkImage;
	wchar_t *stringClassInfo = classInfo;

	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn

	// tim chuỗi <title>
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringTitle); // đọc fileIn-ghi fileOut đến chuỗi stringTitle

	fputws(student.fullName, fileOut); // ghi Họ&Tên sinh viên mới vào fileOut 

	while ((wc = fgetwc(fileIn)) != '<'); // đọc bỏ Họ&Tên mẫu trong fileIn

	fseek(fileIn, ftell(fileIn) - 1, SEEK_SET); // lùi con trỏ chỉ vị ra sau dấu '<' để đọc tiếp
	// tìm chuỗi stringClassFullName
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringClassFullName); // đọc fileIn-ghi fileOut đến chuỗi stringClassFullName

	fputws(student.fullName, fileOut); // ghi Họ&Tên sinh viên mới vào fileOut
	fputwc('-', fileOut); // ghi kí tự '-' vào fileOut
	fputs(student.ID, fileOut); // ghi ID sinh viên mới vào fileOut

	while ((wc = fgetwc(fileIn)) != '<'); // đọc bỏ Họ&Tên-ID mẫu trong fileIn

	fseek(fileIn, ftell(fileIn) - 1, SEEK_SET); // lùi con trỏ chỉ vị ra sau dấu '<' để đọc tiếp
	// tìm chuỗi stringClassFaculty
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringClassFaculty); // đọc fileIn-ghi fileOut đến chuỗi stringClassFaculty

	fputws(student.faculty, fileOut); // ghi Khoa của sinh viên mới vào fileOut

	while ((wc = fgetwc(fileIn)) != '<'); // đọc bỏ Khoa mẫu trong fileIn

	fseek(fileIn, ftell(fileIn) - 1, SEEK_SET); // lùi con trỏ chỉ vị ra sau dấu '<' để đọc tiếp
	// tìm chuỗi stringClassLinkImage
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringClassLinkImage); // đọc fileIn-ghi fileOut đến chuỗi stringClassLinkImage

	fputs(student.linkImage, fileOut); // ghi Link Ảnh Cá Nhân của sinh viên mới vào fileOut

	while ((wc = fgetwc(fileIn)) != '\"'); // đọc bỏ Link Ảnh Cá Nhân mẫu trong fileIn

	fseek(fileIn, ftell(fileIn) - 1, SEEK_SET); // lùi con trỏ chỉ vị ra sau dấu '\"' để đọc tiếp
}