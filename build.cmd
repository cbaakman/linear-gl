set CXX=g++
set CFLAGS=-std=c++17
set LIB_NAME=linear-gl
set VERSION=1.1.2


if not exist obj (mkdir obj)
if not exist bin (mkdir bin)
if not exist lib (mkdir lib)

del /Q /F /S obj\* bin\%LIB_NAME%-%VERSION%.dll lib\lib%LIB_NAME%.a

:: Make the library

@for %%m in (vec quat matrix plane triangle) do (
    %CXX% %CFLAGS% -I include\linear-gl -c src\%%m.cpp -o obj\%%m.o -fPIC

    @if %ERRORLEVEL% neq 0 (
        goto end
    )
)

%CXX% obj\vec.o obj\quat.o obj\matrix.o obj\plane.o obj\triangle.o -o bin\%LIB_NAME%-%VERSION%.dll -shared -fPIC -Wl,--out-implib,lib\lib%LIB_NAME%.a
@if %ERRORLEVEL% neq 0 (
    goto end
)

:: Testing

@for %%t in (vec quat mat triangle) do (
    %CXX% %CFLAGS% -I include\linear-gl -L lib tests\test_%%t.cpp -lboost_unit_test_framework -l%LIB_NAME% -o bin\test_%%t.exe && bin\test_%%t.exe
    @if %ERRORLEVEL% neq 0 (
        echo %%t failed with exit code %=ExitCode%
        goto end
    )
)

:end
