#include <gtest/gtest.h>
#include <string>
#include <CompileCommands.hpp>

using namespace std;

static const string_view COMPILE_COMMANDS_FILE(R"(
[
{
  "directory": "D:/Sourcen/compile_commands/build/Debug",
  "command": "C:\\PROGRA~2\\MICROS~2\\2019\\COMMUN~1\\VC\\Tools\\MSVC\\1428~1.299\\bin\\HostX86\\x86\\cl.exe   /TP -DAIDKIT_STATIC_LIBRARY -D_CRT_SECURE_NO_WARNINGS -D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING -ID:\\Sourcen\\compile_commands\\compile_commands\\src -ID:\\Sourcen\\compile_commands\\compile_commands\\CppAidKit\\src -Ivcpkg_installed\\x86-windows-static\\include /DWIN32 /D_WINDOWS /GR /EHsc /Zi /Ob0 /Od /RTC1 -MTd -EHsc -permissive- -Zc:__cplusplus -Zc:externConstexpr -Zc:inline -Zc:preprocessor -Zc:referenceBinding -Zc:rvalueCast -Zc:strictStrings -Zc:ternary -Zc:throwingNew -W4 -wd4251 -wd4275 -std:c++latest /FoCMakeFiles\\compile_commands_classes.dir\\src\\join.cpp.obj /FdTARGET_COMPILE_PDB /FS -c D:\\Sourcen\\compile_commands\\compile_commands\\src\\join.cpp",
  "file": "D:\\Sourcen\\compile_commands\\compile_commands\\src\\join.cpp"
},
{
  "directory": "D:/Sourcen/compile_commands/build/Debug",
  "command": "C:\\PROGRA~2\\MICROS~2\\2019\\COMMUN~1\\VC\\Tools\\MSVC\\1428~1.299\\bin\\HostX86\\x86\\cl.exe   /TP -DAIDKIT_STATIC_LIBRARY -D_CRT_SECURE_NO_WARNINGS -D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING -ID:\\Sourcen\\compile_commands\\compile_commands\\src -ID:\\Sourcen\\compile_commands\\compile_commands\\CppAidKit\\src -Ivcpkg_installed\\x86-windows-static\\include /DWIN32 /D_WINDOWS /GR /EHsc /Zi /Ob0 /Od /RTC1 -MTd -EHsc -permissive- -Zc:__cplusplus -Zc:externConstexpr -Zc:inline -Zc:preprocessor -Zc:referenceBinding -Zc:rvalueCast -Zc:strictStrings -Zc:ternary -Zc:throwingNew -W4 -wd4251 -wd4275 -std:c++latest /FoCMakeFiles\\compile_commands_classes.dir\\src\\clean.cpp.obj /FdTARGET_COMPILE_PDB /FS -c D:\\Sourcen\\compile_commands\\compile_commands\\src\\clean.cpp",
  "file": "D:\\Sourcen\\compile_commands\\compile_commands\\src\\clean.cpp"
},
{
  "directory": "D:/Sourcen/compile_commands/build/Debug",
  "command": "C:\\PROGRA~2\\MICROS~2\\2019\\COMMUN~1\\VC\\Tools\\MSVC\\1428~1.299\\bin\\HostX86\\x86\\cl.exe   /TP -DAIDKIT_STATIC_LIBRARY -D_CRT_SECURE_NO_WARNINGS -D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING -ID:\\Sourcen\\compile_commands\\compile_commands\\src -ID:\\Sourcen\\compile_commands\\compile_commands\\CppAidKit\\src -Ivcpkg_installed\\x86-windows-static\\include /DWIN32 /D_WINDOWS /GR /EHsc /Zi /Ob0 /Od /RTC1 -MTd -EHsc -permissive- -Zc:__cplusplus -Zc:externConstexpr -Zc:inline -Zc:preprocessor -Zc:referenceBinding -Zc:rvalueCast -Zc:strictStrings -Zc:ternary -Zc:throwingNew -W4 -wd4251 -wd4275 -std:c++latest /FoCMakeFiles\\compile_commands.dir\\src\\main.cpp.obj /FdTARGET_COMPILE_PDB /FS -c D:\\Sourcen\\compile_commands\\compile_commands\\src\\main.cpp",
  "file": "D:\\Sourcen\\compile_commands\\compile_commands\\src\\main.cpp"
}
]
)");

TEST(CompileCommandsTest, testReadWrite)
{
    CompileCommands commands;
    string json(COMPILE_COMMANDS_FILE);
    commands.read(json);
    ASSERT_EQ(commands.size(), 3u);

    commands.write(&json);


}
