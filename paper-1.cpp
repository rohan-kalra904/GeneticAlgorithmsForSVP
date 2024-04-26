#include"paper-1.h"
using namespace std;
using namespace fplll;
template<class ZT, class FT>
int Paper1<ZT, FT>::selection(int k) {
    int pop_size=popObj->pop_size;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(0, pop_size - 1);
    FT comp;
    int val=0;
    for(int i=0;i<k;i++)
    {
        int ind=distribution(generator);
        FT use=(popObj->population[ind]).norm;
        if((comp>use)||(i==0))
        {
            comp=use;
            val=ind;
        }
    }
    return val;
}
template<class ZT, class FT>
bool* Paper1<ZT, FT>::cross(bool* a, bool* b, ZT tot_length) {
     random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, 1);
    bool *randomu=new bool[int(tot_length.get_d())];
    bool *randomubar=new bool[int(tot_length.get_d())];
    for(int i=0;i<int(tot_length.get_d());i++)
    {
        int random_val=distribution(gen);
        if(random_val)
        {
            randomu[i]=false;
            randomubar[i]=true;
        }
        else{
            randomu[i]=false;
            randomubar[i]=true;
        }
    }
    bool* ans=  logical_xor(logical_and(a,randomu,tot_length),logical_and(b,randomubar,tot_length),tot_length);
    delete[]randomu;
    delete[] randomubar;
    return ans;
}

template<class ZT, class FT>
bool* Paper1<ZT, FT>::mutation(bool* a, ZT tot_length) {
    bool* randomM=new bool[int(tot_length.get_d())];
   random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, ((int)tot_length.get_d())-1);
   for(int i=0;i<int(tot_length.get_d());i++)
   {
    int random_val=distribution(gen);
    if(random_val<1)randomM[i]=true;
    else randomM[i]=false;
   }
   bool*ans= logical_xor(a,randomM,tot_length);
   delete[] randomM;
   return ans;
}
template<class ZT, class FT>
bool* Paper1<ZT, FT>::logical_xor(bool* a, bool* b, ZT tot_length) {
     bool* result = new bool[int(tot_length.get_d())];
    for (int i = 0; i < int(tot_length.get_d()); ++i) {
        result[i] = a[i] ^ b[i];
    }
    return result;
}

template<class ZT, class FT>
bool* Paper1<ZT, FT>::logical_and(bool* a, bool* b, ZT tot_length) {
    bool* result = new bool[int(tot_length.get_d())];
    for (int i = 0; i < int(tot_length.get_d()); ++i) {
        result[i] = a[i] && b[i];
    }
    return result;
}
// template<class ZT, class FT>
// Individual<ZT, FT>* Paper1<ZT, FT>::runCrossMut(int dim, int k) {
//      Individual<ZT,FT>* newPop = new Individual<ZT,FT>[popObj->pop_size];
//     newPop[0] = popObj->population[0];
//     for(int i = 1;i<popObj->pop_size;i++)
//     {
//         bool *a = popObj->encode(popObj->population[selection(k)].y,popObj->totLength);
//         bool *b = popObj->encode(popObj->population[selection(k)].y,popObj->totLength);
//         bool *crossed = cross(a,b,popObj->totLength);
//         bool *mutated = mutation(crossed,popObj->totLength);
//         newPop[i].y =  popObj->decode(mutated);
//         newPop[i].x = newPop[i].YtoX(newPop[i].y,popObj->get_mu(),popObj->dim);
//         newPop[i].norm = newPop[i].get_norm(newPop[i].matrix_multiply(newPop[i].x,popObj->get_B(),popObj->dim),popObj->dim);
//         if(newPop[i].norm==0)
//         {
//             delete[] newPop[i].y;
//             delete[] newPop[i].x;
//             i--;
//         }
//         delete[]a;
//         delete[]b;
//         delete[]crossed;
//         delete[]mutated;
//     }
//     return newPop;
// }
template<class ZT, class FT>
Individual<ZT, FT>* Paper1<ZT, FT>::runCrossMut(int dim, int k) {
     Individual<ZT,FT>* newPop = new Individual<ZT,FT>[popObj->pop_size];
    newPop[0] = popObj->population[0];
    //cout<<popObj->pop_size<<'\n';
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
        }
       // cout<<i<<" "<<newPop[i].norm<<'\n';
        delete[]a;
        delete[]b;
        delete[]crossed;
        delete[]mutated;
    }
    return newPop;
}
template<class ZT, class FT>
bool Paper1<ZT, FT>::compare(Individual<ZT, FT>& i1, Individual<ZT, FT>& i2) {
    return (i1.norm<i2.norm);
}

template<class ZT, class FT>
Paper1<ZT, FT>::Paper1(const char *input_filename,int flags_bkz, int flags_gso, int prec, FloatType float_type)
    : GA<ZT, FT>(input_filename,flags_bkz, flags_gso, prec, float_type) {
}
// template<class ZT, class FT>
// Paper1<ZT, FT>::Paper1()
//  {
//     cout<<"Hello"<<" "<<'\n';
// }
template<class ZT, class FT>
ZT* Paper1<ZT, FT>::runGA(FT targetNorm, int k,Individual<ZT,FT> vb) {
    popObj->initialise(vb);
    
    sort(popObj->population,popObj->population+popObj->pop_size,compare);
    Individual<ZT,FT>v0 = popObj->population[0];
    ZT iter;
    FT prevNorm;
    prevNorm = 0.0;
    while(v0.norm>targetNorm)
    {
        popObj->population = runCrossMut(popObj->dim,k);
        sort(popObj->population,popObj->population+popObj->pop_size,compare);
        cout<<iter<<"\n";
        cout<<v0.norm<<" "<<prevNorm<<"\n";
        v0 = popObj->population[0];
        if(prevNorm!=v0.norm)
        {
             cout<<v0.norm<<" "<<'\n';
             prevNorm = v0.norm;
             iter = 0;
        }
        iter.add_ui(iter,1);
        if(iter==1000)
        {
            cout<<"No. of Iteration exceeds 1000\n";
            cout<<"Restarting Algorithm\n";
            delete []popObj->population;
            return runGA(targetNorm,k,v0);
        }

    }
    return v0.matrix_multiply(v0.x,popObj->get_B(),popObj->dim);
}