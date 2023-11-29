#!/usr/bin/bash

position_list=(0 1 2 3)


for pos in ${position_list[@]}
do
  ./analysis.sh ${pos}
done

