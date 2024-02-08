@echo off
setlocal  

set "containers=user1 user2"

echo Stopping containers: %containers%
for %%i in (%containers%) do (
    docker stop %%i 2>&1
    if not errorlevel 1 (
        echo Container %%i stopped
    ) else (
        echo Container %%i not found
    )
)

endlocal