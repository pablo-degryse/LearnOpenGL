@echo off
cls
if not exist %blddir% (mkdir %blddir%)

set config=Debug
set sourcefiles=%srcdir%\Main.cpp %srcdir%\ShaderProgram.cpp
set libfiles=%libbindir%\%config%\glfw3.lib opengl32.lib user32.lib gdi32.lib shell32.lib

pushd %blddir%
cl %sourcefiles% /Fe:%proj%.exe /I%libincdir% /Zi /DEBUG:FULL /MDd /EHsc /W3 /nologo /link /INCREMENTAL:NO %libfiles%
popd