#!/usr/bin/bash

if [ $# -ne 1 ];then
  echo "need 1 parameter."
  echo "such as: ./batch_analysis.sh 1."
  exit 1
fi

run_list=(804 805 806 808 809 810 811 812 815 816 819 820 821 822 823 824 825 826 827 828 829 830 832 833 834 835 836 837 839 840 841 842 843 845 846 847 848 849 855 856 857 858 859 860 861 862 863 864 865 866 867 868 869 870 871 872 875 876 877 878 879 880 881 882 883 884 885 886 887 888)

cp -r src src_${1}
cd src_${1}

for run in ${run_list[@]}
do
  ./analysis $run 1.0 0. 0. ${1}
done

cd ../ana
mkdir z_${1}
cd z_${1}
cp ../analysis.cpp ./
cp ../combine.cpp ./
cp ../macro.cpp ./
root -l macro.cpp

cd ../../rootfile
mkdir z_${1}
mv *.root z_${1}

