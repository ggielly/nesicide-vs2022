@ECHO OFF

:: Variable setup
SET CC=java -jar ..\dist\uc65.jar -s
SET CA=..\cc65\ca65.exe
SET LD=..\cc65\ld65.exe

:: Prep platform files
%CA% ..\lib\crt0.s
IF ERRORLEVEL 1 GOTO ERROR

:: Compile all source file
FOR %%F IN (*.uc) DO (
	%CC% -d %%F
	IF ERRORLEVEL 1 GOTO ERROR
)

:: Assemble all source files
FOR %%F IN (*.s) DO (
	%CA% %%F
	IF ERRORLEVEL 1 GOTO ERROR
)

:: Link all binaries
FOR %%F IN (*.o) DO (
	%LD% --config ..\lib\memory.cfg ..\lib\crt0.o %%F
	IF ERRORLEVEL 1 GOTO ERROR
)

GOTO EXIT

:ERROR
ECHO Test has failed

:EXIT
