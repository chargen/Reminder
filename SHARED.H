#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "typeinfo.h"
#include "afxmt.h"

template <class T> void CreatePtr(T*& pTempPtr)
{
	try
	{
		pTempPtr = new T;
	}
	catch(CException* e)
	{
		CString str;
		str.Format("Proc(%X)-> Error creating a variable of %s\n",GetCurrentProcessId(),typeid(T).name());
		TRACE0(str);

		e->ReportError();
		e->Delete();
		pTempPtr = NULL;
	}

}

// Use this creation function to delete a new pointer
// of ANY type...

template <class T> void DeletePtr(T*& pPtr,BOOL bNullify=TRUE)
{
	if(pPtr==NULL) return;

	try
	{
		delete pPtr;
		
		if(bNullify) pPtr = NULL;
	}
	catch(CException* e)
	{
		CString str;
		str.Format("Proc(%X)-> Error deleting a variable of %s\n",GetCurrentProcessId(),typeid(T).name());
		TRACE0(str);

		e->ReportError();
		e->Delete();
	}

}
