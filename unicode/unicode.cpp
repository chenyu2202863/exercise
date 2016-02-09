// unicode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <locale>
#include <fstream>
#include <codecvt>
#include <cvt\wstring>

int main()
{
	char utf8[] = u8"\u4f60\u597d\u554a";
	char16_t utf16[] = u"hello";
	char32_t utf32[] = U"hello equals \u4f60\u597d\u554a";

	char16_t utf161[] = u"\u4f60\u597d\u554a";

	std::cout << utf8 << std::endl;
	std::cout << utf16 << std::endl;
	std::cout << utf32 << std::endl;

	std::cout << sizeof(utf8) << ' ' << sizeof(utf161) << std::endl;

	std::locale lc("chs");
	auto has_cvt = std::has_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(lc);
	std::cout << "has codecvt: " << /*std::ios::boolalpha << */has_cvt << std::endl;

	std::ofstream("text.txt") << utf8;
	std::wifstream in("text.txt");
	in.imbue(std::locale("chs"));
	
	for(wchar_t c = 0; in >> c; )
		std::cout << c;
	std::cout << std::endl;

	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	auto text = conv.to_bytes(L"unicode≤‚ ‘");
	std::cout << text << std::endl;


	auto codecvt = []()
	{
		// UTF-8 data. The character U+1d10b, musical sign segno, does not fit in UCS2
		std::string utf8 = u8"z\u6c34\U0001d10b";

		// the UTF-8 / UTF-16 standard conversion facet
		std::wstring_convert<std::codecvt_utf8<wchar_t>> utf16conv;
		auto utf16 = utf16conv.from_bytes(utf8);
		std::cout << "UTF16 conversion produced " << utf16.size() << " code points:\n";
		for( auto c : utf16 )
			std::cout << c << '\n';
	};
	codecvt();

	system("pause");
    return 0;
}

