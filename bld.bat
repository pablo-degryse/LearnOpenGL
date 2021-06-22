@echo off
cls

set config=Debug
rem set config=Release

set fullBldDir=%bldDir%\%config%
if not exist %fullBldDir% (mkdir %fullBldDir%)

set sourceFiles=%srcDir%\Main.cpp %srcDir%\ShaderProgram.cpp %srcDir%\FpsCamera.cpp %srcDir%\Texture.cpp %srcDir%\Buffers.cpp %srcDir%\VertexArray.cpp
set libFiles=%libBinDir%\%config%\glfw3.lib opengl32.lib user32.lib gdi32.lib shell32.lib

if %config% EQU Debug (
set configClArgs=/D DEBUG /Zi /DEBUG:FULL /MDd
set configLinkArgs=/DEBUG:FULL
) else (
set configClArgs=/O2 /MD
set configLinkArgs=/DEBUG:NONE
)

pushd %fullBldDir%
cl %sourceFiles% /Fe:%proj%.exe /I%libIncDir% %configClArgs% /EHsc /W3 /nologo /link %configLinkArgs% /INCREMENTAL:NO %libFiles%
popd