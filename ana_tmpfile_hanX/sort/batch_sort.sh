#!/usr/bin/bash

#run_list=(804 805 806 808 809 810 811 812 815 816 819 820 821 822 823 824 825 826 827 828 829 830 832 833 834 835 836 837 839 840 841 842 843 845 846 847 848 849 855 856 857 858 859 860 861 862 863 864 865 866 867 868 869 870 871 872 875 876 877 878 879 880 881 882 883 884 885 886 887 888)

run_list=(890 891 892 893 894 895 896 897 898 899 900 901 902 903 904 905 910 911 912 913 914 915 916 917 918 919 920 923 924 925 926 928 929 930 931 932 933 934 935 936 937 940 952 2000)

start=`date +%s`
thread_num=36

trap "exec 1000>&-;exec 1000<&-;exit 0" 2
tmpfifo=$$.fifo
mkfifo $tmpfifo
exec 1000<>$tmpfifo
rm -rf $tmpfifo

for (( i=0; i<$thread_num; i++ ))
do
  echo >&1000
done

for run in ${run_list[@]}
do
  read -u1000
  {
    ./sort $run > out.txt
    echo >&1000
  }&
done

wait
end=`date +%s`
echo "times: `expr $end - $start`"
