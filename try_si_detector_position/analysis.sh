#!/usr/bin/bash

if [ $# -ne 1 ];then
  echo "need 1 parameter."
  echo "such as: ./batch_analysis.sh 10"
  exit 1
fi

run_list=(804 805 806 808 809 810 811 812 815 816 819 820 821 822 823 824 825 826 827 828 829 830 832 833 834 835 836 837 839 840 841 842 843 845 846 847 848 849 855 856 857 858 859 860 861 862 863 864 865 866 867 868 869 870 871 872 875 876 877 878 879 880 881 882 883 884 885 886 887 888)

cp -r si_position si_position_${1}
cd si_position_${1}

sed -i "s/d_target_si = 10/d_target_si = ${1}/g" angle_info.cpp
make clean
make

for run in ${run_list[@]}
do
  echo $run 1.0 0. 0. 0.
  ./analysis $run 1.0 0. 0. 0.
done

cd ../ana
mkdir si_position_${1}
cd si_position_${1}
cp ../analysis.cpp ./
cp ../combine.cpp ./
cp ../macro.cpp ./
root -l macro.cpp

cd ../../rootfile
mkdir si_position_${1}
mv *.root si_position_${1}

