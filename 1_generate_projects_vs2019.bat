mkdir build
cd build
mkdir vs2019_64
cd vs2019_64
del /s /q ".\CMakeCache.txt"
cmake ../.. -G "Visual Studio 16 2019" -A x64
cd ..
mkdir vs2019_32
cd vs2019_32
del /s /q ".\CMakeCache.txt"
cmake ../.. -G "Visual Studio 16 2019" -A Win32
cd ..