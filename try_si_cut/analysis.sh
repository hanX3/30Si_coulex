#!/usr/bin/bash

if [ $# -ne 2 ];then
  echo "need 2 parameter."
  echo "such as: ./batch_analysis.sh 2000 2000"
  exit 1
fi

run_list=(804 805 806 808 809 810 811 812 815 816 819 820 821 822 823 824 825 826 827 828 829 830 832 833 834 835 836 837 839 840 841 842 843 845 846 847 848 849 855 856 857 858 859 860 861 862 863 864 865 866 867 868 869 870 871 872 875 876 877 878 879 880 881 882 883 884 885 886 887 888)

cp -r cut_si cut_si_${1}_${2}
cd cut_si_${1}_${2}

sed -i "s/CUTSIADC = 2000/CUTSIADC = ${1}/g" set.h
sed -i "s/CUTSIDIFF = 2000/CUTSIDIFF = ${2}/g" set.h
make clean
make

for run in ${run_list[@]}
do
  echo $run 1.0 0. 0. 0.
  ./analysis $run 1.0 0. 0. 0.
done

cd ../ana
mkdir adc_${1}_diff_${2}
cd adc_${1}_diff_${2}
cp ../analysis.cpp ./
cp ../combine.cpp ./
cp ../macro.cpp ./
root -l macro.cpp

cd ../../cut_si_rootfile
mkdir adc_${1}_diff_${2}
mv *.root adc_${1}_diff_${2}

