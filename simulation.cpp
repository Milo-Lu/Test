#include "simulation.h"

simulation::simulation()
{
}

int simulation::my_simulation(vector<int>& V){
    sort(V.begin(),V.end());

    vector<pair<int,int>> V_odd;    //seperate the odd and even numbers
    vector<pair<int,int>> V_even;

    for(int i=0;i<V.size();++i){
        int index{i};
        int count{1};

        while(V[i]==V[index+1]){
            ++count;
            ++index;
        }
        pair<int,int> ip{V[i],count};
        V[i]%2 == 0 ? V_even.push_back(ip):V_odd.push_back(ip);
        i=index;
    }

    reduce(V_odd,V_even);
    reduce(V_even,V_odd);
    
    int sum{};

    if(V_odd.size()==0){
        sum = acc2(V_even);
        return sum;
    }

    if(V_even.size()==0){
        sum = acc2(V_odd);
        return sum;
    }

    sum = acc(V_odd);
    sum += acc(V_even);

    return sum;
}

//normal accumulation
int simulation::acc(const vector<pair<int,int>>& lp){
    int sum{};

    for(int i=0;i!=lp.size();++i){
        sum+=pow(-2,lp[i].first)*lp[i].second;
    }
    return sum;
}

//accumulation. If limit is exceeded, terminate the program
int simulation::acc2(const vector<pair<int,int>>& lp){
    int sum{};

    for(int i=lp.size()-1;i!=-1;--i){
        sum+=pow(-2,lp[i].first)*lp[i].second;
        if(abs(sum)>1000000) throw runtime_error{"error: exceed the limit"};
    }
    return sum;
}

//remove the counter parts to simplified the calculation
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
