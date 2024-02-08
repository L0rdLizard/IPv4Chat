@echo off
setlocal

set "containers=user1 user2"

for %%i in (%containers%) do (
    docker stop %%i > nul 2>&1
    if not errorlevel 1 (
        echo Stopped container: %%i
    ) else (
        echo Container %%i not found or already stopped.
    )
)

endlocal