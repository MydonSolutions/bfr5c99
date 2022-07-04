#ifndef __bfr5_h__
#define __bfr5_h__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hdf5.h"

//Complex
typedef struct complex_float_t{
   float re;
   float im;
}complex_float_t;

//Diminfo
typedef struct{
    hid_t nants_id;
    uint64_t nants;

    hid_t npol_id;
    uint64_t npol;

    hid_t nchan_id;
    uint64_t nchan;

    hid_t nbeams_id;
    uint64_t nbeams;

    hid_t ntimes_id;
    uint64_t ntimes;

} BFR5_diminfo_t;

//Telinfo
typedef struct{
    hid_t antenna_positions_id;
    double* antenna_positions;
    uint64_t antenna_position_elements;

    hid_t antenna_position_frame_id;
    char* antenna_position_frame;
    
    hid_t antenna_names_id;
    hvl_t* antenna_names; 
    uint64_t antenna_name_elements; 
    
    uint64_t antenna_numbers_id;
    uint64_t* antenna_numbers;
    uint64_t antenna_number_elements; 
    
    hid_t antenna_diameters_id;
    double* antenna_diameters;
    uint64_t antenna_diameter_elements;
    
    hid_t latitude_id;
    double* latitude;
    uint64_t latitude_elements;
    
    hid_t longitude_id;
    double* longitude;
    uint64_t longitude_elements;
    
    hid_t altitude_id;
    double* altitude;
    uint64_t altitude_elements;
    
    hid_t telescope_name_id;
    char* telescope_name;
} BFR5_telinfo_t;

//Obsinfo
typedef struct{
    hid_t id;
    // hid_t obs_type;
    // hid_t native_type;
    // uint64_t obs_size;
    char* obs_id;

    hid_t freq_array_id;
    double* freq_array;
    uint64_t freq_array_elements;
    
    uint64_t phase_center_ra_id;
    hid_t phase_center_ra;
    
    uint64_t phase_center_dec_id;
    hid_t phase_center_dec;

    uint64_t instrument_name_id;
    char* instrument_name;
} BFR5_obsinfo_t;

//Calinfo
typedef struct{
    uint64_t refant_id;
    char* refant;

    hid_t cal_k_id;
    float* cal_k;
    uint64_t cal_k_elements;

    hid_t cal_b_id;
    complex_float_t* cal_b;
    uint64_t cal_b_elements;

    hid_t cal_g_id;
    complex_float_t* cal_g;
    uint64_t cal_g_elements;

    hid_t cal_all_id;
    complex_float_t* cal_all;
    uint64_t cal_all_elements;

} BFR5_calinfo_t;

//Beaminfo
typedef struct{
    hid_t ras_id;
    double* ras;
    uint64_t ra_elements;

    hid_t decs_id;
    double* decs;
    uint64_t dec_elements;

    hid_t src_names_id;
    hvl_t* src_names;
    hid_t native_type;
    uint64_t src_name_elements;

} BFR5_beaminfo_t;

//Delayinfo
typedef struct{
    hid_t delays_id;
    double* delays;
    uint64_t delay_elements;

    hid_t rates_id;
    double* rates;
    uint64_t rate_elements;

    hid_t time_array_id;
    double* time_array;
    uint64_t time_array_elements;

    hid_t jds_id;
    double* jds;
    uint64_t jd_elements;

    hid_t dut1_id;
    hid_t dut1;

} BFR5_delayinfo_t;


typedef struct{
    hid_t file_id;
    
    hid_t reim_tid;

    BFR5_diminfo_t dim_info;
    BFR5_telinfo_t tel_info;
    BFR5_obsinfo_t obs_info;
    BFR5_calinfo_t cal_info;
    BFR5_beaminfo_t beam_info;
    BFR5_delayinfo_t delay_info;
} BFR5_file_t;

herr_t status;

herr_t BFR5open(char* hdf5_filename, BFR5_file_t* BFR5file);

void BFR5read_all(BFR5_file_t* bfr5_file);

void BFR5read_dim_info(BFR5_file_t* bfr5_file);
herr_t BFR5read_dim_nants(BFR5_file_t* bfr5_file);
herr_t BFR5read_dim_npol(BFR5_file_t* bfr5_file);
herr_t BFR5read_dim_nbeams(BFR5_file_t* bfr5_file);
herr_t BFR5read_dim_nchan(BFR5_file_t* bfr5_file);
herr_t BFR5read_dim_ntimes(BFR5_file_t* bfr5_file);

void BFR5read_tel_info(BFR5_file_t* bfr5_file);
herr_t BFR5read_tel_antenna_positions(BFR5_file_t* bfr5_file);
herr_t BFR5read_tel_antenna_position_frame(BFR5_file_t* bfr5_file);
herr_t BFR5read_tel_antenna_names(BFR5_file_t* bfr5_file);
herr_t BFR5read_tel_antenna_numbers(BFR5_file_t* bfr5_file);
herr_t BFR5read_tel_antenna_diameters(BFR5_file_t* bfr5_file);
herr_t BFR5read_tel_latitude(BFR5_file_t* bfr5_file);
herr_t BFR5read_tel_longitude(BFR5_file_t* bfr5_file);
herr_t BFR5read_tel_altitude(BFR5_file_t* bfr5_file);
herr_t BFR5read_tel_telescope_name(BFR5_file_t* bfr5_file);

void BFR5read_obs_info(BFR5_file_t* bfr5_file);
herr_t BFR5read_obs_id(BFR5_file_t* bfr5_file);
herr_t BFR5read_obs_freq_array(BFR5_file_t* bfr5_file);
herr_t BFR5read_obs_phase_center_ra(BFR5_file_t* bfr5_file);
herr_t BFR5read_obs_phase_center_dec(BFR5_file_t* bfr5_file);
herr_t BFR5read_obs_instrument_name(BFR5_file_t* bfr5_file);

void BFR5read_cal_info(BFR5_file_t* bfr5_file);
herr_t BFR5read_cal_refant(BFR5_file_t* bfr5_file);
herr_t BFR5read_cal_k(BFR5_file_t* bfr5_file);
herr_t BFR5read_cal_b(BFR5_file_t* bfr5_file);
herr_t BFR5read_cal_g(BFR5_file_t* bfr5_file);
herr_t BFR5read_cal_all(BFR5_file_t* bfr5_file);

void BFR5read_beam_info(BFR5_file_t* bfr5_file);
herr_t BFR5read_beam_ras(BFR5_file_t* bfr5_file);
herr_t BFR5read_beam_decs(BFR5_file_t* bfr5_file);
herr_t BFR5read_beam_src(BFR5_file_t* bfr5_file);

void BFR5read_delay_info(BFR5_file_t* bfr5_file);
herr_t BFR5read_delay_delays(BFR5_file_t* bfr5_file);
herr_t BFR5read_delay_rates(BFR5_file_t* bfr5_file);
herr_t BFR5read_delay_time_array(BFR5_file_t* bfr5_file);
herr_t BFR5read_delay_jds(BFR5_file_t* bfr5_file);
herr_t BFR5read_delay_dut1(BFR5_file_t* bfr5_file);

//Free structs
void BFR5free_all(BFR5_file_t* bfr5_file);
void BFR5free_tele_info(BFR5_file_t* bfr5_file);
void BFR5free_obs_info(BFR5_file_t* bfr5_file);
void BFR5free_cal_info(BFR5_file_t* bfr5_file);
void BFR5free_beam_info(BFR5_file_t* bfr5_file);
void BFR5free_delays_info(BFR5_file_t* bfr5_file);
herr_t BFR5close(BFR5_file_t* bfr5_file);
#endif