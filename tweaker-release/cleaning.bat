@echo off
echo Cleaning Temp folders...

del /s /q %TEMP%\*
for /d %%x in (%TEMP%\*) do rd /s /q "%%x"

del /s /q C:\Windows\Temp\*
for /d %%x in (C:\Windows\Temp\*) do rd /s /q "%%x"

del /s /q "%LocalAppData%\NVIDIA\DXCache\*"
del /s /q "%LocalAppData%\NVIDIA\GLCache\*"

del /s /q "%LocalAppData%\D3DSCache\*"

del /s /q C:\Windows\Prefetch\*

echo Done.
exit
