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

    printf("\nReading Telescope Information...\n");
    BFR5read_tel_info(&file);

    printf("\nReading Obsecrvation Information...\n");
    BFR5read_obs_info(&file);

    printf("\nReading Calibration Information...\n");
    BFR5read_cal_info(&file);

    printf("\nReading Beam Information...\n");
    BFR5read_beam_info(&file);

    printf("\nReading Delay Information...\n");
    BFR5read_delay_info(&file);

    printf("\nReading All...\n");
    BFR5read_all(&file);

    return 0;
}