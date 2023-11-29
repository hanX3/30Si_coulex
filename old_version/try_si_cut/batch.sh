#!/usr/bin/bash

adc_list=(2000 4000 6000 8000)
diff_list=(18 16 14 12 10 8 6 4 2)


for adc in ${adc_list[@]}
do
  for diff in ${diff_list[@]}
  do
    ./analysis.sh $adc $diff
  done
done

