#!/bin/bash

${data_base_cmd} < ${sql_script_path}/create_table_simple_label.sql

"INSERT INTO simple_labels (media_id, frame_id, label_str) VALUES (1, 0, 'face');"
