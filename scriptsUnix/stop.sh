#!/bin/bash

containers="user1 user2"

echo "Stopping containers: $containers"
for i in $containers
do
   if docker stop $i > /dev/null 2>&1; then
       echo "Container $i stopped"
   else
       echo "Container $i not found"
   fi
done
