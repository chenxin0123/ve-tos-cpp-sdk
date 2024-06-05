@echo off

rmdir /s /q .\output

xcopy ".\sdk\include\*.h" ".\output\include\" /y /s

xcopy ".\build\vs2019_32\lib\Debug\ve-tos-cpp-sdk-lib.lib" ".\output\win32\Debug\" /y
xcopy ".\build\vs2019_32\lib\Debug\ve-tos-cpp-sdk-lib.pdb" ".\output\win32\Debug\" /y
xcopy ".\build\vs2019_32\lib\RelWithDebInfo\ve-tos-cpp-sdk-lib.lib" ".\output\win32\Release\" /y
xcopy ".\build\vs2019_32\lib\RelWithDebInfo\ve-tos-cpp-sdk-lib.pdb" ".\output\win32\Release\" /y

xcopy ".\build\vs2019_64\lib\Debug\ve-tos-cpp-sdk-lib.lib" ".\output\win64\Debug\" /y
xcopy ".\build\vs2019_64\lib\Debug\ve-tos-cpp-sdk-lib.pdb" ".\output\win64\Debug\" /y
xcopy ".\build\vs2019_64\lib\RelWithDebInfo\ve-tos-cpp-sdk-lib.lib" ".\output\win64\Release\" /y
xcopy ".\build\vs2019_64\lib\RelWithDebInfo\ve-tos-cpp-sdk-lib.pdb" ".\output\win64\Release\" /y