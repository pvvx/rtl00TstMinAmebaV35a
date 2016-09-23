taskkill /F /IM openocd.exe
openocd -f interface\Jlink.cfg -f ..\..\..\component\soc\realtek\8195a\misc\gcc_utility\openocd\ameba1.cfg
