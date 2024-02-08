#!/bin/bash

IMAGENAME="udpchat"
CONTAINERNAME="user2"

NETWORK="info"
IP_ADDRESS="172.18.0.22"
PORT="5000"

docker run -it --rm --name $CONTAINERNAME --network $NETWORK --ip $IP_ADDRESS --env IP_ADDRESS=$IP_ADDRESS --env PORT=$PORT $IMAGENAME
