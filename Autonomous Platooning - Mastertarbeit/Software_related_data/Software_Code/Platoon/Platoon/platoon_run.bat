:: 
:: 
:: platoon_run.bat - provide data recording functionality and parallel (build/upload/monitor) to abstract from VSC 
:: 
:: Copyright (C) 2021  Institute of Communication Networks (ComNets), 
::                     Hamburg University of Technology (TUHH)
::           (C) 2021  Ahmed Shaheen
:: 
:: This program is free software: you can redistribute it and/or modify
:: it under the terms of the GNU General Public License as published by
:: the Free Software Foundation, either version 3 of the License, or
:: (at your option) any later version.
:: 
:: This program is distributed in the hope that it will be useful,
:: but WITHOUT ANY WARRANTY; without even the implied warranty of
:: MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
:: GNU General Public License for more details.
:: 
:: You should have received a copy of the GNU General Public License
:: along with this program.  If not, see <https://www.gnu.org/licenses/>.
:: 

@echo off

set PIO_EXE="C:\Users\Kimo Store\.platformio\penv\Scripts\platformio.exe"
set CMD=
set UPLOAD_ARG="target upload"
set MONITOR_ARG="device monitor"
set CLEAN_ARG="device monitor"
set TARGET=
set TARGET_F=all
set RUN=run
set save_file=false
IF NOT "%1"=="" (
	echo Argument entered
	IF "%1"=="leader" (
	echo Build for Leader
	SET TARGET=--environment leader
	set TARGET_F=leader
	)
	IF "%1"=="vone" (
	echo Build for Vehicle One
	set TARGET=--environment vOne
	set TARGET_F=vehicle_one
	)
	IF "%1"=="vtwo" (
	set TARGET=--environment vTwo
	set TARGET_F=vehicle_two
	)
	IF "%1"=="logger" (
	set TARGET=--environment logger
	set TARGET_F=logger
	)
	IF "%1"=="test" (
	set TARGET=--environment test
	set TARGET_F=test_out
	)
)

IF NOT "%2"=="" (
	echo Argument entered
	IF "%2"=="-u" (
	SET CMD=--target upload
	)
	IF "%2"=="-u_m" (
	SET CMD=--target upload --target monitor
	)
	IF "%2"=="-m" (
	SET RUN=device
	SET CMD= monitor
	)
	IF "%2"=="-c" (
	SET CMD=--target clean
	)
)

echo Processing...
echo %PIO_EXE% %RUN% %CMD% %TARGET%
echo %3

IF "%3"=="-f" (SET save_file=true) 
IF "%2"=="-f" (SET save_file=true)
IF "%1"=="-f" (SET save_file=true)


IF %save_file%==true (
	echo Output saved in file -- output_%TARGET_F%.txt
	call %PIO_EXE% %RUN% %CMD% %TARGET% >output_%TARGET_F%.txt 2>&1
) ELSE ( 
	echo run directly
	call %PIO_EXE% %RUN% %CMD% %TARGET%
)

