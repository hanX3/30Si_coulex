#!/usr/bin/bash

if [ -e "output_pt.txt" ];then
  rm output_pt.txt
fi

while IFS= read -r line; do
  angle=$(echo "$line" | awk '{print $1}')
  energy=$(echo "$line" | awk '{print $2}')
  elast -Qa $angle o "1(196Pt)" 0.05 196Pt $energy >> output_pt.txt
  # echo $angle 
  # echo $energy
done < input_pt.txt 

