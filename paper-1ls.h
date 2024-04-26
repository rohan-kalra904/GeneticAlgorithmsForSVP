#include "paper-1.h"
template<class ZT, class FT>
class Paper1_ls:public Paper1<ZT,FT>
{
    public:
    using GA<ZT, FT>::popObj;
    using Paper1<ZT, FT>::selection;
    using Paper1<ZT, FT>::cross;
    using Paper1<ZT, FT>::mutation;
    using Paper1<ZT, FT>::runCrossMut;
    using Paper1<ZT, FT>::compare;
    using Paper1<ZT, FT>::logical_xor;
    using Paper1<ZT, FT>::logical_and;
    using Paper1<ZT, FT>::runGA;
    Paper1_ls(const char *input_filename,int flags_bkz, int flags_gso, int prec, FloatType float_type);
    Individual<ZT, FT>* runCrossMut(int dim, int k) override;
};