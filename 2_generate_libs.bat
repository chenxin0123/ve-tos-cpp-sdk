@echo off

set VS_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\MSBuild.exe"
set SLN_FILE="ve-tos-cpp-sdk.sln"
set TARGET="ve-tos-cpp-sdk-lib"

cd build

cd vs2019_32
%VS_PATH% %SLN_FILE% /target:%TARGET% /property:Configuration=Debug /property:Platform=Win32
%VS_PATH% %SLN_FILE% /target:%TARGET% /property:Configuration=RelWithDebInfo /property:Platform=Win32
cd..

cd vs2019_64
%VS_PATH% %SLN_FILE% /target:%TARGET% /property:Configuration=Debug /property:Platform=x64
%VS_PATH% %SLN_FILE% /target:%TARGET% /property:Configuration=RelWithDebInfo /property:Platform=x64
cd ..

cd ..