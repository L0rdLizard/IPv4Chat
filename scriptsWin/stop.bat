@echo off
setlocal

set "container1=user1"
set "container2=user2"

docker stop %container1% > nul 2>&1
if not errorlevel 1 (
        echo Stopped container: %container1%
    ) else (
        echo %container1% not found or already stopped.
    )

docker stop %container2% > nul 2>&1
if not errorlevel 1 (
        echo Stopped container: %container2%
    ) else (
        echo %container2% not found or already stopped.
    )    


endlocal