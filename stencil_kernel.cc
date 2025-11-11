#include <stencil_kernel.h>
using namespace adf;

void jacobi_2d3_i32(
    adf::input_buffer<float, adf::extents<ROW>>& __restrict in0, 
    adf::input_buffer<float, adf::extents<ROW>>& __restrict in1, 
    adf::input_buffer<float, adf::extents<ROW>>& __restrict in2,
    adf::output_buffer<float, adf::extents<ROW>>& __restrict out0
) {
    auto in0ptr  = aie::begin_vector<w>(in0);
    auto in1ptr  = aie::begin_vector<w>(in1);
    auto in2ptr  = aie::begin_vector<w>(in2);
    auto out0ptr = aie::begin_vector<w>(out0);

    const float* pTop = in0.data();
    const float* pMid = in1.data();
    const float* pBot = in2.data();
    float*       pOut = out0.data();
    

    aie::vector<float, w> k_center   = aie::broadcast<float, w>(1);
    aie::vector<float, w> k_neighbor = aie::broadcast<float, w>(1);

    for (int i = 0; i < 16; i += w) {
        aie::vector<float,w> top = aie::load_unaligned_v<w>(pTop+i+1);
        aie::vector<float,w> mid = aie::load_unaligned_v<w>(pMid+i+1);
        aie::vector<float,w> left = aie::load_unaligned_v<w>(pMid+i);
        aie::vector<float,w> right = aie::load_unaligned_v<w>(pMid+i+2);
        aie::vector<float,w> bot = aie::load_unaligned_v<w>(pBot+i+1); 

        aie::accum<accfloat, w> acc = aie::zeros<accfloat, w>();
        acc = aie::mac(acc, mid,   k_center);
        acc = aie::mac(acc, top,  k_neighbor);
        acc = aie::mac(acc, bot,  k_neighbor);
        acc = aie::mac(acc, left,  k_neighbor);
        acc = aie::mac(acc, right, k_neighbor);

        aie::store_v(pOut + i, aie::to_vector<float>(acc));

        aie::print(aie::to_vector<float>(acc), true, "out: ");
        aie::print(mid,  true, "mid: ");
        aie::print(top,  true, "top: ");
        aie::print(bot,  true, "bot: ");
        aie::print(left,  true, "left:");
        aie::print(right, true, "right:");
    }
}












