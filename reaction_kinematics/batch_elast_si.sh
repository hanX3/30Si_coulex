#!/usr/bin/bash

if [ -e "output_si.txt" ];then
  rm output_si.txt
fi

while IFS= read -r line; do
  angle=$(echo "$line" | awk '{print $1}')
  energy=$(echo "$line" | awk '{print $2}')
  elast -Qa $angle o "1(196Pt)" 1.3 30Si $energy >> output_si.txt
  # echo $angle 
  # echo $energy
done < input_si.txt 

