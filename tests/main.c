#include <stdlib.h>
#include <stdio.h>
#include "bfr5.h"

int main(){
    printf("Testing HDF5 Library...\n");

    char* hdf5_filename="../tests/golden_synthesized_input.bfr5";

    BFR5_file_t file;

    BFR5open(hdf5_filename,&file);
    
    BFR5read_dim_info(&file);

    printf("Reading Dimensional Information...\n");
    printf("nants: %ld\n",file.dim_info.nants);
    printf("npol: %ld\n",file.dim_info.npol);
    printf("nbeams: %ld\n",file.dim_info.nbeams);
    printf("nchan: %ld\n",file.dim_info.nchan);
    printf("ntimes: %ld\n",file.dim_info.ntimes);

    printf("\nReading All...\n");
    BFR5read_all(&file);

    printf("cal_k_dims    : [%lld, %lld]\n", file.cal_info.cal_k_dims[0], file.cal_info.cal_k_dims[1]);
    printf("cal_b_dims    : [%lld, %lld, %lld]\n", file.cal_info.cal_b_dims[0], file.cal_info.cal_b_dims[1], file.cal_info.cal_b_dims[2]);
    printf("cal_g_dims    : [%lld, %lld]\n", file.cal_info.cal_g_dims[0], file.cal_info.cal_g_dims[1]);
    printf("cal_all_dims  : [%lld, %lld, %lld]\n", file.cal_info.cal_all_dims[0], file.cal_info.cal_all_dims[1], file.cal_info.cal_all_dims[2]);
    printf("delay_dims    : [%lld, %lld, %lld]\n", file.delay_info.delay_dims[0], file.delay_info.delay_dims[1], file.delay_info.delay_dims[2]);
    printf("rate_dims     : [%lld, %lld, %lld]\n", file.delay_info.rate_dims[0], file.delay_info.rate_dims[1], file.delay_info.rate_dims[2]);


    return 0;
}