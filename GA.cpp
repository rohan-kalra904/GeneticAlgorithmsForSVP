#include "GA.h"
template<class ZT, class FT>
GA<ZT, FT>::GA(const char *input_filename,int flags_bkz, int flags_gso, int prec, FloatType float_type) {
    popObj = new repres<ZT, FT>(input_filename,flags_bkz, flags_gso, prec, float_type);
}