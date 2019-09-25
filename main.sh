#!/bin/bash

cmd=$1

export media_storage_path=$(pwd)/medias

export password="codocodo"
export data_base_cmd="mysql -u root -p${password} -D media_bank"
export media_table_name="medias"

export sql_script_path=$(pwd)/sql_scripts
export python_path=$(pwd)/python

if [ -z $cmd ]; then
  echo "Usage : main.sh cmd [parameters]"
  exit
fi

# prepare, e.g. database and table of medias
if [ "$cmd" == "prepare" ]; then
  ./script/prepare.sh
fi 

if [ "$cmd" == "add" ]; then
  ./script/add_media.sh $2
fi

if [ "$cmd" == "test" ]; then
  ./script/test.sh $2
fi
