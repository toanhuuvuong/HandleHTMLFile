#include"fileHTML.h"

// HÀM PHỤ
// hàm construtor
STUDENT::student()
{
	ID = NULL;
	fullName = NULL;
	faculty = NULL;
	yearSchool = 0;
	birthDay = NULL;
	Email = NULL;
	linkImage = NULL;
	description = NULL;
	hobby[0] = NULL;
	hobby[1] = NULL;
}
// hàm đọc fileIn đến các dấu ngắt câu của chuỗi mark (đọc luôn dấu ngắt câu đó) và dừng ==> sau đó lưu chuỗi vừa đọc vào chuỗi ws (không tính dấu ngắt câu)
void FGETWS(wchar_t *&ws, int maxSizeWS, FILE *fileIn, wchar_t *mark) 
{
	int lengthMark = wcslen(mark); // độ dài chuỗi chứa các dấu ngắt câu
	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn
	int isMatchMark; // cờ kiểm tra kí tự wc có trùng với mark[i] hay không 
	int indexWS = 0; // chỉ số của chuỗi ws


	while (true)
	{
		wc = fgetwc(fileIn);
		for (int i = 0; i < lengthMark; i++)
		{
			isMatchMark = 0; // giả sử chưa đến dấu ngắt câu
			if (wc == *(mark + i))
			{
				isMatchMark = 1; // đã tìm được dấu ngắt câu
				break;
			}
		}
		if (indexWS == 0 && isMatchMark == 1) // kí tự đầu là dấu ngắt câu thì đọc bỏ
			continue;
		if (isMatchMark || indexWS == maxSizeWS - 1) // tìm được dấu ngắt câu hoặc chỉ số indexWS vượt quá maxSizeWS
		{
			ws = (wchar_t*)realloc(ws, (indexWS + 1)*sizeof(wchar_t));
			*(ws + indexWS) = 0; // kết thúc chuỗi ws
			break;
		}
		else
		{
			ws = (wchar_t*)realloc(ws, (indexWS + 1)*sizeof(wchar_t)); // nới rộng kích thước chuỗi ra 1 đơn vị
			*(ws + indexWS) = wc; // thêm kí tự wc vào cuối chuỗi ws
			indexWS++;
		}
	}
}
// tương tự hàm FGETWS nhưng với kiểu dữ liệu là char
void FGETS(char *&s, int maxSizeS, FILE *fileIn, char *mark)
{
	int lengthMark = strlen(mark);
	char c;
	int isMatchMark; 
	int indexS = 0; 

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
		if (indexS == 0 && isMatchMark == 1)
			continue;
		if (isMatchMark || indexS == maxSizeS - 1) 
		{
			s = (char*)realloc(s, (indexS + 1)*sizeof(char));
			*(s + indexS) = 0;
			break;
		}
		else
		{
			s = (char*)realloc(s, (indexS + 1)*sizeof(char));
			*(s + indexS) = c;
			indexS++;
		}
	}
}
// hàm đọc fileIn(HTML) và ghi fileOut cho đến lúc phát hiện chuỗi ws thì (ghi luôn chuỗi ws) và dừng
bool readFileIn_WriteFileOut_ToWS(FILE *fileOut, FILE *fileIn, wchar_t* ws)
{
	int lengthWS = wcslen(ws); // độ dài chuỗi ws
	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn
	int isMatchWS = 0; // cờ kiểm tra kí tự wc có trùng với ws[i] hay không 

	while (!feof(fileIn))
	{
		wc = fgetwc(fileIn); // vừa đọc kí tự wc từ fileIn
		fputwc(wc, fileOut); // vừa thêm kí tự wc vào fileOut

		if (wc == *ws) // kí tự wc = kí tự đầu tiên của chuỗi ws
		{
			isMatchWS = 1; // giả sử trùng - TH ws có 1 kí tự thì điều kiện (wc == *ws) đã thỏa (cờ = 1)

			for (int i = 1; i < lengthWS; i++) // TH ws có 2 kí tự trở lên - kiểm tra các kí tự tiếp theo của chuỗi ws có bằng các wc tiếp theo của fileIn hay không
			{
				isMatchWS = 1; // giả sử trùng 

				wc = fgetwc(fileIn);
				fputwc(wc, fileOut);

				if (wc != *(ws + i))
				{
					isMatchWS = 0; // không trùng
					break;
				}
			}
		}
		if (isMatchWS) // nếu trùng
			return true;
	}
	return false; // nếu không tìm được chuỗi ws trong fileIn
}
// đọc fileIn(HTML) đến chuỗi ws (không ghi chuỗi ws) và dừng 
bool readFileIn_ToWS(FILE *fileIn, wchar_t *ws) 
{
	int lengthWS = wcslen(ws);
	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn
	int isMatchWS = 0; // cờ kiểm tra kí tự wc có trùng với ws[i] hay không 
	int pos; // đánh dấu vị trí tìm được kí tự đầu tiên của chuỗi ws = kí tự wc đọc từ fileIn

	while (!feof(fileIn))
	{
		wc = fgetwc(fileIn);

		if (wc == *ws && !feof(fileIn)) // kí tự wc đọc từ fileIn = kí tự đầu tiên của chuỗi ws
		{
			pos = ftell(fileIn); // đánh dấu vị trí con trỏ chỉ vị ở đầu chuỗi ws ====> với ý định không đọc luôn chuỗi này mà trả về vị trí pos

			isMatchWS = 1; // giả sử trùng - TH ws có 1 kí tự thì điều kiện (wc == *ws) đã thỏa (cờ = 1)

			for (int i = 1; i < lengthWS; i++) // // TH ws có 2 kí tự trở lên - kiểm tra các kí tự tiếp theo của chuỗi ws có bằng các wc tiếp theo của fileIn hay không
			{
				isMatchWS = 1; // giả sử trùng 

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
	return false; // nếu không tìm được chuỗi ws trong fileIn
}
// kiểm tra trường dữ liệu trong struct Sinh Viên có được chọn hay không
bool isInMenu(int *Menu, int nMenu, int choose)
{
	for (int i = 0; i < nMenu; i++)
	{
		if (choose == *(Menu + i))
			return true;
	}
	return false;
}
// hàm hủy
void destroyList(LIST &list)
{
	for (int i = 0; i < list.nStudent; i++)
	{
		free(list[i].ID);
		free(list[i].fullName);
		free(list[i].faculty);
		free(list[i].birthDay);
		free(list[i].Email);
		free(list[i].linkImage);
		free(list[i].description);
		free(list[i].hobby[0]);
		free(list[i].hobby[1]);
	}
	delete[] list.student;
}
//==============================================================================================================================================
// HÀM CHÍNH
// hàm đọc danh sách sinh viên trong fileIn(CSV)
void readFileCSV(FILE *fileIn, LIST &list)
{
	while (fgetwc(fileIn) != '\n'); // đọc bỏ hàng đầu của file CSV

	for (int i = 0; i < list.nStudent; i++)
	{
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
		//==============================BA TRƯỜNG HỢP ĐẶC BIỆT CÓ THỂ NGĂN CÁCH NHAU BẰNG DẤU , HOẶC DẤU " ================================
		/*    1.	" " "
			  2.	" " ,
			  3.	" , "
			  4.	" , ,
			  5.	, " "
			  6.	, " ,
			  7.	, , "
			  8.	, , ,
			  */
		if (fgetwc(fileIn) == '\"') // sau khi đọc xong linkImage đọc thử 1 kí tự tiếp theo của fileIn và kiểm tra 
		{
			FGETWS(list[i].description, 1000, fileIn, L"\""); // đọc Mô Tả bản thân của sinh viên
			fgetwc(fileIn); // đọc bỏ dấu ,
			if (fgetwc(fileIn) == '\"')
			{
				FGETWS(list[i].hobby[0], 1000, fileIn, L"\""); // đọc Sở Thích 1 cá nhân của sinh viên
				fgetwc(fileIn); // đọc bỏ dấu ,
				if (fgetwc(fileIn) == '\"')
				{
					FGETWS(list[i].hobby[1], 1000, fileIn, L"\""); // đọc Sở Thích 2 cá nhân của sinh viên
					fgetc(fileIn); // đọc bỏ kí tự \n (là kí tự ngăn cách 2 sinh viên trên 2 dòng) ===> theo định dạng của file CSV
				}// TH1------------------------------------------------------------------------------------------------------------------------
				else
				{
					fseek(fileIn, ftell(fileIn) - 1, SEEK_SET); // lui con trỏ chỉ vị xuống 1 đơn vị (vì đã đọc lố 1 kí tự đầu của nội dung Sở Thích 2)
					FGETWS(list[i].hobby[1], 1000, fileIn, L"\n");
				}// TH2------------------------------------------------------------------------------------------------------------------------
			}
			else
			{
				fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
				FGETWS(list[i].hobby[0], 1000, fileIn, L",");
				if (fgetwc(fileIn) == '\"')
				{
					FGETWS(list[i].hobby[1], 1000, fileIn, L"\"");
					fgetc(fileIn);
				}// TH3------------------------------------------------------------------------------------------------------------------------
				else
				{
					fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
					FGETWS(list[i].hobby[1], 1000, fileIn, L"\n");
				}// TH4------------------------------------------------------------------------------------------------------------------------
			}
		}
		else
		{
			fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
			FGETWS(list[i].description, 1000, fileIn, L",");

			if (fgetwc(fileIn) == '\"')
			{
				FGETWS(list[i].hobby[0], 1000, fileIn, L"\"");
				fgetwc(fileIn);
				if (fgetwc(fileIn) == '\"')
				{
					FGETWS(list[i].hobby[1], 1000, fileIn, L"\"");
					fgetc(fileIn);
				}// TH5------------------------------------------------------------------------------------------------------------------------
				else
				{
					fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
					FGETWS(list[i].hobby[1], 1000, fileIn, L"\n");
				}// TH6------------------------------------------------------------------------------------------------------------------------
			}
			else
			{
				fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
				FGETWS(list[i].hobby[0], 1000, fileIn, L",");
				if (fgetwc(fileIn) == '\"')
				{
					FGETWS(list[i].hobby[1], 1000, fileIn, L"\"");
					fgetc(fileIn);
				}// TH7------------------------------------------------------------------------------------------------------------------------
				else
				{
					fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
					FGETWS(list[i].hobby[1], 1000, fileIn, L"\n");
				}// TH8------------------------------------------------------------------------------------------------------------------------
			}
		}
	}
}
// hàm vừa đọc fileIn(HTML) vừa ghi fileOut
void writeOneStudentInFileCSV(FILE *fileIn, FILE *fileOut, STUDENT student, int *Menu, int nMenu)
{
	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn

	// tìm chuỗi <title> ---------------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, title); // đọc fileIn-ghi fileOut đến chuỗi title

	if (isInMenu(Menu, nMenu, 2))
		fputws(student.fullName, fileOut); // ghi Họ&Tên sinh viên mới vào fileOut 
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</title>"); // đọc bỏ Họ&Tên mẫu trong fileIn
	// tìm chuỗi classFullName ---------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classFullName); // đọc fileIn-ghi fileOut đến chuỗi classFullName

	if (isInMenu(Menu, nMenu, 2))
		fputws(student.fullName, fileOut); // ghi Họ&Tên sinh viên mới vào fileOut 
	else
		fputws(L"", fileOut); // ghi trống vào fileOut
	fputwc('-', fileOut); // ghi kí tự '-' vào fileOut
	if (isInMenu(Menu, nMenu, 1))
		fputs(student.ID, fileOut); // ghi ID sinh viên mới vào fileOut
	else
		fputs("", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</span>");// đọc bỏ Họ&Tên-ID mẫu trong fileIn
	// tìm chuỗi classFaculty ---------------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classFaculty); // đọc fileIn-ghi fileOut đến chuỗi classFaculty

	if (isInMenu(Menu, nMenu, 3))
		fputws(student.faculty, fileOut); // ghi Khoa sinh viên mới vào fileOut 
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</div>"); // đọc bỏ Khoa mẫu trong fileIn
	// tìm chuỗi classEmail ---------------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classEmail); // đọc fileIn-ghi fileOut đến chuỗi classEmail

	if (isInMenu(Menu, nMenu, 7))
		fputs(student.Email, fileOut); // ghi Email sinh viên mới vào fileOut 
	else
		fputs("", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</div>"); // đọc bỏ Khoa mẫu trong fileIn
	// tìm chuỗi classLinkImage ---------------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classLinkImage); // đọc fileIn-ghi fileOut đến chuỗi classLinkImage

	if (isInMenu(Menu, nMenu, 6))
		fputs(student.linkImage, fileOut); // ghi Link Ảnh Cá Nhân sinh viên mới vào fileOut 
	else
		fputs("", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"\""); // đọc bỏ Link Ảnh Cá Nhân mẫu trong fileIn
	// tìm chuỗi classInfo <thông tin sinh viên> -----------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classInfo); // đọc fileIn-ghi fileOut đến chuỗi classInfo

	if (isInMenu(Menu, nMenu, 2))
		addLine(topicFullName, student.fullName, fileOut);               // thông tin Họ&Tên
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	if (isInMenu(Menu, nMenu, 1))
		addLine(topicID, student.ID, fileOut);							// thông tin ID
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	if (isInMenu(Menu, nMenu, 3))
		addLine(topicFaculty, student.faculty, fileOut);                // thông tin Khoa
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	if (isInMenu(Menu, nMenu, 5))
		addLine(topicBirthDay, student.birthDay, fileOut);              // thông tin Ngày Sinh
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	if (isInMenu(Menu, nMenu, 7))
		addLine(topicEmail, student.Email, fileOut);                     // thông tin Ngày Sinh
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</ul>"); // đọc bỏ Thông Tin mẫu trong fileIn
	// tìm chuỗi classHobby <sở thích cá nhân> --------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classHobby); // đọc fileIn-ghi fileOut đến chuỗi classHobby

	if (isInMenu(Menu, nMenu, 9))
	{
		addLine(topicHobby1, student.hobby[0], fileOut);                 // ghi Sở Thích 1 của sinh viên mới vào fileOut
		addLine(topicHobby2, student.hobby[1], fileOut);                 // ghi Sở Thích 2 của sinh viên mới vào fileOut
	}
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</ul>"); // đọc bỏ Sở Thích mẫu trong fileIn
	// tìm chuỗi classDescription <mô tả bản thân> -----------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classDescription); // đọc fileIn-ghi fileOut đến chuỗi classDescription

	if (isInMenu(Menu, nMenu, 8))
		fputws(student.description, fileOut);                 // ghi Mô Tả Bản Thân của sinh viên mới vào fileOut
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</div>"); // đọc bỏ Mô Tả Bản Thân mẫu trong fileIn
	// tìm chuỗi classFooter <cuối trang> --------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classFooter); // đọc fileIn-ghi fileOut đến chuỗi classFooter

	if (isInMenu(Menu, nMenu, 4))
	{
		fprintf(fileOut, "%d", student.yearSchool);
		fputs("</br>\n\t\t\t\t\t", fileOut);
	}
	else
		fputws(L"", fileOut); // ghi trống vào fileOut 

	readFileIn_ToWS(fileIn, L"</br>");

	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, KTLT);
	fputs("TH2018/03", fileOut);
	fputs("</br>\n\t\t\t\t\t", fileOut);

	fputs("1712825", fileOut);
	fputs(" - ", fileOut);
	fputws(L"VÆ°Æ¡ng Há»¯u ToÃ n", fileOut);
	fputs("</br>\n\t\t\t\t\t", fileOut);

	readFileIn_ToWS(fileIn, L"</div>"); // đọc bỏ Thông Tin Cuối Trang mẫu của fileIn
	// -----------------------------------------------------------------------------------------------------------------------------------------------
	// đã thay thế hết tất cả các vị trí yêu cầu
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, L"</html>"); //====> đọc và ghi fileOut đến cuối fileIn
}
