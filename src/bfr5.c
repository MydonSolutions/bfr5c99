#include "bfr5.h"

herr_t BFR5open(const char* hdf5_filename, BFR5_file_t* bfr5_file){

    bfr5_file->reim_tid = H5Tcreate(H5T_COMPOUND, sizeof(complex_float_t));
    H5Tinsert(bfr5_file->reim_tid, "r", HOFFSET(complex_float_t, re), H5T_IEEE_F32LE);
    H5Tinsert(bfr5_file->reim_tid, "i", HOFFSET(complex_float_t, im), H5T_IEEE_F32LE);
    
    return bfr5_file->file_id     =   H5Fopen(hdf5_filename, H5F_ACC_RDONLY, H5P_DEFAULT);
}

void BFR5read_all(BFR5_file_t* bfr5_file){
    BFR5read_dim_info(bfr5_file);
    BFR5read_tel_info(bfr5_file);
    BFR5read_obs_info(bfr5_file);
    BFR5read_cal_info(bfr5_file);
    BFR5read_beam_info(bfr5_file);
    BFR5read_delay_info(bfr5_file);
}

//DIMENSIONAL INFO
void BFR5read_dim_info(BFR5_file_t* bfr5_file){
    BFR5read_dim_nants(bfr5_file);
    BFR5read_dim_npol(bfr5_file);
    BFR5read_dim_nbeams(bfr5_file);
    BFR5read_dim_nchan(bfr5_file);
    BFR5read_dim_ntimes(bfr5_file);
}
herr_t BFR5read_dim_nants(BFR5_file_t* bfr5_file){
    bfr5_file->dim_info.nants_id = H5Dopen(bfr5_file->file_id, "/diminfo/nants", H5P_DEFAULT);
    H5Dread(bfr5_file->dim_info.nants_id, H5T_STD_I64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->dim_info.nants));
    return H5Dclose(bfr5_file->dim_info.nants_id);
}
herr_t BFR5read_dim_npol(BFR5_file_t* bfr5_file){
    bfr5_file->dim_info.npol_id = H5Dopen(bfr5_file->file_id, "/diminfo/npol", H5P_DEFAULT);
    H5Dread(bfr5_file->dim_info.npol_id, H5T_STD_I64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->dim_info.npol));
    return H5Dclose(bfr5_file->dim_info.npol_id);
}
herr_t BFR5read_dim_nbeams(BFR5_file_t* bfr5_file){
    bfr5_file->dim_info.nbeams_id = H5Dopen(bfr5_file->file_id, "/diminfo/nbeams", H5P_DEFAULT);
    H5Dread(bfr5_file->dim_info.nbeams_id, H5T_STD_I64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->dim_info.nbeams));
    return H5Dclose(bfr5_file->dim_info.nbeams_id);
}
herr_t BFR5read_dim_nchan(BFR5_file_t* bfr5_file){
    bfr5_file->dim_info.nchan_id = H5Dopen(bfr5_file->file_id, "/diminfo/nchan", H5P_DEFAULT);
    H5Dread(bfr5_file->dim_info.nchan_id, H5T_STD_I64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->dim_info.nchan));
    return H5Dclose(bfr5_file->dim_info.nchan_id);
}
herr_t BFR5read_dim_ntimes(BFR5_file_t* bfr5_file){
    bfr5_file->dim_info.ntimes_id = H5Dopen(bfr5_file->file_id, "/diminfo/ntimes", H5P_DEFAULT);
    H5Dread(bfr5_file->dim_info.ntimes_id, H5T_STD_I64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->dim_info.ntimes));
    return H5Dclose(bfr5_file->dim_info.ntimes_id);
}

//TELESCOPE INFO//
void BFR5read_tel_info(BFR5_file_t* bfr5_file){
    BFR5read_tel_antenna_positions(bfr5_file);
    BFR5read_tel_antenna_position_frame(bfr5_file);
    BFR5read_tel_antenna_names(bfr5_file); //Eish
    BFR5read_tel_antenna_numbers(bfr5_file);
    BFR5read_tel_antenna_diameters(bfr5_file);
    BFR5read_tel_latitude(bfr5_file);
    BFR5read_tel_longitude(bfr5_file);
    BFR5read_tel_altitude(bfr5_file);
    BFR5read_tel_telescope_name(bfr5_file);
}
//Float64 Array
herr_t BFR5read_tel_antenna_positions(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->tel_info.antenna_positions_id = H5Dopen(bfr5_file->file_id, "/telinfo/antenna_positions", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->tel_info.antenna_positions_id);
    bfr5_file->tel_info.antenna_position_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->tel_info.antenna_positions = malloc(bfr5_file->tel_info.antenna_position_elements*sizeof(long double));
    H5Dread(bfr5_file->tel_info.antenna_positions_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->tel_info.antenna_positions);
    return H5Dclose(bfr5_file->tel_info.antenna_positions_id);
}
//String
herr_t BFR5read_tel_antenna_position_frame(BFR5_file_t* bfr5_file){
    hid_t type;
    hid_t native_type;
    uint64_t size;
    bfr5_file->tel_info.antenna_position_frame_id = H5Dopen(bfr5_file->file_id, "/telinfo/antenna_position_frame", H5P_DEFAULT);
    type = H5Dget_type(bfr5_file->tel_info.antenna_position_frame_id);
    native_type = H5Tget_native_type(type, H5T_DIR_DEFAULT);
    size = (int)H5Tget_size(native_type);
    bfr5_file->tel_info.antenna_position_frame = malloc((size+1));
    bfr5_file->tel_info.antenna_position_frame[size] = '\0';
    H5Dread(bfr5_file->tel_info.antenna_position_frame_id, native_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, (bfr5_file->tel_info.antenna_position_frame));
    return H5Dclose(bfr5_file->tel_info.antenna_position_frame_id);
}

//String Array
herr_t BFR5read_tel_antenna_names(BFR5_file_t* bfr5_file){

    hid_t dataspace_id;
    hid_t native_type;

    bfr5_file->tel_info.antenna_names_id = H5Dopen(bfr5_file->file_id, "/telinfo/antenna_names", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->tel_info.antenna_names_id);
    bfr5_file->tel_info.antenna_name_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    native_type = H5Tvlen_create(H5T_NATIVE_CHAR);
    bfr5_file->tel_info.antenna_names = malloc((int)native_type*sizeof(hvl_t));
    H5Dread(bfr5_file->tel_info.antenna_names_id, native_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->tel_info.antenna_names);
    return H5Dclose(bfr5_file->tel_info.antenna_names_id);
}

//Integer Array
herr_t BFR5read_tel_antenna_numbers(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->tel_info.antenna_numbers_id = H5Dopen(bfr5_file->file_id, "/telinfo/antenna_numbers", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->tel_info.antenna_numbers_id);
    bfr5_file->tel_info.antenna_number_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->tel_info.antenna_numbers = malloc(bfr5_file->tel_info.antenna_number_elements*sizeof(int));
    H5Dread(bfr5_file->tel_info.antenna_numbers_id, H5T_STD_I64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->tel_info.antenna_numbers));
    return H5Dclose(bfr5_file->tel_info.antenna_numbers_id);
}
//Float64 Array
herr_t BFR5read_tel_antenna_diameters(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->tel_info.antenna_diameters_id = H5Dopen(bfr5_file->file_id, "/telinfo/antenna_diameters", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->tel_info.antenna_diameters_id);
    bfr5_file->tel_info.antenna_diameter_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->tel_info.antenna_diameters = malloc(bfr5_file->tel_info.antenna_diameter_elements*sizeof(long double));
    H5Dread(bfr5_file->tel_info.antenna_diameters_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->tel_info.antenna_diameters);
    return H5Dclose(bfr5_file->tel_info.antenna_diameters_id);
}
//Float64
herr_t BFR5read_tel_latitude(BFR5_file_t* bfr5_file){
    bfr5_file->tel_info.latitude_id = H5Dopen(bfr5_file->file_id, "/telinfo/latitude", H5P_DEFAULT);
    H5Dread(bfr5_file->tel_info.latitude_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->tel_info.latitude));
    return H5Dclose(bfr5_file->tel_info.latitude_id);
}
//Float64
herr_t BFR5read_tel_longitude(BFR5_file_t* bfr5_file){
    bfr5_file->tel_info.longitude_id = H5Dopen(bfr5_file->file_id, "/telinfo/longitude", H5P_DEFAULT);
    H5Dread(bfr5_file->tel_info.longitude_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->tel_info.longitude));
    return H5Dclose(bfr5_file->tel_info.longitude_id);
}
//Float64
herr_t BFR5read_tel_altitude(BFR5_file_t* bfr5_file){
    bfr5_file->tel_info.altitude_id = H5Dopen(bfr5_file->file_id, "/telinfo/altitude", H5P_DEFAULT);
    H5Dread(bfr5_file->tel_info.altitude_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->tel_info.altitude));
    return H5Dclose(bfr5_file->tel_info.altitude_id);
}
//String
herr_t BFR5read_tel_telescope_name(BFR5_file_t* bfr5_file){
    hid_t type;
    hid_t native_type;
    uint64_t size;
    bfr5_file->tel_info.telescope_name_id = H5Dopen(bfr5_file->file_id, "/telinfo/telescope_name", H5P_DEFAULT);
    type = H5Dget_type(bfr5_file->tel_info.telescope_name_id);
    native_type = H5Tget_native_type(type, H5T_DIR_DEFAULT);
    size = (int)H5Tget_size(native_type);
    bfr5_file->tel_info.telescope_name = malloc((size+1));
    bfr5_file->tel_info.telescope_name[size] = '\0';
    H5Dread(bfr5_file->tel_info.telescope_name_id, native_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, (bfr5_file->tel_info.telescope_name));
    return H5Dclose(bfr5_file->tel_info.telescope_name_id);
}

//OBSERVATION INFO//
void BFR5read_obs_info(BFR5_file_t* bfr5_file){
    BFR5read_obs_id(bfr5_file);
    BFR5read_obs_freq_array(bfr5_file);
    BFR5read_obs_phase_center_ra(bfr5_file);
    BFR5read_obs_phase_center_dec(bfr5_file);
    BFR5read_obs_instrument_name(bfr5_file);
}
//String
herr_t BFR5read_obs_id(BFR5_file_t* bfr5_file){
    hid_t type;
    hid_t native_type;
    uint64_t size;
    bfr5_file->obs_info.id = H5Dopen(bfr5_file->file_id, "/obsinfo/obsid", H5P_DEFAULT);
    type = H5Dget_type(bfr5_file->obs_info.id);
    native_type = H5Tget_native_type(type, H5T_DIR_DEFAULT);
    size = (int)H5Tget_size(native_type);
    bfr5_file->obs_info.obs_id = malloc((size+1));
    bfr5_file->obs_info.obs_id[size] = '\0';
    H5Dread(bfr5_file->obs_info.id, native_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, (bfr5_file->obs_info.obs_id));
    return H5Dclose(bfr5_file->obs_info.id);
}
//Float64
herr_t BFR5read_obs_freq_array(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->obs_info.freq_array_id = H5Dopen(bfr5_file->file_id, "/obsinfo/freq_array", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->obs_info.freq_array_id);
    bfr5_file->obs_info.freq_array_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->obs_info.freq_array = malloc(bfr5_file->obs_info.freq_array_elements*sizeof(double));
    H5Dread(bfr5_file->obs_info.freq_array_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, (bfr5_file->obs_info.freq_array));
    return H5Dclose(bfr5_file->obs_info.freq_array_id);
}
//Float64
herr_t BFR5read_obs_phase_center_ra(BFR5_file_t* bfr5_file){
    bfr5_file->obs_info.phase_center_ra_id = H5Dopen(bfr5_file->file_id, "/obsinfo/phase_center_ra", H5P_DEFAULT);
    H5Dread(bfr5_file->obs_info.phase_center_ra_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->obs_info.phase_center_ra));
    return H5Dclose(bfr5_file->obs_info.phase_center_ra_id);
}
//Float64
herr_t BFR5read_obs_phase_center_dec(BFR5_file_t* bfr5_file){
    bfr5_file->obs_info.phase_center_dec_id = H5Dopen(bfr5_file->file_id, "/obsinfo/phase_center_dec", H5P_DEFAULT);
    H5Dread(bfr5_file->obs_info.phase_center_dec_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->obs_info.phase_center_dec));
    return H5Dclose(bfr5_file->obs_info.phase_center_dec_id);
}
//String
herr_t BFR5read_obs_instrument_name(BFR5_file_t* bfr5_file){
    hid_t type;
    hid_t native_type;
    uint64_t size;
    bfr5_file->obs_info.instrument_name_id = H5Dopen(bfr5_file->file_id, "/obsinfo/instrument_name", H5P_DEFAULT);
    type = H5Dget_type(bfr5_file->obs_info.instrument_name_id);
    native_type = H5Tget_native_type(type, H5T_DIR_DEFAULT);
    size = (int)H5Tget_size(native_type);
    bfr5_file->obs_info.instrument_name = malloc((size+1));
    bfr5_file->obs_info.instrument_name[size] = '\0';
    H5Dread(bfr5_file->obs_info.instrument_name_id, native_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, (bfr5_file->obs_info.instrument_name));
    return H5Dclose(bfr5_file->obs_info.instrument_name_id);
}

//CALIBRATION INFO//
void BFR5read_cal_info(BFR5_file_t* bfr5_file){
    BFR5read_cal_refant(bfr5_file);
    BFR5read_cal_k(bfr5_file);
    BFR5read_cal_b(bfr5_file);
    BFR5read_cal_g(bfr5_file);
    BFR5read_cal_all(bfr5_file);
}
herr_t BFR5read_cal_refant(BFR5_file_t* bfr5_file){
    hid_t type;
    hid_t native_type;
    uint64_t size;
    bfr5_file->cal_info.refant_id = H5Dopen(bfr5_file->file_id, "/calinfo/refant", H5P_DEFAULT);
    type = H5Dget_type(bfr5_file->cal_info.refant_id);
    native_type = H5Tget_native_type(type, H5T_DIR_DEFAULT);
    size = (int)H5Tget_size(native_type);
    bfr5_file->cal_info.refant = malloc((size+1));
    bfr5_file->cal_info.refant[size] = '\0';
    H5Dread(bfr5_file->cal_info.refant_id, native_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, (bfr5_file->cal_info.refant));
    return H5Dclose(bfr5_file->cal_info.refant_id);
}
herr_t BFR5read_cal_k(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->cal_info.cal_k_id = H5Dopen(bfr5_file->file_id, "/calinfo/cal_K", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->cal_info.cal_k_id);
    H5Sget_simple_extent_dims(dataspace_id, bfr5_file->cal_info.cal_k_dims, NULL);
    bfr5_file->cal_info.cal_k_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->cal_info.cal_k = malloc(bfr5_file->cal_info.cal_k_elements*sizeof(float));
    H5Dread(bfr5_file->cal_info.cal_k_id, H5T_IEEE_F32LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->cal_info.cal_k);
    return H5Dclose(bfr5_file->cal_info.cal_k_id);
}
herr_t BFR5read_cal_b(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->cal_info.cal_b_id = H5Dopen(bfr5_file->file_id, "/calinfo/cal_B", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->cal_info.cal_b_id);
    H5Sget_simple_extent_dims(dataspace_id, bfr5_file->cal_info.cal_b_dims, NULL);
    bfr5_file->cal_info.cal_b_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->cal_info.cal_b = malloc(bfr5_file->cal_info.cal_b_elements*sizeof(complex_float_t));
    H5Dread(bfr5_file->cal_info.cal_b_id, bfr5_file->reim_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->cal_info.cal_b);
    return H5Dclose(bfr5_file->cal_info.cal_b_id);
}
herr_t BFR5read_cal_g(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->cal_info.cal_g_id = H5Dopen(bfr5_file->file_id, "/calinfo/cal_G", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->cal_info.cal_g_id);
    H5Sget_simple_extent_dims(dataspace_id, bfr5_file->cal_info.cal_g_dims, NULL);
    bfr5_file->cal_info.cal_g_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->cal_info.cal_g = malloc(bfr5_file->cal_info.cal_g_elements*sizeof(complex_float_t));
    H5Dread(bfr5_file->cal_info.cal_g_id, bfr5_file->reim_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->cal_info.cal_g);
    return H5Dclose(bfr5_file->cal_info.cal_g_id);
}
herr_t BFR5read_cal_all(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->cal_info.cal_all_id = H5Dopen(bfr5_file->file_id, "/calinfo/cal_all", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->cal_info.cal_all_id);
    H5Sget_simple_extent_dims(dataspace_id, bfr5_file->cal_info.cal_all_dims, NULL);
    bfr5_file->cal_info.cal_all_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->cal_info.cal_all = malloc(bfr5_file->cal_info.cal_all_elements*sizeof(complex_float_t));
    H5Dread(bfr5_file->cal_info.cal_all_id, bfr5_file->reim_tid, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->cal_info.cal_all);
    return H5Dclose(bfr5_file->cal_info.cal_all_id);
}

//BEAM INFO//
void BFR5read_beam_info(BFR5_file_t* bfr5_file){
    BFR5read_beam_ras(bfr5_file);
    BFR5read_beam_decs(bfr5_file);
    BFR5read_beam_src(bfr5_file);
}


herr_t BFR5read_beam_ras(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->beam_info.ras_id = H5Dopen(bfr5_file->file_id, "/beaminfo/ras", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->beam_info.ras_id);
    bfr5_file->beam_info.ra_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->beam_info.ras = malloc(bfr5_file->beam_info.ra_elements*sizeof(double));
    H5Dread(bfr5_file->beam_info.ras_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->beam_info.ras);
    return H5Dclose(bfr5_file->beam_info.ras_id);
}
herr_t BFR5read_beam_decs(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->beam_info.decs_id = H5Dopen(bfr5_file->file_id, "/beaminfo/decs", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->beam_info.decs_id);
    bfr5_file->beam_info.dec_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->beam_info.decs = malloc(bfr5_file->beam_info.dec_elements*sizeof(double));
    H5Dread(bfr5_file->beam_info.decs_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->beam_info.decs);
    return H5Dclose(bfr5_file->beam_info.decs_id);
}
herr_t BFR5read_beam_src(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->beam_info.src_names_id = H5Dopen(bfr5_file->file_id, "/beaminfo/src_names", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->beam_info.src_names_id);
    bfr5_file->beam_info.src_name_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->beam_info.native_type = H5Tvlen_create(H5T_NATIVE_CHAR);
    bfr5_file->beam_info.src_names = malloc((int)bfr5_file->beam_info.native_type*sizeof(hvl_t));
    H5Dread(bfr5_file->beam_info.src_names_id, bfr5_file->beam_info.native_type, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->beam_info.src_names);
    return H5Dclose(bfr5_file->beam_info.src_names_id);
}

//DELAY INFO//

void BFR5read_delay_info(BFR5_file_t* bfr5_file){
    BFR5read_delay_delays(bfr5_file);
    BFR5read_delay_rates(bfr5_file);
    BFR5read_delay_time_array(bfr5_file);
    BFR5read_delay_jds(bfr5_file);
    BFR5read_delay_dut1(bfr5_file);
}

herr_t BFR5read_delay_delays(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->delay_info.delays_id = H5Dopen(bfr5_file->file_id, "/delayinfo/delays", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->delay_info.delays_id);
    H5Sget_simple_extent_dims(dataspace_id, bfr5_file->delay_info.delay_dims, NULL);
    bfr5_file->delay_info.delay_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->delay_info.delays = malloc(bfr5_file->delay_info.delay_elements*sizeof(double));
    H5Dread(bfr5_file->delay_info.delays_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->delay_info.delays);
    return H5Dclose(bfr5_file->delay_info.delays_id);
}
herr_t BFR5read_delay_rates(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->delay_info.rates_id = H5Dopen(bfr5_file->file_id, "/delayinfo/rates", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->delay_info.rates_id);
    H5Sget_simple_extent_dims(dataspace_id, bfr5_file->delay_info.rate_dims, NULL);
    bfr5_file->delay_info.rate_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->delay_info.rates = malloc(bfr5_file->delay_info.rate_elements*sizeof(double));
    H5Dread(bfr5_file->delay_info.rates_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->delay_info.rates);
    return H5Dclose(bfr5_file->delay_info.rates_id);
}
herr_t BFR5read_delay_time_array(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->delay_info.time_array_id = H5Dopen(bfr5_file->file_id, "/delayinfo/time_array", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->delay_info.time_array_id);
    bfr5_file->delay_info.time_array_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);   ;
    bfr5_file->delay_info.time_array = malloc(bfr5_file->delay_info.time_array_elements*sizeof(double));
    H5Dread( bfr5_file->delay_info.time_array_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT,  bfr5_file->delay_info.time_array);
    return H5Dclose(bfr5_file->delay_info.time_array_id);
}
herr_t BFR5read_delay_jds(BFR5_file_t* bfr5_file){
    hid_t dataspace_id;
    bfr5_file->delay_info.jds_id = H5Dopen(bfr5_file->file_id, "/delayinfo/jds", H5P_DEFAULT);
    dataspace_id = H5Dget_space(bfr5_file->delay_info.jds_id);
    bfr5_file->delay_info.jd_elements = (int) H5Sget_simple_extent_npoints(dataspace_id);
    bfr5_file->delay_info.jds = malloc(bfr5_file->delay_info.jd_elements*sizeof(double));
    H5Dread(bfr5_file->delay_info.jds_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, bfr5_file->delay_info.jds);
    return H5Dclose(bfr5_file->delay_info.jds_id);
}
herr_t BFR5read_delay_dut1(BFR5_file_t* bfr5_file){
    bfr5_file->delay_info.dut1_id = H5Dopen(bfr5_file->file_id, "/delayinfo/dut1", H5P_DEFAULT);
    H5Dread(bfr5_file->delay_info.dut1_id, H5T_STD_I64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, &(bfr5_file->delay_info.dut1));
    return H5Dclose(bfr5_file->delay_info.dut1_id);
}


void BFR5free_all(BFR5_file_t* bfr5_file){
    BFR5free_tel_info(bfr5_file);
    BFR5free_obs_info(bfr5_file);
    BFR5free_cal_info(bfr5_file);
    BFR5free_beam_info(bfr5_file);
    BFR5free_delays_info(bfr5_file);
}

void BFR5free_tel_info(BFR5_file_t* bfr5_file){
    free(bfr5_file->tel_info.antenna_positions);
    free(bfr5_file->tel_info.antenna_position_frame);
    free(bfr5_file->tel_info.antenna_names);
    free(bfr5_file->tel_info.antenna_numbers);
    free(bfr5_file->tel_info.telescope_name);
}
void BFR5free_obs_info(BFR5_file_t* bfr5_file){
    free(bfr5_file->obs_info.obs_id);
    free(bfr5_file->obs_info.freq_array);
}
void BFR5free_cal_info(BFR5_file_t* bfr5_file){
    free(bfr5_file->cal_info.refant);
    free(bfr5_file->cal_info.cal_k);
    free(bfr5_file->cal_info.cal_b);
    free(bfr5_file->cal_info.cal_g);
    free(bfr5_file->cal_info.cal_all);
}
void BFR5free_beam_info(BFR5_file_t* bfr5_file){
    free(bfr5_file->beam_info.ras);
    free(bfr5_file->beam_info.decs);
    free(bfr5_file->beam_info.src_names);
    
}
void BFR5free_delays_info(BFR5_file_t* bfr5_file){
    free(bfr5_file->delay_info.delays);
    free(bfr5_file->delay_info.rates);
    free(bfr5_file->delay_info.time_array);
    free(bfr5_file->delay_info.jds);
}
herr_t BFR5close(BFR5_file_t* bfr5_file){
    return H5Fclose(bfr5_file->file_id);
}