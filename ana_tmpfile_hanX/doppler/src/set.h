#ifndef SET_H
#define SET_H

#define TIMEWINDOW 40 

// #define SINGLEGEVSSINGLESI
// #define DOPPLERSI
#define DOPPLERPT

constexpr double BINNUMBER = 2048.;

constexpr double CUTGEENERGY = 200.;
constexpr double CUTSIADC = 7000.;
constexpr double CUTSIDIFF = 150.;
constexpr char RAWDATAPATH[1024] = "../../ana_finalfile_hanX/ana_rootfile";//no '/' !!!
constexpr char SAVEDATAPATH[1024] = "../rootfile";//no '/' !!! 

#endif
