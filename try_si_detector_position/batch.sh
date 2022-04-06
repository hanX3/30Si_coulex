#!/usr/bin/bash

position_list=(9 10 11)


for pos in ${position_list[@]}
do
  ./analysis.sh ${pos}
done

