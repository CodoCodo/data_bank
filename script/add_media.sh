#!/bin/bash

file_path=$1
project_root_dir=$(pwd)
get_file_type=${project_root_dir}/script/get_file_type.sh

if [ -z ${file_path} ]; then
  echo "Please specify file path"
  exit
fi

# 检查文件是否存在
if [ ! -f ${file_path} ]; then
  echo "File not exist. ${file_path}"
  exit
fi

# 判断是图片、视频、还是图片列、还是无效文件
# 提取文件扩展名
# 生成新名称
file_type=$(${get_file_type} ${file_path})
ext_name=${file_path##*.}
new_file_name="${file_type}_$(date +%Y%m%d%H%M%S).${ext_name}"

# 存放到存储目录中
target_path=${project_root_dir}/${file_type}/${new_file_name}
if [ "${file_type}"=="image" ]; then
  cp ${file_path} ${target_path}
elif [ "${file_type}"=="video" ]; then
  cp ${file_path} ${target_path}
else
  echo "Not supported file type. ${file_path}"
  exit
fi

# 设置为只读
chmod 0440 ${target_path}

# 更新数据库
