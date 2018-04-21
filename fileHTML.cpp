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
	for (int i = 0; i < 100; i++)
		hobby[i] = NULL;
}
LIST::list()
{
	student = NULL;
	nStudent = 0;
	nHobbyOfOneStudent = NULL;
}
// hàm đọc fileIn(CSV) và lưu vào chuỗi ws đến dấu ngắt câu mark (cụ thể là dấu phẩy, dấu ngoặc kép và dấu \n) và cập nhật dấu ngắt câu mới
void FGETWS(wchar_t *&ws, const int &maxSizeWS, FILE *fileIn, char &mark)
{
	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn
	int indexWS = 0; // chỉ số của chuỗi ws
	/*	Có 6 trường hợp :
		TH1 :	"nội dung 1", "nội dung 2"
		TH2 :	"nội dung 1", nội dung 2
		TH3 :	"nội dung 1"\n
		TH4 :	,nội dung 1, "nội dung 2"
		TH5 :	,nội dung 1, nội dung 2
		TH6 :	,nội dung 1\n		*/
	while (true)
	{
		wc = fgetwc(fileIn);

		if (wc == '\n') // không tìm được mark nhưng tìm được kí tự \n kết thúc một dòng
		{
			ws = (wchar_t*)realloc(ws, (indexWS + 1)*sizeof(wchar_t));
			*(ws + indexWS) = 0; // kết thúc chuỗi ws
			mark = '\n';	// --> TH6
			break;
		}
		else if (wc != (wchar_t)mark) //--------------------------------------------------------------------------------------------------------------------
		{
			ws = (wchar_t*)realloc(ws, (indexWS + 1)*sizeof(wchar_t)); // nới rộng kích thước chuỗi ra 1 đơn vị
			*(ws + indexWS) = wc; // thêm kí tự wc vào cuối chuỗi ws
			indexWS++;
		}
		else // tìm được mark--------------------------------------------------------------------------------------------------------------------------------
		{
			ws = (wchar_t*)realloc(ws, (indexWS + 1)*sizeof(wchar_t));
			*(ws + indexWS) = 0; // kết thúc chuỗi ws
			//	Cập nhật lại mark
			switch (mark)
			{
			case '\"':
				wc = fgetwc(fileIn);
				if (wc == '\n')
					mark = '\n';		// --> TH3
				else if (wc == ',')
				{
					wc = fgetwc(fileIn);
					if (wc == '\"')
						mark = '\"';	// --> TH1
					else
					{
						fseek(fileIn, ftell(fileIn) - 1, SEEK_SET); // lùi con trỏ chỉ vị vì đọc lố sang nội dung tiếp theo
						mark = ',';		// -->TH2
					}
				}
				break;
			default: // mark == ','
				wc = fgetwc(fileIn);
				if (wc == '\"')
					mark = '\"';	// --> TH4
				else
				{
					fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
					mark = ',';		// --> TH5
				}
				break;
			}

			break;
		}

		if (indexWS > maxSizeWS) // chỉ số indexWS vượt quá maxSizeWS mà vẫn chưa tìm thấy mark-------------------------------------
		{
			ws = (wchar_t*)realloc(ws, (indexWS + 1)*sizeof(wchar_t));
			*(ws + indexWS) = 0; // kết thúc chuỗi ws
			wprintf(L"Lỗi vượt quá kích thước cho phép đọc\n");
			break;
		}
	}
}
// hàm tương tự FGETWS nhưng kiểu dữ liệu là char
void FGETS(char *&s, const int &maxSizeS, FILE *fileIn, char &mark)
{
	char c; // biến tạm để lữu từng kí tự đọc ra từ fileIn
	int indexS = 0; // chỉ số của chuỗi s

	while (true)
	{
		c = fgetc(fileIn);

		if (c == '\n') // không tìm được mark nhưng tìm được kí tự \n kết thúc một dòng
		{
			s = (char*)realloc(s, (indexS + 1)*sizeof(char));
			*(s + indexS) = 0; // kết thúc chuỗi s
			mark = '\n';	// --> TH6
			break;
		}
		else if (c != mark) //--------------------------------------------------------------------------------------------------------------------
		{
			s = (char*)realloc(s, (indexS + 1)*sizeof(char)); // nới rộng kích thước chuỗi ra 1 đơn vị
			*(s + indexS) = c; // thêm kí tự c vào cuối chuỗi s
			indexS++;
		}
		else // tìm được mark--------------------------------------------------------------------------------------------------------------------------------
		{
			s = (char*)realloc(s, (indexS + 1)*sizeof(char));
			*(s + indexS) = 0; // kết thúc chuỗi s
			//	Cập nhật lại mark
			switch (mark)
			{
			case '\"':
				c = fgetc(fileIn);
				if (c == '\n')
					mark = '\n';		// --> TH3
				else if (c == ',')
				{
					c = fgetc(fileIn);
					if (c == '\"')
						mark = '\"';	// --> TH1
					else
					{
						fseek(fileIn, ftell(fileIn) - 1, SEEK_SET); // lùi con trỏ chỉ vị vì đọc lố sang nội dung tiếp theo
						mark = ',';		// -->TH2
					}
				}
				break;
			default: // mark == ','
				c = fgetc(fileIn);
				if (c == '\"')
					mark = '\"';	// --> TH4
				else
				{
					fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
					mark = ',';		// --> TH5
				}
				break;
			}

			break;
		}
		if (indexS > maxSizeS) // chỉ số indexS vượt quá maxSizeS-------------------------------------------------------------------
		{
			s = (char*)realloc(s, (indexS + 1)*sizeof(char));
			*(s + indexS) = 0; // kết thúc chuỗi s
			wprintf(L"Lỗi vượt quá kích thước cho phép đọc\n");
			break;
		}
	}
}
// hàm tương tự FGETWS nhưng kiểu dữ liệu là int
void FSCANF_NUMBER(int &number, FILE *fileIn, char &mark)
{
	fscanf_s(fileIn, "%d", &number);
	fgetc(fileIn); // đọc bỏ dấu phẩy
	if (fgetc(fileIn) != '\"')
	{
		fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
		mark = ',';
	}
	else
		mark = '\"';
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
	wprintf(L"Lỗi không tìm thấy :(\n");
	return false; // nếu không tìm được chuỗi ws trong fileIn
}
// hàm chỉ đọc fileIn(HTML) đến chuỗi ws (không ghi chuỗi ws) và dừng 
bool readFileIn_ToWS(FILE *fileIn, wchar_t *ws) 
{
	int lengthWS = wcslen(ws);
	wchar_t wc; // biến tạm để lữu từng kí tự đọc ra từ fileIn
	int isMatchWS = 0; // cờ kiểm tra kí tự wc có trùng với ws[i] hay không 
	int pos; // đánh dấu vị trí tìm được kí tự đầu tiên của chuỗi ws = kí tự wc đọc từ fileIn

	while (!feof(fileIn))
	{
		wc = fgetwc(fileIn);

		if (wc == *ws) // kí tự wc đọc từ fileIn = kí tự đầu tiên của chuỗi ws
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
	wprintf(L"Lỗi không tìm thấy :(\n");
	return false; // nếu không tìm được chuỗi ws trong fileIn
}
// kiểm tra trường dữ liệu trong struct Sinh Viên có được chọn hay không
bool isInMenu(int *Menu, const int &nMenu, const int &choose)
{
	for (int i = 0; i < nMenu; i++)
	{
		if (choose == *(Menu + i))
			return true;
	}
	return false;
}
// hàm Menu
void optionMenu(int *&Menu, int &nMenu)
{
	Menu = NULL;
	nMenu = 0;
	int choose;
	wprintf(L"\t\t--MENU--\n");
	wprintf(L"1. Mã số sinh viên\n");
	wprintf(L"2. Họ và Tên\n");
	wprintf(L"3. Khoa\n");
	wprintf(L"4. Khóa\n");
	wprintf(L"5. Ngày sinh\n");
	wprintf(L"6. Ảnh đại diện\n");
	wprintf(L"7. Email\n");
	wprintf(L"8. Mô tả bản thân\n");
	wprintf(L"9. Sở thích cá nhân\n");
	wprintf(L"10. Tất cả\n\n");
	wprintf(L"Chọn các mục (nhiều nhất là 10) bạn muốn hiển thị trên TRANG CÁ NHÂN (Nhấn CTR + Z để kết thúc tùy chọn): ");
	while (scanf_s("%d%*c", &choose) > 0 && nMenu < 10)
	{
		Menu = (int*)realloc(Menu, (nMenu + 1)*sizeof(int));
		*(Menu + nMenu) = choose;
		nMenu++;
	}//-----------------------------------------------------------------------------------------------------------------------------
}
// số lượng sinh viên có trong CSV
int nStudentOfList(FILE *fileIn)
{
	int count = 0;
	while (!feof(fileIn))
	{
		if (fgetwc(fileIn) == '\n')
			count++;
	}
	return count;
}
// hàm phát sinh tên fileOut của các sinh viên
void nameFileOutOfListStudent(wchar_t *nameFileOut[100], LIST list)
{
	int lengthID;
	for (int i = 0; i < list.nStudent; i++)
	{
		nameFileOut[i] = NULL;
		lengthID = strlen(list[i].ID);
		nameFileOut[i] = (wchar_t*)realloc(nameFileOut[i], (lengthID + 1)*sizeof(wchar_t));
		for (int j = 0; j < lengthID; j++)
			nameFileOut[i][j] = (wchar_t)(list[i].ID)[j];
		nameFileOut[i][lengthID] = '\0';

		lengthID += strlen(".htm");
		nameFileOut[i] = (wchar_t*)realloc(nameFileOut[i], (lengthID + 1)*sizeof(wchar_t));
		nameFileOut[i] = wcscat(nameFileOut[i], L".htm");
	}
}
// hàm hủy
void destroyList(LIST &list)
{
	free(list.nHobbyOfOneStudent);
	for (int i = 0; i < list.nStudent; i++)
	{
		free(list[i].ID);
		free(list[i].fullName);
		free(list[i].faculty);
		free(list[i].birthDay);
		free(list[i].Email);
		free(list[i].linkImage);
		free(list[i].description);
		for (int j = 0; j < list.nHobbyOfOneStudent[i]; j++)
			free(list[i].hobby[j]);
	}
	delete[] list.student;
}
//==============================================================================================================================================
// HÀM CHÍNH
// hàm đọc danh sách sinh viên trong fileIn(CSV)
void readFileCSV(FILE *fileIn, LIST &list)
{
	for (int i = 0; i < 3; i++)
		fgetwc(fileIn);// đọc bỏ 3 kí tự rác đầu của file CSV

	char mark;
	for (int i = 0; i < list.nStudent; i++)
	{
		/*		Xác định dấu ngắt câu đầu tiên cần đọc đến
		Có 2 trường hợp:
		TH1:	nội dung,			--> mark = ','
		TH2:   "nội dung",			--> mark = '\"'		*/
		if (fgetc(fileIn) == '\"')
			mark = '\"';	// TH2:
		else
		{
			fseek(fileIn, ftell(fileIn) - 1, SEEK_SET);
			mark = ',';		// TH1
		}
		FGETS(list[i].ID, 11, fileIn, mark);
		
		FGETWS(list[i].fullName, 31, fileIn, mark);
	
		FGETWS(list[i].faculty, 31, fileIn, mark);
	
		FSCANF_NUMBER(list[i].yearSchool, fileIn, mark);
	
		FGETS(list[i].birthDay, 11, fileIn, mark);
	
		FGETS(list[i].Email, 31, fileIn, mark);
	
		FGETS(list[i].linkImage, 31, fileIn, mark);

		FGETWS(list[i].description, 1000, fileIn, mark);

		if (mark != '\n') // trường hợp người dùng có ghi sở thích
		{
			// Đọc n Sở thích của một sinh viên
			list.nHobbyOfOneStudent = (int*)realloc(list.nHobbyOfOneStudent, (i + 1)*sizeof(int)); // danh sách các Sở thích của 1 sinh viên
			list.nHobbyOfOneStudent[i] = 0;
			while (true)
			{
				FGETWS(list[i].hobby[list.nHobbyOfOneStudent[i]], 1000, fileIn, mark);

				list.nHobbyOfOneStudent[i]++;

				if (mark == '\n')
					break;
			}
		}
	}
}
// hàm vừa đọc fileIn(HTML) vừa ghi fileOut cho 1 sinh viên
void writeOneStudentInFileCSV(FILE *fileIn, FILE *fileOut, const STUDENT &student, const int &nHobby, int *Menu, const int &nMenu)
{
	// tìm chuỗi <title> ---------------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, title); // đọc fileIn-ghi fileOut đến chuỗi title
	
	fputws(student.fullName, fileOut); // ghi Họ&Tên sinh viên mới vào fileOut 

	readFileIn_ToWS(fileIn, L"</title>"); // đọc bỏ Họ&Tên mẫu trong fileIn
	// tìm chuỗi classFullName ---------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classFullName); // đọc fileIn-ghi fileOut đến chuỗi classFullName

	if (isInMenu(Menu, nMenu, 2) || isInMenu(Menu, nMenu, 10))
		fputws(student.fullName, fileOut); // ghi Họ&Tên sinh viên mới vào fileOut 
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	if (isInMenu(Menu, nMenu, 1) && isInMenu(Menu, nMenu, 2) || isInMenu(Menu, nMenu, 10)) // khi fullName và ID đều được chọn trong Menu dấu này mới xuất hiện
		fputws(L" - ", fileOut); // ghi kí tự ' - ' vào fileOut

	if (isInMenu(Menu, nMenu, 1) || isInMenu(Menu, nMenu, 10))
		fputs(student.ID, fileOut); // ghi ID sinh viên mới vào fileOut
	else
		fputs("", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</span>");// đọc bỏ Họ&Tên-ID mẫu trong fileIn
	// tìm chuỗi classFaculty ---------------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classFaculty); // đọc fileIn-ghi fileOut đến chuỗi classFaculty

	if (isInMenu(Menu, nMenu, 3) || isInMenu(Menu, nMenu, 10))
		fputws(student.faculty, fileOut); // ghi Khoa sinh viên mới vào fileOut 
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</div>"); // đọc bỏ Khoa mẫu trong fileIn
	// tìm chuỗi classEmail ---------------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classEmail); // đọc fileIn-ghi fileOut đến chuỗi classEmail

	if (isInMenu(Menu, nMenu, 7) || isInMenu(Menu, nMenu, 10))
		fputs(student.Email, fileOut); // ghi Email sinh viên mới vào fileOut 
	else
		fputs("", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</div>"); // đọc bỏ Khoa mẫu trong fileIn
	// tìm chuỗi classLinkImage ---------------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classLinkImage); // đọc fileIn-ghi fileOut đến chuỗi classLinkImage

	if (isInMenu(Menu, nMenu, 6) || isInMenu(Menu, nMenu, 10))
		fputs(student.linkImage, fileOut); // ghi Link Ảnh Cá Nhân sinh viên mới vào fileOut 
	else
		fputs("", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"\""); // đọc bỏ Link Ảnh Cá Nhân mẫu trong fileIn
	// tìm chuỗi classInfo <thông tin sinh viên> -----------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classInfo); // đọc fileIn-ghi fileOut đến chuỗi classInfo

	if (isInMenu(Menu, nMenu, 2) || isInMenu(Menu, nMenu, 10))
		addLineInList(topicFullName, student.fullName, fileOut);               // thông tin Họ&Tên
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	if (isInMenu(Menu, nMenu, 1) || isInMenu(Menu, nMenu, 10))
		addLineInList(topicID, student.ID, fileOut);							// thông tin ID
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	if (isInMenu(Menu, nMenu, 3) || isInMenu(Menu, nMenu, 10))
		addLineInList(topicFaculty, student.faculty, fileOut);                // thông tin Khoa
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	if (isInMenu(Menu, nMenu, 5) || isInMenu(Menu, nMenu, 10))
		addLineInList(topicBirthDay, student.birthDay, fileOut);              // thông tin Ngày Sinh
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	if (isInMenu(Menu, nMenu, 7) || isInMenu(Menu, nMenu, 10))
		addLineInList(topicEmail, student.Email, fileOut);                     // thông tin Email
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	if (isInMenu(Menu, nMenu, 4) || isInMenu(Menu, nMenu, 10))
		addLineInList(topicYearSchool, student.yearSchool, fileOut);			// thông tin Khóa
	else
		fputws(L"", fileOut); // ghi trống vào fileOut 

	readFileIn_ToWS(fileIn, L"</ul>"); // đọc bỏ Thông Tin mẫu trong fileIn
	// tìm chuỗi classHobby <sở thích cá nhân> --------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classHobby); // đọc fileIn-ghi fileOut đến chuỗi classHobby

	if (isInMenu(Menu, nMenu, 9) || isInMenu(Menu, nMenu, 10))
	{
		for (int i = 0; i < nHobby; i++)
		{
			if (*student.hobby[i] != '\0')
				addLineInList(L"", student.hobby[i], fileOut);                 // ghi Sở Thích thứ i của sinh viên mới vào fileOut
		}
	}
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</ul>"); // đọc bỏ Sở Thích mẫu trong fileIn
	// tìm chuỗi classDescription <mô tả bản thân> -----------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classDescription); // đọc fileIn-ghi fileOut đến chuỗi classDescription

	if (isInMenu(Menu, nMenu, 8) || isInMenu(Menu, nMenu, 10))
		fputws(student.description, fileOut);                 // ghi Mô Tả Bản Thân của sinh viên mới vào fileOut
	else
		fputws(L"", fileOut); // ghi trống vào fileOut

	readFileIn_ToWS(fileIn, L"</div>"); // đọc bỏ Mô Tả Bản Thân mẫu trong fileIn
	// tìm chuỗi classFooter <cuối trang> --------------------------------------------------------------------------------------------------------------
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, classFooter); // đọc fileIn-ghi fileOut đến chuỗi classFooter

	if (isInMenu(Menu, nMenu, 4) || isInMenu(Menu, nMenu, 10))
	{
		fprintf_s(fileOut, "%d", student.yearSchool);
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
	readFileIn_WriteFileOut_ToWS(fileOut, fileIn, L"</html>"); //====> đọc fileIn và ghi fileOut đến cuối fileIn
}
