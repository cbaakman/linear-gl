@echo off

set CXX=g++
set CFLAGS=-std=c++17

if not exist bin (mkdir bin)
if not exist obj (mkdir obj)


echo compile
for %%c in (1 2) do (
    %CXX% %CFLAGS% -I include -c tests\compile%%c.cpp -o obj\compile%%c.o
)
%CXX% obj\compile1.o obj\compile2.o -o bin\compile


for %%t in (vec quat mat) do (
    echo test: %%t
    %CXX% %CFLAGS% -I include tests\test_%%t.cpp -lboost_unit_test_framework -o bin\test_%%t && bin\test_%%t
)
