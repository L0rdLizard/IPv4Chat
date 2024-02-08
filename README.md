# UDP Broadcast IPv4 chat
Project on github: https://github.com/L0rdLizard/IPv4Chat

## About code

This project implements the “IPv4 chat” program, which exchanges text broadcast (IPv4 UDP broadcast) messages over a local network segment, with copies running on other machines physically connected to one logical network segment. 

The project uses the broadcast IPv4 address 255.255.255.255. 

The client code contains a reception thread and a sending thread with an input limit of up to 1007 bytes. 

The project is built through the run_first.sh and run_second.sh scripts into docker containers in a common virtual network. 

The image for docker containers is written using a multi-stage build and is optimized.

## Getting started
### 1. Docker network
```
$ docker network create --subnet=172.18.0.0/24 --gateway=172.18.0.1 info
```

### 2. Docker image 
```
$ docker build -t udpchat .
```

### 3. Run
For Windows
```
$ .\scriptsWin\run_first.bat  
```

```
$ .\scriptsWin\run_second.bat
```

For Unix
```
$ chmod +x ./scriptsUnix/run_first.sh
$ ./scriptsUnix/run_first.sh
```

```
$ chmod +x ./scriptsUnix/run_second.sh
$ ./scriptsUnix/run_second.sh
```

### 4. Stop
For Windows
```
$ .\scriptsWin\stop.bat  
```

For Unix
```
$ chmod +x ./scriptsUnix/stop.sh
$ ./scriptsUnix/stop.sh
```