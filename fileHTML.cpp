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
bool readFileIn_WriteFileOut_ToWS(FILE *fileOut, FILE *fileIn, wchar_t* ws) // hàm đọc fileIn và ghi fileOut cho đến lúc phát hiện chuỗi ws thì ghi luôn chuỗi ws và dừng
{
	int lengthWS = wcslen(ws);
	int isMatchWS = 0; // cờ kiểm tra kí tự wc có trùng với ws[i] hay không 

	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn
	while (!feof(fileIn))
	{
		wc = fgetwc(fileIn);
		fputwc(wc, fileOut); // thêm kí tự wc vào fileOut

		if (wc == *ws) // kí tự wc = kí tự đầu tiên của chuỗi ws
		{
			isMatchWS = 1; // giả sử trùng - TH ws có 1 kí tự thì điều kiện (wc == *ws) đã thỏa (cờ = 1)

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
			return true;
	}
	return false;
}
bool readFileIn_ToWS(FILE *fileIn, wchar_t *ws) // đọc fileIn đến chuỗi ws thì dừng không tính chuỗi ws
{
	int lengthWS = wcslen(ws);
	int isMatchWS = 0; // cờ kiểm tra kí tự wc có trùng với ws[i] hay không 
	int pos;

	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn
	while (!feof(fileIn))
	{
		wc = fgetwc(fileIn);

		if (wc == *ws && !feof(fileIn)) // kí tự wc = kí tự đầu tiên của chuỗi ws
		{
			isMatchWS = 1; // giả sử trùng - TH ws có 1 kí tự thì điều kiện (wc == *ws) đã thỏa (cờ = 1)

			pos = ftell(fileIn); // lấy vị trí con trỏ chỉ vị ở đầu chuỗi ws ====> với ý định không đọc luôn chuỗi này mà trả về vị trí pos

			for (int i = 1; i < lengthWS; i++) // kiểm tra các kí tự tiếp theo của chuỗi ws có bằng các wc tiếp theo của fileIn hay không
			{
				isMatchWS = 1; // giả sử trùng - TH ws có nhiều kí tự

				wc = fgetwc(fileIn);

				if (wc != *(ws + i))
				{
					isMatchWS = 0;
					break;
				}
			}
		}
		if (isMatchWS) // nếu trùng
		{
			fseek(fileIn, pos - 1, SEEK_SET); // trả con trỏ chỉ vị về đầu chuỗi ws
			return true;
		}
	}
	return false;
}

void readFileStudent(FILE *fileIn, LIST &list)
{
	for (int i = 0; i < list.nStudent; i++)
	{
		if (i == 0)
		{
			// đọc bỏ 3 kí tự rác đầu file CSV
			for (int i = 1; i <= 3; i++)
				fgetc(fileIn);
		}
		else
			fgetc(fileIn); // đọc bỏ kí tự \n
		// đọc ID sinh viên 
		FGETS(list[i].ID, 11, fileIn, ",");
		// đọc Họ và Tên sinh viên
		FGETWS(list[i].fullName, 31, fileIn, L",");
		// đọc Khoa đang học của sinh viên
		FGETWS(list[i].faculty, 31, fileIn, L",");
		// đọc Niên Khóa vào trường
		fscanf(fileIn, "%d", &list[i].yearSchool);
		// đọc Ngày Sinh của sinh viên
		FGETS(list[i].birthDay, 11, fileIn, ",");
		// đọc email sinh viên
		FGETS(list[i].Email, 31, fileIn, ",");
		// đọc Link hình ảnh cá nhân của sinh viên
		FGETS(list[i].linkImage, 31, fileIn, ",");
		//==============================HAI TRƯỜNG HỢP ĐẶC BIỆT CÓ THỂ NGĂN CÁCH NHAU BẰNG DẤU , HOẶC DẤU " ================================
		// đọc Mô Tả bản thân của sinh viên
		if (fgetwc(fileIn) == '\"')
		{
			FGETWS(list[i].description, 1000, fileIn, L"\"");
			// đọc Sở Thich cá nhân của sinh viên
			fgetwc(fileIn); // đọc bỏ dấu ,
			if (fgetwc(fileIn) == '\"')
				FGETWS(list[i].hobby, 1000, fileIn, L"\"");
			else
			{
				fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
				FGETWS(list[i].hobby, 1000, fileIn, L",");
			}
		}
		else
		{
			fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
			FGETWS(list[i].description, 1000, fileIn, L",");
			FGETWS(list[i].hobby, 1000, fileIn, L",");
		}
	}
}
void writeFileStudent(FILE *fileIn, FILE *fileOut, STUDENT student)
{
	wchar_t *stringTitle = title;
	wchar_t *stringClassFullName = classFullName;
	wchar_t *stringClassFaculty = classFaculty;
	wchar_t *stringClassEmail = classEmail;
	wchar_t *stringClassLinkImage = classLinkImage;
	wchar_t *stringClassInfo = classInfo;
	wchar_t *stringClassHobby = classHobby;
	wchar_t *stringClassDescription = classDescription;
	wchar_t *stringFooter = classFooter;
	wchar_t *stringKTLT = KTLT;

	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn

	rewind(fileIn);
	// tìm chuỗi <title>
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringTitle); // đọc fileIn-ghi fileOut đến chuỗi stringTitle

	fputws(student.fullName, fileOut); // ghi Họ&Tên sinh viên mới vào fileOut 

	readFileIn_ToWS(fileIn, L"<"); // đọc bỏ Họ&Tên mẫu trong fileIn
	// tìm chuỗi stringClassFullName
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringClassFullName); // đọc fileIn-ghi fileOut đến chuỗi stringClassFullName

	fputws(student.fullName, fileOut); // ghi Họ&Tên sinh viên mới vào fileOut
	fputwc('-', fileOut); // ghi kí tự '-' vào fileOut
	fputs(student.ID, fileOut); // ghi ID sinh viên mới vào fileOut

	readFileIn_ToWS(fileIn, L"<");// đọc bỏ Họ&Tên-ID mẫu trong fileIn
	// tìm chuỗi stringClassFaculty
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringClassFaculty); // đọc fileIn-ghi fileOut đến chuỗi stringClassFaculty

	fputws(student.faculty, fileOut); // ghi Khoa của sinh viên mới vào fileOut

	readFileIn_ToWS(fileIn, L"<"); // đọc bỏ Khoa mẫu trong fileIn
	// tìm chuỗi stringClassEmail
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringClassEmail); // đọc fileIn-ghi fileOut đến chuỗi stringClassEmail

	fputs(student.Email, fileOut); // ghi Email của sinh viên mới vào fileOut

	readFileIn_ToWS(fileIn, L"<"); // đọc bỏ Khoa mẫu trong fileIn
	// tìm chuỗi stringClassLinkImage
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringClassLinkImage); // đọc fileIn-ghi fileOut đến chuỗi stringClassLinkImage

	fputs(student.linkImage, fileOut); // ghi Link Ảnh Cá Nhân của sinh viên mới vào fileOut

	readFileIn_ToWS(fileIn, L"\""); // đọc bỏ Link Ảnh Cá Nhân mẫu trong fileIn

	// tìm chuỗi stringClassInfo <thông tin sinh viên>
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringClassInfo); // đọc fileIn-ghi fileOut đến chuỗi stringClassInfo

	fputws(L"<li>Há» vÃ  tÃªn: ", fileOut);
	fputws(student.fullName, fileOut);                 // thông tin Họ&Tên
	fputws(L"</li>\n\t\t\t\t\t\t\t\t", fileOut);

	fputws(L"<li>MSSV: ", fileOut);
	fputs(student.ID, fileOut);                       // thông tin ID
	fputws(L"</li>\n\t\t\t\t\t\t\t\t", fileOut);

	fputws(L"<li>Sinh viÃªn khoa: ", fileOut);
	fputws(student.faculty, fileOut);                 // thông tin Khoa
	fputws(L"</li>\n\t\t\t\t\t\t\t\t", fileOut);

	fputws(L"<li>NgÃ y sinh: ", fileOut);
	fputs(student.birthDay, fileOut);                 // thông tin Ngày Sinh
	fputws(L"</li>\n\t\t\t\t\t\t\t\t", fileOut);

	fputws(L"<li>Email: ", fileOut);
	fputs(student.Email, fileOut);                 // thông tin Ngày Sinh
	fputws(L"</li>\n\t\t\t\t\t\t\t\t", fileOut);

	readFileIn_ToWS(fileIn, L"</ul>"); // đọc bỏ Thông Tin mẫu trong fileIn
	// tìm chuỗi stringClassHobby <sở thích cá nhân>
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringClassHobby); // đọc fileIn-ghi fileOut đến chuỗi stringClassHobby

	fputws(student.hobby, fileOut);                 // ghi Sở Thích Cá Nhân của sinh viên mới vào fileOut

	readFileIn_ToWS(fileIn, L"</ul>"); // đọc bỏ Sở Thích mẫu trong fileIn
	// tìm chuỗi stringClassDescription <mô tả bản thân>
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringClassDescription); // đọc fileIn-ghi fileOut đến chuỗi stringClassDescription

	fputws(student.description, fileOut);                 // ghi Mô Tả Bản Thân của sinh viên mới vào fileOut

	readFileIn_ToWS(fileIn, L"<"); // đọc bỏ Mô Tả Bản Thân mẫu trong fileIn
	// tìm chuỗi stringFooter <cuối trang>
	//================================================================================================================
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringFooter); // đọc fileIn-ghi fileOut đến chuỗi stringFooter

	fprintf(fileOut, "%d", student.yearSchool);
	fputs("</br>\n\t\t\t\t\t", fileOut);
	readFileIn_ToWS(fileIn, L"<");

	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, stringKTLT);
	fputs("TH2018/03", fileOut);
	fputs("</br>\n\t\t\t\t\t", fileOut);

	fputs(student.ID, fileOut);
	fputs(" - ", fileOut);
	fputws(student.fullName, fileOut);
	fputs("</br>\n\t\t\t\t\t", fileOut);

	readFileIn_ToWS(fileIn, L"</div>"); // đọc bỏ
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, L"</html>");
}
