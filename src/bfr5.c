#include "bfr5.h"

herr_t BFR5open(char* hdf5_filename, BFR5_file_t* bfr5_file){

    bfr5_file->reim_tid = H5Tcreate(H5T_COMPOUND, sizeof(complex_float_t));
    H5Tinsert(bfr5_file->reim_tid, "r", HOFFSET(complex_float_t, re), H5T_IEEE_F32LE);
    H5Tinsert(bfr5_file->reim_tid, "i", HOFFSET(complex_float_t, im), H5T_IEEE_F32LE);
    
    bfr5_file->file_id     =   H5Fopen(hdf5_filename,H5F_ACC_RDONLY,H5P_DEFAULT);
    bfr5_file->obs_id      =   H5Dopen(bfr5_file->file_id, "/obsinfo/obsid", H5P_DEFAULT);
    bfr5_file->obs_type    =   H5Dget_type(bfr5_file->obs_id);
    bfr5_file->native_type =   H5Tget_native_type(bfr5_file->obs_type, H5T_DIR_DEFAULT);
    bfr5_file->obs_size    =   (int)H5Tget_size(bfr5_file->native_type);

    if(bfr5_file->file_id==-1){
        return -1;
    }
    else{
        bfr5_file->hdf5_obsid  =   malloc((bfr5_file->obs_size+1));
        bfr5_file->hdf5_obsid[bfr5_file->obs_size] = '\0'; //Null termination
        status      =   H5Dread(bfr5_file->obs_id, bfr5_file->native_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->hdf5_obsid);
        status      =   H5Dclose(bfr5_file->obs_id);

        BFR5read_src(bfr5_file);
        BFR5read_dim_info(bfr5_file);
        BFR5read_cal_all(bfr5_file);
        BFR5read_delays(bfr5_file);
        BFR5read_beam_info(bfr5_file);

        return 0;
    }
}

herr_t BFR5close(BFR5_file_t* bfr5_file){
    //HDF5 File Info IDs:
    free(bfr5_file->hdf5_obsid);

    //Src
    free(bfr5_file->src_names_str);

    //Cal Data
    free(bfr5_file->cal_all_data);

    //Beam Data
    free(bfr5_file->beam_info.dec_data);
    free(bfr5_file->beam_info.ra_data);

    //Delay Info
    free(bfr5_file->delay_info.delays_data);
    free(bfr5_file->delay_info.time_array_data);
    status = H5Fclose(bfr5_file->file_id);
    return status;
}

void BFR5read_src(BFR5_file_t* bfr5_file){
    bfr5_file->src_id        =   H5Dopen(bfr5_file->file_id, "/beaminfo/src_names", H5P_DEFAULT);
    bfr5_file->src_dspace_id =   H5Dget_space(bfr5_file->src_id);
    bfr5_file->src_elements  =   H5Sget_simple_extent_npoints(bfr5_file->src_dspace_id);
    bfr5_file->native_src_type = H5Tvlen_create(H5T_NATIVE_CHAR);
    bfr5_file->src_names_str =   malloc((int)bfr5_file->src_elements*sizeof(hvl_t));
    status                  =   H5Dread(bfr5_file->src_id, bfr5_file->native_src_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->src_names_str);
    status                  =   H5Dclose(bfr5_file->src_id);
}

//Read Cal
void BFR5read_cal_all(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    herr_t elements;
    bfr5_file->cal_all_id            =   H5Dopen(bfr5_file->file_id, "/calinfo/cal_all", H5P_DEFAULT);
    dataspace_id                    =   H5Dget_space(bfr5_file->cal_all_id);
    elements                        =   H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->cal_all_elements              =  (int) elements;
    bfr5_file->cal_all_data          =   malloc((int)elements*sizeof(complex_float_t));
    status = H5Dread(bfr5_file->cal_all_id, bfr5_file->reim_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->cal_all_data);
}

void BFR5read_delays(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    herr_t elements;

    //Read delays
    bfr5_file->delays_id             =   H5Dopen(bfr5_file->file_id, "/delayinfo/delays", H5P_DEFAULT);
    dataspace_id                    =   H5Dget_space(bfr5_file->delays_id);
    elements                        =   H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->delay_info.delays_elements    =  (int) elements;
    bfr5_file->delay_info.delays_data    =   malloc((int)elements*sizeof(double));
    status = H5Dread(bfr5_file->delays_id, H5T_IEEE_F64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->delay_info.delays_data);

    //Read time array
    bfr5_file->time_array_id         =   H5Dopen(bfr5_file->file_id, "/delayinfo/time_array", H5P_DEFAULT);
    dataspace_id                    =   H5Dget_space(bfr5_file->time_array_id);
    elements                        =   H5Sget_simple_extent_npoints(dataspace_id);    
    bfr5_file->delay_info.time_array_elements    =  (int) elements;
    bfr5_file->delay_info.time_array_data    =   malloc((int)elements*sizeof(double));
    status = H5Dread( bfr5_file->time_array_id, H5T_IEEE_F64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT,  bfr5_file->delay_info.time_array_data);

}

void BFR5read_beam_info(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    herr_t elements;
    
    //Read ras
    bfr5_file->ra_id                 =   H5Dopen(bfr5_file->file_id, "/beaminfo/ras", H5P_DEFAULT);
    dataspace_id                    =   H5Dget_space(bfr5_file->ra_id);
    elements                        =   H5Sget_simple_extent_npoints(dataspace_id);      
    bfr5_file->beam_info.ra_elements =  (int) elements;
    bfr5_file->beam_info.ra_data     =   malloc((int)elements*sizeof(double));
    status = H5Dread( bfr5_file->ra_id, H5T_IEEE_F64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT,  bfr5_file->beam_info.ra_data);

    //Read dec
    bfr5_file->dec_id                =   H5Dopen(bfr5_file->file_id, "/beaminfo/decs", H5P_DEFAULT);
    dataspace_id                    =   H5Dget_space(bfr5_file->dec_id);
    elements                        =   H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->beam_info.dec_elements    =  (int) elements;
    bfr5_file->beam_info.dec_data    =   malloc((int)elements*sizeof(double));
    status = H5Dread( bfr5_file->dec_id, H5T_IEEE_F64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT,  bfr5_file->beam_info.dec_data);

}

void BFR5read_dim_info(BFR5_file_t* bfr5_file){
    //Read npol
    bfr5_file->npol_id   =   H5Dopen(bfr5_file->file_id, "/diminfo/npol", H5P_DEFAULT);
    status              =   H5Dread(bfr5_file->npol_id, H5T_STD_I64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->dim_info.npol));

    //Read nbeams
    bfr5_file->nbeams_id =   H5Dopen(bfr5_file->file_id, "/diminfo/nbeams", H5P_DEFAULT);
    status              =   H5Dread(bfr5_file->nbeams_id, H5T_STD_I64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->dim_info.nbeams));

}