#include <adf.h>
#include "stencil_kernel.h"
using namespace adf;

template<int N>
class StencilGraph : public graph {
public:
     input_plio in_plio[3];
     output_plio out_plio[N];
     kernel k1[N];
     
     StencilGraph(){
       
      for(int i = 0;i < N;i ++) {
        k1[i] = kernel::create(jacobi_2d3_i32);
        source(k1[i]) = "stencil_kernel.cc";
        runtime<ratio>(k1[i]) = 0.9;
      }
       in_plio[0] = input_plio::create("InputData0",plio_32_bits, "input0.txt");
       in_plio[1] = input_plio::create("InputData1",plio_32_bits, "input1.txt");
       in_plio[2] = input_plio::create("InputData2",plio_32_bits, "input2.txt");
       for(int i = 0;i < N;i ++) {
        out_plio[i] = output_plio::create("OutputData"+std::to_string(i),plio_32_bits,"output"+std::to_string(i)+".txt");
       }
       
       for(int i = 0;i < N;i ++) {
        connect(in_plio[0].out[0], k1[i].in[0]);
        connect(in_plio[1].out[0], k1[i].in[1]);
        connect(in_plio[2].out[0], k1[i].in[2]);
        connect(k1[i].out[0], out_plio[i].in[0]);
       }  
        
     }
};

StencilGraph<32> mygraph;

int main(){

     mygraph.init();
     mygraph.run(1);
     mygraph.end();
     return 0;

}
