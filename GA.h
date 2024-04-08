#pragma once
#include "repres.h"
template<class ZT,class FT> class GA
{
    public: 
    repres<ZT,FT> *popObj;
    virtual int selection(int k)=0;
    virtual bool* cross(bool* a,bool* b,ZT tot_length)=0;
    virtual bool* mutation(bool* a,ZT tot_length)=0;
    GA(const char *input_filename,int flags_bkz,int flags_gso,int prec,FloatType float_type);
    virtual ZT* runGA(FT targetNorm,int k)=0;
    virtual Individual<ZT,FT>*runCrossMut(int dim,int k)=0;
};