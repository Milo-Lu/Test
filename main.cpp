#include <QCoreApplication>
#include "simulation.h"

using namespace std;

int f(vector<int>& A){
    // remove negative values
    for(int i=A.size()-1;i!=-1;--i){
        if(A[i]<0){
            swap(A[i],A[A.size()-1]);
            A.pop_back();
        }
    }

    sort(A.begin(),A.end());

    list<pair<int,int>> A2{};

    for(int i=0;i!=A.size();++i) A2.push_back({A[i],1});        //pair<value, sign>

    for(list<pair<int,int>>::reverse_iterator it=A2.rbegin();it!=prev(A2.rend());){
        auto it2 = next(it);
        if((*it).first==(*it2).first && (*it).second==(*it2).second){       //two elements with the same value and same sign
            A2.erase(next(it).base());
            ++(*it2).first;
            (*it2).second = -(*it2).second;     //if "value" changes, so as "sign"
            if(it!=A2.rbegin()) --it;
        }else if((*it).first==(*it2).first && (*it).second!=(*it2).second){     //two elements with the same value and different sign
            A2.erase(next(it2).base(), it.base());
        }else if((*it).first==(*it2).first+1 && (*it).second==(*it2).second){       //remove adjacent values. For example "9" and "10" of the same sign will be changed to a "9" with the opposite sign
            A2.erase(next(it).base());
            (*it2).second = -(*it2).second;
        }
        else{
            ++it;
        }
    } 
    
    int sum{};

    for(auto it=A2.begin();it!=A2.end();++it){
        sum += pow(-2,(*it).first) * (*it).second;
//        if(1000000<sum) throw runtime_error{"error: exceed the limit"};
    }
    
    if(1000000<sum) throw runtime_error{"error: exceed the limit"};
    return sum;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    vector<int> mv{2,2,2,2,2,2,5,6,9,4,12,8,8,7,7,7,7,9,8,7,7,7,7,8,8,-5,-6,-9,-8};

    cout <<  f(mv) << '\n';

    return a.exec();
}
