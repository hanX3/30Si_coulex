# 30Si data processing

## Note
old version folder save the analysis code using final.root files.
Now, using tmp file.

## Process
### calibration
+ `get_his_raw/get_his_raw.cpp`: get histogram from tmp.root file
+ `check_detector.cpp`: check spectrum of each channel
+ `auto_cali.cpp`: auto cali, add 2614.5 keV
+ `get_par.cpp & macro_get_par.cpp`: get cali parameter and save parameter into ener_cal.dat
+ `check_cali.cpp & macro_check_cali.cpp`: check cali result
+ `get_Si_longtime.cpp & draw.cpp`: check Si detector vs longtime

### ana_tmpfile
#### get_time_offset
+ `analysis.h & analysis.cpp & set.h & main.cpp & Makefile`: get time difference spectrum
+ `draw.cpp`: draw time difference spectrum
+ `fit_offset.cpp`: get time offset and save to ts.offset file
#### check_time_offset
+ `analysis.h & analysis.cpp & set.h & main.cpp & Makefile`: check time difference spectrum
#### sort
+ `sort.h & sort.cpp & set.h & main.cpp & Makefile`: sort all data into one tree structure after time alignment
+ `batch_sort.sh`: shell script
#### for_Si_front_and_back_correlation
+ `build.h & build.cpp & set.h & main.cpp & Makefile`: build Si ring and sector coincidence events
+ `batch_sort.sh`: shell script
+ `analysis/cali.cpp`: for correlation
+ `analysis/check.cpp`: for correlation results
+ `analysis/draw.cpp`: for correlation results
#### build
+ `build.h & build.cpp & set.h & main.cpp & Makefile`: build Ge, Si ring and sector coincidence events
+ `batch_sort.sh`: shell script
#### doppler
+ `src/doppler.h/cpp & angle_info.h/cpp & analysis.h/cpp set.h main.cpp Makefile si_cal.txt ener_cal.dat`: doppler correction
+ `analysis.sh & batch_anlysis.sh`: analysis shell script. After run analysis.sh, the rootfile will be saved in rootfile/rootfile_$index path. Go in that path and run `hadd all.root *.root` command in the terminal to add the whole rootfiles together.
+ `try_phi.cpp`: draw doppler result with different phi rotation angles
+ `clean.sh & batch_clean.sh`: analysis shell script
+ `yield.cpp`: get yield
