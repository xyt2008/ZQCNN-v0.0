
#ifndef _ZQ_MFC_UTILS_H_
#define _ZQ_MFC_UTILS_H_

#include "stdafx.h"
#include <string>
#include <fstream>

#ifndef BIF_NEWDIALOGSTYLE  
#define  BIF_NEWDIALOGSTYLE  0x0040  
#endif  

namespace ZQ
{
	class ZQ_MFC_Utils
	{
	public:
		static CString SelectFolder()
		{
			TCHAR           szFolderPath[MAX_PATH] = { 0 };
			CString         strFolderPath = TEXT("");

			BROWSEINFO bi;
			::ZeroMemory(&bi, sizeof(bi));
			LPITEMIDLIST pNetHoodIDL;

			::SHGetSpecialFolderLocation(NULL, CSIDL_HISTORY, &pNetHoodIDL);  //���ļ���Ϊ��ʷ�ļ���   
			bi.pidlRoot = 0;
			bi.lpszTitle = _T("��ѡ��һ���ļ��У�");
			bi.ulFlags = /*BIF_BROWSEINCLUDEFILES | */   //����ѡ���ļ�����    
				BIF_EDITBOX |                        //��ʾ�༭��    
				BIF_STATUSTEXT |                     //��ʾ״̬�ı�    
				BIF_VALIDATE |                       //У��༭���е�����    
				BIF_DONTGOBELOWDOMAIN | 
				BIF_RETURNONLYFSDIRS ;

			LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&bi);
			if (lpidlBrowse != NULL)
			{
				// ȡ���ļ�����  
				if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
				{
					strFolderPath = szFolderPath;
				}
			}
			if (lpidlBrowse != NULL)
			{
				::CoTaskMemFree(lpidlBrowse);
			}

			return strFolderPath;
		}

		static CString SelectFolder2()
		{
			CString strFolder = _T("");
			CFolderPickerDialog dlgFolder;
			if (dlgFolder.DoModal())
			{
				strFolder = dlgFolder.GetPathName();
			}
			return strFolder;
		}

		static CString SelectFolder3(CString default_filename = _T(""))
		{
			CString strFile = _T("");

			LPCTSTR pdefault_filename = NULL;
			if (!default_filename.IsEmpty())
				pdefault_filename = default_filename.GetBuffer();
			CFileDialog    dlgFile(TRUE, NULL, pdefault_filename, OFN_HIDEREADONLY, NULL, NULL, 0, TRUE);


			if (dlgFile.DoModal())
			{
				strFile = dlgFile.GetPathName();
			}

			return strFile;
		}

		static CString SelectFile(CString default_filename = _T(""))
		{
			CString strFile = _T("");

			LPCTSTR pdefault_filename = NULL;
			if (!default_filename.IsEmpty())
				pdefault_filename = default_filename.GetBuffer();
			CFileDialog    dlgFile(TRUE, NULL, pdefault_filename, OFN_HIDEREADONLY, _T("(*.txt)|*.txt|(*.cfg)|*.cfg|All Files (*.*)|*.*||"), NULL);

			if (dlgFile.DoModal())
			{
				strFile = dlgFile.GetPathName();
			}

			return strFile;
		}


		static std::string CStringToString(CString& input)
		{
			return std::string(CW2A(input.GetString()));
			//printf("%d\n", input.GetLength());
			//char *chr = new char[input.GetLength() + 1];
			//WideCharToMultiByte(CP_ACP, 0, input.GetBuffer(), -1, chr, input.GetLength() + 1, NULL, NULL);
			//delete[]chr;
			//return str;
		}

		static bool CheckFileExist(const std::string& file)
		{
			std::fstream _file;
			_file.open(file, std::ios::in);
			return _file.is_open();
		}

		static bool CheckFolderExist(const std::string &strPath)
		{
			WIN32_FIND_DATA  wfd;
			bool rValue = false;
			HANDLE hFind = FindFirstFile(CString(strPath.c_str()).GetBuffer(), &wfd);
			if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				rValue = true;
			}
			FindClose(hFind);
			return rValue;
		}
	};
}

#endif