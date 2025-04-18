@echo off
setlocal

REM Compiler
set CXX=clang++

REM Source file(s)
set SRC="src\main.cpp src\physics\physics-engine.cpp src/game-loop/game-loop.cpp"

REM Output executable
set OUT=wizards-nest.exe

REM Compiler flags
set CXXFLAGS=-std=c++17 -Wall -Wextra -O2

REM Linker libraries (adjust if needed for Windows)
set LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm

echo Building...

%CXX% %SRC% %CXXFLAGS% %LIBS% -o %OUT%

if %ERRORLEVEL% NEQ 0 (
    echo Build failed.
    exit /b %ERRORLEVEL%
)

echo Build successful.
endlocal
