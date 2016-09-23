@echo off
PATH=D:\MCU\SEGGER\JLink_V610a;%PATH%
start JLinkGDBServerCL.exe -device Cortex-M3 -if SWD -ir -endian little -speed 3500 

