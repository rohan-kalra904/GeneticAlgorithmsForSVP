#include "paper-1ls.h"

template<class ZT, class FT>
Paper1_ls<ZT, FT>::Paper1_ls(const char *input_filename,int flags_bkz, int flags_gso, int prec, FloatType float_type)
    : Paper1<ZT, FT>(input_filename,flags_bkz, flags_gso, prec, float_type) {
}

template<class ZT, class FT>
Individual<ZT, FT>* Paper1_ls<ZT, FT>::runCrossMut(int dim, int k) {//local search
     Individual<ZT,FT>* newPop = new Individual<ZT,FT>[popObj->pop_size];
    newPop[0] = popObj->population[0];
    for(int i = 1;i<popObj->pop_size;i++)
    {
        bool *a = popObj->encode(popObj->population[selection(k)].y,popObj->totLength);
        bool *b = popObj->encode(popObj->population[selection(k)].y,popObj->totLength);
        bool *crossed = cross(a,b,popObj->totLength);
        bool *mutated = mutation(crossed,popObj->totLength);
        newPop[i].y =  popObj->decode(mutated);
        newPop[i].x = newPop[i].YtoX(newPop[i].y,popObj->get_mu(),popObj->dim);
        newPop[i].norm = newPop[i].get_norm(newPop[i].matrix_multiply(newPop[i].x,popObj->get_B(),popObj->dim),popObj->dim);
        if(newPop[i].norm==0)
        {
        delete[] newPop[i].y;
        delete[] newPop[i].x;
        i--;
        delete[]a;
        delete[]b;
        delete[]crossed;
        delete[]mutated;
        continue;
        }
        FT norm =newPop[i].norm;
        int pos=-1;
        int sgn;
        for(int j=0;j<dim;j++)
        {
            newPop[i].y[j].sub_ui(newPop[i].y[j],1);
            ZT* use=newPop[i].YtoX(newPop[i].y,popObj->get_mu(),popObj->dim);
            FT temp=newPop[i].get_norm(newPop[i].matrix_multiply(use,popObj->get_B(),popObj->dim),popObj->dim);
            if((temp!=0)&&(temp<norm))
            {
                pos=j;
                sgn=-1;
                norm=temp;
            }
            newPop[i].y[j].add_ui(newPop[i].y[j],2);
            use=newPop[i].YtoX(newPop[i].y,popObj->get_mu(),popObj->dim);
            temp=newPop[i].get_norm(newPop[i].matrix_multiply(use,popObj->get_B(),popObj->dim),popObj->dim);
            if((temp!=0)&&(temp<norm))
            {
                pos=j;
                sgn=+1;
                norm=temp;
            }
            newPop[i].y[j].sub_ui(newPop[i].y[j],1);
        }
        if(pos!=(-1))
        {
            // newPop[i].y[pos]+=sgn;
            if(sgn==-1)
            {
                newPop[i].y[pos].sub_ui(newPop[i].y[pos],1);
            }
            else if(sgn==1)
            {
                newPop[i].y[pos].add_ui(newPop[i].y[pos],1);

            }
            newPop[i].x=newPop[i].YtoX(newPop[i].y,popObj->get_mu(),popObj->dim);
            newPop[i].norm=norm;
        }
        delete[]a;
        delete[]b;
        delete[]crossed;
        delete[]mutated;
    }
    return newPop;
}