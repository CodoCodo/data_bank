#!/bin/bash

cmd=$1

if [ -z $cmd ]; then
  echo "Usage : main.sh cmd [parameters]"
  exit
fi

if [ "$cmd"=="add" ]; then
  ./script/add_media.sh $2
fi 
