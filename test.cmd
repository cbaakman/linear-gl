@echo off

set CXX=g++
set CFLAGS=-std=c++17

if not exist bin (mkdir bin)

for %%t in (vec quat mat) do (
    echo test: %%t
    %CXX% %CFLAGS% -I include tests/test_%%t.cpp -lboost_unit_test_framework -o bin/test_%%t && bin\test_%%t
)
