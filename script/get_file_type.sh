#!/bin/bash

file_path=$1

if [ -z ${file_path} ]; then
  echo "Please specify file path"
  exit
fi

ext_name=${file_path##*.}
file_type=""

case $ext_name in
  "mp4" | "avi")
    file_type="video"
    ;;
  "jpg" | "bmp" | "png")
    file_type="image"
    ;;
  * )
    file_type="unknown"
    ;;
esac

echo $file_type
