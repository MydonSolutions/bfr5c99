#ifndef __bfr5_h__
#define __bfr5_h__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hdf5.h"

typedef struct{
    uint64_t nbeams;
    uint64_t npol;
} BFR5_diminfo_t;

typedef struct{
    double* ra_data;
    int ra_elements;
    double* dec_data;
    int dec_elements;
} BFR5_beaminfo_t;

typedef struct{
    double* delays_data;
    int delays_elements;
    double* time_array_data;
    int time_array_elements;
} BFR5_delayinfo_t;

typedef struct complex_float_t{
   float re;
   float im;
  }complex_float_t;


typedef struct{

    //HDF5 File Info IDs:
    hid_t file_id;
    hid_t obs_id;
    hid_t obs_type;
    hid_t native_type;
    int obs_size;
    char* hdf5_obsid;

    //Data IDs
    hid_t cal_all_id;
    hid_t delays_id;
    hid_t time_array_id;
    hid_t ra_id;
    hid_t dec_id;
    hid_t npol_id;
    hid_t nbeams_id;

    //DataSet
    hid_t src_id;
    hid_t src_dspace_id;
    int src_elements;
    hid_t native_src_type;

    hvl_t* src_names_str;

    //Cal Data
    complex_float_t* cal_all_data;
    int cal_all_elements;
    hid_t reim_tid;

    //Diminfo Data
    uint64_t nbeams;
    uint64_t npol;

    
    BFR5_diminfo_t dim_info;
    BFR5_beaminfo_t beam_info;
    BFR5_delayinfo_t delay_info;
    
} BFR5_file_t;

herr_t status;

herr_t BFR5open(char* hdf5_filename, BFR5_file_t* BFR5file);
herr_t BFR5close(BFR5_file_t* BFR5file);
void BFR5read_src(BFR5_file_t* BFR5file);
void BFR5read_cal_all(BFR5_file_t* BFR5file);
void BFR5read_delays(BFR5_file_t* BFR5file);
void BFR5read_beam_info(BFR5_file_t* BFR5file);
void BFR5read_dim_info(BFR5_file_t* BFR5file);

#endif