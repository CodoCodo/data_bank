#!/bin/bash

cmd=$1

export DB_PATH=db/bank.db

if [ -z $cmd ]; then
  echo "Usage : main.sh cmd [parameters]"
  exit
fi

if [ "$cmd"=="add" ]; then
  ./script/add_media.sh $2
fi 
