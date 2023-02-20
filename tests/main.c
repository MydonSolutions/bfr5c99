#include <stdlib.h>
#include <stdio.h>
#include "bfr5.h"

int main(int argc, char const *argv[]){
    printf("Testing HDF5 Library...\n");

    BFR5_file_t file;

    BFR5open(argv[1],&file);
    
    BFR5read_dim_info(&file);

    printf("Reading Dimensional Information...\n");
    printf("nants: %ld\n",file.dim_info.nants);
    printf("npol: %ld\n",file.dim_info.npol);
    printf("nbeams: %ld\n",file.dim_info.nbeams);
    printf("nchan: %ld\n",file.dim_info.nchan);
    printf("ntimes: %ld\n",file.dim_info.ntimes);


    printf("\nReading All...\n");
    BFR5read_all(&file);

    printf("instrument name: %s\n", file.obs_info.instrument_name);
    printf("observation ID: %s\n", file.obs_info.obs_id);

    printf("cal_info:\n");
    printf("\tcal_k_dims    : [%lld, %lld]\n", file.cal_info.cal_k_dims[0], file.cal_info.cal_k_dims[1]);
    printf("\tcal_b_dims    : [%lld, %lld, %lld]\n", file.cal_info.cal_b_dims[0], file.cal_info.cal_b_dims[1], file.cal_info.cal_b_dims[2]);
    printf("\tcal_g_dims    : [%lld, %lld]\n", file.cal_info.cal_g_dims[0], file.cal_info.cal_g_dims[1]);
    printf("\tcal_all_dims  : [%lld, %lld, %lld]\n", file.cal_info.cal_all_dims[0], file.cal_info.cal_all_dims[1], file.cal_info.cal_all_dims[2]);

    printf("delay_info:\n");
    printf("\tdelay_dims    : [%lld, %lld, %lld]\n", file.delay_info.delay_dims[0], file.delay_info.delay_dims[1], file.delay_info.delay_dims[2]);
    printf("\trate_dims     : [%lld, %lld, %lld]\n", file.delay_info.rate_dims[0], file.delay_info.rate_dims[1], file.delay_info.rate_dims[2]);

    printf("tel_info:\n");
    printf("\ttelescope_name              : %s\n", file.tel_info.telescope_name);
    printf("\tlatitude                    : %f\n", file.tel_info.latitude);
    printf("\tlongitude                   : %f\n", file.tel_info.longitude);
    printf("\taltitude                    : %f\n", file.tel_info.altitude);
    printf("\tantenna_position_elements   : %ld\n", file.tel_info.antenna_position_elements);
    for (int i = 0; i < file.tel_info.antenna_position_elements; i += 3) {
        printf("\t\tantpos #%d: %f, %f, %f\n", i/3, file.tel_info.antenna_positions[i], file.tel_info.antenna_positions[i+1], file.tel_info.antenna_positions[i+2]);
    }
    printf("\tantenna_name_elements       : %ld\n", file.tel_info.antenna_name_elements);
    for (int i = 0; i < file.tel_info.antenna_name_elements; i++) {
        printf("\t\tantname #%d: %s\n", i, (char*) file.tel_info.antenna_names[i]);
    }
    printf("\tantenna_number_elements     : %ld\n", file.tel_info.antenna_number_elements);
    for (int i = 0; i < file.tel_info.antenna_number_elements; i++) {
        printf("\t\tantnum #%d: %ld\n", i, file.tel_info.antenna_numbers[i]);
    }
    printf("\tantenna_diameter_elements   : %ld\n", file.tel_info.antenna_diameter_elements);
    for (int i = 0; i < file.tel_info.antenna_diameter_elements; i++) {
        printf("\t\tantdiam #%d: %f\n", i, file.tel_info.antenna_diameters[i]);
    }


    return 0;
}