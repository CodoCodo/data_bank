#!/bin/bash

class_name=$1

if [[ "${class_name}" == "" ]]; then
  echo "Please specify class name."
  exit
fi

file_name=$(tdj_gen_file_name ${class_name})
dir_name=${file_name}

header_file="${file_name}.hpp"
macro_name="_$(echo ${file_name} | tr '[a-z]' '[A-Z]')_HPP"

echo "Generating header file : ${header_file}"
echo "" > ${header_file}
echo "#ifndef ${macro_name}" >> ${header_file}
echo "#define ${macro_name}" >> ${header_file}
echo "" >> ${header_file}
echo "#include <string>" >> ${header_file}
echo "#include <memory>" >> ${header_file}
echo "#include \"label_core_command.h\"" >> ${header_file}
echo "" >> ${header_file}
echo "class ${class_name} : public LabelCoreCommand {" >> ${header_file}
echo " public:" >> ${header_file}
echo "  virtual std::string Key() override {" >> ${header_file}
echo "  }" >> ${header_file}
echo "" >> ${header_file}
echo "  virtual void Execute(std::shared_ptr<LabelCoreContext> p_context) override {" >> ${header_file}
echo "  }" >> ${header_file}
echo "" >> ${header_file}
echo "  virtual std::shared_ptr<LabelCoreCommand> Clone(const CommandObject & cmd_obj) override {" >> ${header_file}
echo "    return std::make_shared<${class_name}>(*this);" >> ${header_file}
echo "  }" >> ${header_file}
echo "};" >> ${header_file}
echo "#endif //${macro_name}" >> ${header_file}

