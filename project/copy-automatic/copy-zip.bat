 chcp 65001

@echo off

@echo 正在定时备份Minecraft1.12.2存档zain-survive(时间间隔为1s)

:start


::设置7z的命令行程序路径
::WinRAR运行文件
set winrar=D:\Install\NoGreenInstall\WinRAR\WinRAR.exe
::设置要打包压缩的文件夹
set files=F:\Game\Install\GreenInstall\Minecraft\Minecraft1.12.2\.minecraft\saves\zain-survive
::设置压缩包保存后文件及路径
set save=.\zain-survive.zip
::压缩文件
"%winrar%" a -ag{-}YYYY{-}MM{-}DD{-}HH{-}MM{-}SS -k -r -s -ep1 -ibck %save% %files%


choice /t 1 /d y /n >nul
goto start

::winrar参数说明
::a :备份所有文件；
::-ag :当创建压缩文件时，以格式“-YYYY-MM-DD-HH-MM-SS”附加当前日期字符串,文件名bak-YYYY-MM-DD-HH-MM-SS.zip；
::-k :锁定压缩文件；
::-r:备份目录和子目录；
::-s :创建固实压缩文件；
::-ibck :后台运行；


::删除超过7天的备份--start--
::forfiles /p "%Save%" /m *.zip -d -7 /c "cmd /c del /f @path"