#pragma once

typedef struct _tagCopyData
{
	bool         Pass_Exam_fg;
	int          Math_Score_i;
	//CString    Name_cstr;  //send copydata could not use cstring 
	TCHAR        Name[256];
	//CString    ID_cstr;
	TCHAR        ID[256];

}TAG_COPYDATA;
