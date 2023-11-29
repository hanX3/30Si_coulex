#ifndef SET_H
#define SET_H

constexpr int GEMODNUMMIN = 0;
constexpr int GEMODNUMMAX = 4;
constexpr int GEMODNUM = GEMODNUMMAX-GEMODNUMMIN+1;
constexpr int SIMODNUMMIN = 5;
constexpr int SIMODNUMMAX = 8;
constexpr int SIMODNUM = SIMODNUMMAX-SIMODNUMMIN+1;

constexpr double CUTGE = 200.;//keV
constexpr double CUTSI = 2000.;//channel

constexpr double TIMEWINDOW1 = 200.;//ns
constexpr double TIMEWINDOW2 = 100.;//ns


#endif
