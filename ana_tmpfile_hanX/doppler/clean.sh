#!/usr/bin/bash

if [ $# -ne 1 ];then
  echo "need 1 parameter."
  echo "such as: ./clean.sh 1"
  exit 1
fi

rm -rf src_${1}
cd ./ana
rm -rf ana_${1}
cd ../
cd ./rootfile
rm -rf rootfile_${1}
