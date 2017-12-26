#pragma once
#include <string.h>
#include <exception> 
class CGameException : CException
{
public:
	CGameException();
	~CGameException();
	
	CGameException(char* str)
	{
		msg = str;
	}
	CGameException(CGameException& rhs)
	{
		this->msg = rhs.msg;
	}
    CString msg;
};

