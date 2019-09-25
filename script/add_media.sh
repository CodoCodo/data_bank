#!/bin/bash

file_path=$1
project_root_dir=$(pwd)
get_file_type=${project_root_dir}/script/get_file_type.sh
media_dir=${project_root_dir}/medias

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

# 校验和
md5_result=$(md5sum ${file_path})
check_sum=$(echo ${md5_result} | awk '{print $1}')

# 扩展名
ext_name=${file_path##*.}

# 新文件名称
new_file_name="media_${check_sum}.${ext_name}"
current_time=$(date +%Y%m%d%H%M%S)

# 指定存储目录
target_path=${media_dir}/${new_file_name}

# 检查是否重复文件
if [ -f ${target_path} ];then
  echo "File already exist. ${file_path} ${target_path}"
  exit
fi

# 提取媒体信息width height channels frame_cnt
media_info=$(python3 ${python_path}/media_info.py ${file_path})
media_type=$(echo "$media_info" | awk '{print $1}')
width=$(echo "$media_info" | awk '{print $2}')
height=$(echo "$media_info" | awk '{print $3}')
channels=$(echo "$media_info" | awk '{print $4}')
frame_cnt=$(echo "$media_info" | awk '{print $5}')

if [[ "${media_type}" == "none" ]]; then
  echo "not_supported media ${file_path}"
  exit
fi

# 复制到target_path
cp ${file_path} ${target_path}

# 设置为只读
chmod 0440 ${target_path}

# 更新数据库
sql_cmd="INSERT INTO ${media_table_name} (location, checksum, modify_date, width, height, channels, frame_cnt) 
         VALUES ('${new_file_name}', '${check_sum}', '${current_time}', ${width}, ${height}, ${channels}, ${frame_cnt});"
echo "${sql_cmd}"
echo ${sql_cmd} | ${data_base_cmd} 

