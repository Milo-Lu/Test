#include "simulation.h"

simulation::simulation()
{
}

int simulation::my_simulation(vector<int>& V){
    // remove negative values
    for(int i=0;i<V.size();++i){
        if(V[i]<0){
            V.erase(V.begin()+i);
            --i;
        }
    }

    sort(V.begin(),V.end());

    vector<pair<int,int>> V_odd;    //seperate odd and even numbers
    vector<pair<int,int>> V_even;

    for(int i=0;i<V.size();++i){
        int index{i};
        int count{1};       //duplicates are removed. "count" represents the degree of the duplication of the element

        while(V[i]==V[index+1]){
            ++count;
            ++index;
        }
        pair<int,int> ip{V[i],count};
        V[i]%2 == 0 ? V_even.push_back(ip):V_odd.push_back(ip);
        i=index;
    }

    reduce(V_odd,V_even);      //remove the counter parts
    reduce(V_even,V_odd);

    int sum = acc(V_odd);
    sum += acc(V_even);

    return sum;
}

int simulation::acc(const vector<pair<int,int>>& lp){
    int sum_acc2{};

    for(int i=lp.size()-1;i!=-1;--i){
        sum_acc2+=pow(-2,lp[i].first)*lp[i].second;
        if(abs(sum_acc2)>1000000) throw runtime_error{"exceed the limit"};
    }
    return sum_acc2;
}

void simulation::reduce(vector<pair<int,int>>& vp1, vector<pair<int,int>>& vp2){
    for(int i=vp1.size()-1;i!=-1;--i){
        for(int j=vp2.size()-1;j!=-1;--j){

            if(vp2[j].first<vp1[i].first){
                while(pow(2,vp1[i].first-vp2[j].first)<=vp2[j].second){
                    --vp1[i].second;
                    vp2[j].second -= pow(2,vp1[i].first-vp2[j].first);

                    if(vp1[i].second==0 || vp2[j].second==0) break;
                }
                if(vp2[j].second==0) vp2.erase(vp2.begin()+j);
                if(vp1[i].second==0){
                    vp1.erase(vp1.begin()+i);
                    break;
                }
           }
        }
    }
}
