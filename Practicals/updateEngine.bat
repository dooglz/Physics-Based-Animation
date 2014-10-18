REM INCLUDE FILES
xcopy /s /y "..\..\sharp-blue\src\*.h" include\sharp-blue\
REM
xcopy /s /y "..\..\sharp-blue\bin\Win32_debugLib\*.lib" lib\win32\x86\sharp-blue\
xcopy /s /y "..\..\sharp-blue\res\*" bin\Project1-enginePort\Debug\
pause>null