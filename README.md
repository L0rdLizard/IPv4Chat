# UDP Broadcast IPv4 chat
Project on github: https://github.com/L0rdLizard/IPv4Chat

## About code



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