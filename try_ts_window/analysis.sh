#!/usr/bin/bash

run_list=(804 805 806 808 809 810 811 812 815 816 819 820 821 822 823 824 825 826 827 828 829 830 832 833 834 835 836 837 839 840 841 842 843 845 846 847 848 849 855 856 857 858 859 860 861 862 863 864 865 866 867 868 869 870 871 872 875 876 877 878 879 880 881 882 883 884 885 886 887 888)

cp -r ts_window ts_window_doppler3
cd ts_window_doppler3

sed -i "154,206s/doppler1/doppler3/g" analysis.cpp
sed -i "154,206s/tr1/tr3/g" analysis.cpp
make clean
make

for run in ${run_list[@]}
do
  echo $run 1.0 0. 0. 0.
  ./analysis $run 1.0 0. 0. 0.
done

cd ../ana
mkdir ts_window_doppler3
cd ts_window_doppler3
cp ../analysis.cpp ./
cp ../combine.cpp ./
cp ../macro.cpp ./
root -l macro.cpp

cd ../../ts_window_rootfile
mkdir ts_window_doppler3
mv *.root ts_window_doppler3

