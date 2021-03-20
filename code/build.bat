@echo off
if not exist ..\build mkdir ..\build
pushd ..\build
del *.pdb > NUL 2> NUL
echo WAITING FOR PDB > lock.tmp

clang -FC ..\code\win32_platform.c -g -o win32_platform.exe -luser32 -lgdi32

del *.ilk
del lock.tmp

popd
