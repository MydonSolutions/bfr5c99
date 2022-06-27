#include <stdlib.h>
#include <stdio.h>
#include "bfr5.h"

int main(){
    printf("Testing HDF5 Library...\n");

    char* hdf5_filename="../tests/golden_synthesized_input.bfr5";

    BFR5_file_t file;

    BFR5open(hdf5_filename,&file);
    printf("File Obs ID:\n\n%s\n\n",file.hdf5_obsid);

    BFR5read_src(&file);
    printf("Number of elements in the src_names dataset is : %d\n", file.src_elements);


    //DimInfo:
    BFR5read_dim_info(&file);
    printf("npol = %lu \n", file.dim_info.npol);
    printf("nbeams = %lu \n", file.dim_info.nbeams);

    //Cal:
    BFR5read_cal_all(&file);
    printf("Cal_all dataset has %d elements\n",file.cal_all_elements);
    // for(int i=0; i<file.cal_all_elements; i++){
    //     printf("");
    // }

    //Delay Info:
    BFR5read_delays(&file);

    //Delays
    printf("Delay dataset has %d elements\n",file.delay_info.delays_elements);
    printf("Delays:\n");
    // for (int i = 0; i < file.delay_info.delays_elements; i++)
    // {
    //     printf("%d: %f",i,file.delay_info.delays_data[i]);
    // }
    
    //Time Arrays
    printf("Time_array dataset has %d elements\n",file.delay_info.time_array_elements);
    printf("Time Array:\n");
    // for (int i = 0; i < file.delay_info.time_array_elements; i++)
    // {
    //     printf("%d: %f",i,file.delay_info.time_array_data[i]);
    // }

    //Beam Info:
    BFR5read_beam_info(&file);

    //RAs
    printf("Ras dataset has %d elements\n",file.beam_info.ra_elements);
    printf("RAs:\n");
    // for (int i = 0; i < file.beam_info.ra_elements; i++)
    // {
    //     printf("%d: %f",i,file.beam_info.ra_data[i]);
    // }

    //Dec
    printf("Dec dataset has %d elements\n",file.beam_info.dec_elements);
    printf("Dec:\n");
    // for (int i = 0; i < file.beam_info.dec_elements; i++)
    // {
    //     printf("%d: %f",i,file.beam_info.dec_data[i]);
    // }

    return 0;
}