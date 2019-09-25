#!/bin/bash

file_path=$1

media_info=$(python3 ${python_path}/media_info.py ${file_path})
echo "${media_info}"

media_type=$(echo "$media_info" | awk '{print $1}')

if [[ "${media_type}" == "bmp" ]]; then
  echo "not_supported media ${file_path}"
  exit
fi
