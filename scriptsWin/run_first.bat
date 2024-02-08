@echo off
setlocal

set "IMAGENAME=udpchat"
set "CONTAINERNAME=user1"

set "NETWORK=info"
set "IP_ADDRESS=172.18.0.11"
set "PORT=5000"

docker run -it --rm --name %CONTAINERNAME% --network %NETWORK% --ip %IP_ADDRESS% --env IP_ADDRESS=%IP_ADDRESS% --env PORT=%PORT% %IMAGENAME%

endlocal