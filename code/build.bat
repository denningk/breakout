@echo off
if not exist ..\build mkdir ..\build
pushd ..\build
del *.pdb > NUL 2> NUL
echo WAITING FOR PDB > lock.tmp

SET compilerFlags=-g -Wvarargs -Wall
SET linkerFlags=-luser32 -lgdi32

clang ..\code\win32_platform.c %compilerFlags% -o win32_platform.exe %linkerFlags%

del *.ilk
del lock.tmp

popd
