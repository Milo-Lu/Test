#include <QCoreApplication>
#include <iostream>

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
    //if(20<A[i]) throw runtime_error{"error: exceed the limit"};       //test the first element. Magic number is used to save some space
    list<pair<int,int>> A2{};       //pair<value,sign>

    for(int i=0;i!=A.size();++i) A[i]%2==1 ? A2.push_front({A[i],-1}) : A2.push_front({A[i],1}); //sign is -1 for odd numbers, +1 for even numbers

    for(auto it=A2.begin();it!=prev(A2.end());){
        auto it2 = next(it);
        if((*it).first==(*it2).first && (*it).second==(*it2).second){       //two elements with the same value and same sign, remove one, incease the value of the other one
            it = A2.erase(it);
            ++(*it).first;
            if(it!=A2.begin()) --it;
        }else if((*it).first==(*it2).first && (*it).second!=(*it2).second){     //two elements with the same value and different sign, remove both values
            it = A2.erase(it,next(it2));
        }else if((*it).first==(*it2).first+1 && (*it).second!=(*it2).second){       //remove adjacent values. For example "9" and "10" of the same sign will be changed to a "9" with the opposite sign
            it = A2.erase(it);
            (*it).second = -(*it).second;
        }
        else{
            ++it;
        }
    }
    int sum{};

    for(auto it=A2.begin();it!=A2.end();++it){
        sum += pow(2,(*it).first) * (*it).second;
//        if(1000000<sum) throw runtime_error{"error: exceed the limit"};
    }

    if(1000000<sum) throw runtime_error{"error: exceed the limit"};     //magic number is used to save some space
    return sum;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    vector<int> mv{2,2,2,2,2,2,5,6,9,4,12,8,8,7,7,7,7,9,8,7,7,7,7,8,8,-5,-6,-9,-8};
    vector<int> mv1{3,4,5,-9,2,2,6};
    cout << f(mv) << '\n';

    return a.exec();
}
