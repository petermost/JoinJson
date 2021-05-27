#include <gtest/gtest.h>
#include <clean.hpp>

using namespace std;

// static const string_view COMMAND(R"("C:\\PROGRA~2\\MICROS~2\\2019\\COMMUN~1\\VC\\Tools\\MSVC\\1428~1.299\\bin\\HostX86\\x86\\cl.exe   /TP -DAIDKIT_STATIC_LIBRARY -D_CRT_SECURE_NO_WARNINGS -D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING -ID:\\Sourcen\\compile_commands\\compile_commands\\src -ID:\\Sourcen\\compile_commands\\compile_commands\\CppAidKit\\src -Ivcpkg_installed\\x86-windows-static\\include /DWIN32 /D_WINDOWS /GR /EHsc /Zi /Ob0 /Od /RTC1 -MTd -EHsc -permissive- -Zc:__cplusplus -Zc:externConstexpr -Zc:inline -Zc:preprocessor -Zc:referenceBinding -Zc:rvalueCast -Zc:strictStrings -Zc:ternary -Zc:throwingNew -W4 -wd4251 -wd4275 -std:c++latest /FoCMakeFiles\\compile_commands_classes.dir\\src\\clean.cpp.obj /FdTARGET_COMPILE_PDB /FS -c D:\\Sourcen\\compile_commands\\compile_commands\\src\\clean.cpp")");

TEST(CleanTest, replaceDefine)
{
	string cleanCommand = cleanCommandParameters("/DSYMBOL"s);
	ASSERT_EQ(cleanCommand, "-DSYMBOL"s);
}


TEST(CleanTest, replaceWarning)
{
	string cleanCommand = cleanCommandParameters("/wd1234"s);
	ASSERT_EQ(cleanCommand, ""s);
}

TEST(CleanTest, replaceNoLogo)
{
	string cleanCommand = cleanCommandParameters("/nologo"s);
	ASSERT_EQ(cleanCommand, ""s);
}

TEST(CleanTest, replaceWall)
{
	string cleanCommand = cleanCommandParameters("/Wall"s);
	ASSERT_EQ(cleanCommand, "-Wall"s);
}
