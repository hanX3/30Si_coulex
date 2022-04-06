#!/usr/bin/bash

# x y z
#change x
nohup ./analysis.sh 0 -4  0  0 & 
nohup ./analysis.sh 1 -3  0  0 & 
nohup ./analysis.sh 2 -2  0  0 & 
nohup ./analysis.sh 3 -1  0  0 & 
nohup ./analysis.sh 4  0  0  0 & 
nohup ./analysis.sh 5  1  0  0 & 
nohup ./analysis.sh 6  2  0  0 & 
nohup ./analysis.sh 7  3  0  0 & 
nohup ./analysis.sh 8  4  0  0 & 

#change y
nohup ./analysis.sh 10  0 -4  0 & 
nohup ./analysis.sh 11  0 -3  0 & 
nohup ./analysis.sh 12  0 -2  0 & 
nohup ./analysis.sh 13  0 -1  0 & 
nohup ./analysis.sh 14  0  0  0 & 
nohup ./analysis.sh 15  0  1  0 & 
nohup ./analysis.sh 16  0  2  0 & 
nohup ./analysis.sh 17  0  3  0 & 
nohup ./analysis.sh 18  0  4  0 & 

#change z
nohup ./analysis.sh 20  0  0  -4 & 
nohup ./analysis.sh 21  0  0  -3 & 
nohup ./analysis.sh 22  0  0  -2 & 
nohup ./analysis.sh 23  0  0  -1 & 
nohup ./analysis.sh 24  0  0   0 & 
nohup ./analysis.sh 25  0  0   1 & 
nohup ./analysis.sh 26  0  0   2 & 
nohup ./analysis.sh 27  0  0   3 & 
nohup ./analysis.sh 28  0  0   4 & 
