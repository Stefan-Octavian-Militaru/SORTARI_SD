#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace chrono;
ifstream fin("input.txt");
bool check_sort(int n, vector<int> v)
{
    for(int i = 1; i < n; i++){
        if(v[i] < v[i-1]){
            return 0;
        }
    }
    return 1;
}
int main()
{
    int n,t,mx;
    fin >> t;

    for(int contor = 0; contor < t; contor++){
        fin >> n >> mx;
        vector<int> v;
        v.resize(n);
        for(int i = 0; i < n; i++){
            fin >> v[i];
        }
        if(n < 50000000 && mx < 1000000000)
        {
            auto start = high_resolution_clock::now();
            sort(v.begin(), v.end());

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);


            if( check_sort(n, v) == 1){
                cout << "SORTARE REUSITA";
            }
            else
            {
               cout << "SORTARE ESUATA";
            }
            cout << "\n" << "TESTUL " << contor << "\n";
            cout << "Timp de executie: " << duration.count() << " milisecunde" << endl;
        }
        else
        {
            cout << "NU POATE SORTA\n";
        }
    }
}
