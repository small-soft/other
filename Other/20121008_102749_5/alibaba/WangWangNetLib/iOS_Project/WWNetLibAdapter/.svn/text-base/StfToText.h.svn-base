#ifndef STFTOTEXT_H
#define STFTOTEXT_H

#define _T(str) str
#define LPCTSTR const char*

class CStfToText
{
public:

	CStfToText(void)
	{
	}

	~CStfToText(void)
	{
	}

	static void Transform(LPCTSTR pStf, int nLen, std::string  &sText)
	{
		LPCTSTR p = pStf;
		LPCTSTR pLast = pStf + nLen;

		//如果字符串未带字体（老版本兼容）
		if(*p != _T('\\'))
		{
            char * ctemp = strstr(pStf, "\\T\/\:");
            if (ctemp != NULL) {
                sText = p;  
            }else {
                FormatInsertText(p, (int)(pLast-p), sText);
            }
			
			return;
		}

		/// process format tokens.
		while (p != NULL && *p != 0 && p < pLast)
		{
			if (*p == _T('\\') )
			{
				switch (*(++p))
				{
				case _T('T'):	/// write text now.
					++p;
					p = FormatInsertText(p, (int)(pLast-p), sText);
					break;
				case _T('\0'):
					break;
				default:	// default is ignore the tokens.
					++p;
					break;
				}
			}
			else
			{
				++p;
			}
		}
	}

	static LPCTSTR FormatInsertText(LPCTSTR pSrc, int nLen, std::string &sText)
	{
		LPCTSTR pEnd = strchr(pSrc, _T('\\'));
		while (NULL != pEnd)
		{
			if (*(pEnd+1) == _T('\\'))
			{
				sText += std::string(pSrc, (int)(pEnd - pSrc));
				sText += _T('\\');
				pSrc = pEnd+2;
				pEnd = strchr(pSrc, _T('\\'));
			}
			else
			{
				break;
			}
		}

		if (pEnd != NULL)
		{
			sText += std::string(pSrc, (int)(pEnd - pSrc));
		}
		else
		{
			sText += pSrc;
		}

		return pEnd;
	}
};

#endif //STFTOTEXT_H
