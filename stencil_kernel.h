#include <adf.h>
#include "aie_api/aie.hpp"
#include <aie_api/aie_adf.hpp>
#include "aie_api/utils.hpp"
#include <stdio.h>
#define __AIE_DEBUG__    



constexpr int ROW = 16;
constexpr int w   = 8;


void jacobi_2d3_i32(adf::input_buffer<float, adf::extents<ROW>>& __restrict in0, 
    adf::input_buffer<float, adf::extents<ROW>>& __restrict in1, 
    adf::input_buffer<float, adf::extents<ROW>>& __restrict in2,
    adf::output_buffer<float, adf::extents<ROW>>& __restrict out0 
);