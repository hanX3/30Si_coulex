#!/usr/bin/bash

beta_list=(0.5 0.6 0.7 0.8 0.9 1.0 1.1 1.2 1.3 1.4 1.5)

for beta in ${beta_list[@]}
do
  ./analysis.sh $beta
done

