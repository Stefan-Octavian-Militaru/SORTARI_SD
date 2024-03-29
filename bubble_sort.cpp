#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;
using namespace chrono;
ifstream fin("input.txt");
void bubblesort(int stanga, int dreapta, vector<double> &v){
    bool inversiune;
    for(int i = stanga; i < dreapta - 1; i++){
        inversiune = 0;
        for(int j = stanga; j < dreapta - 1 - stanga; j++){
            if(v[j] > v[j+1]){
                swap(v[j+1], v[j]);
                inversiune = 1;
            }
        }
        if(inversiune == 0){
            break;
        }
    }
}
bool check_sort(int n, vector<double> v)
{
    for(int i = 1; i < n; i++){
        if(v[i] < v[i-1]){
            return false;
        }
    }
    return true;
}
int main()
{
    int t, n, mx;
    vector<double> v;
    fin >> t;
    for(int i = 0; i < t; i++){
        fin >> n >> mx;
        v.resize(n);
        for(int j = 0; j < n; j++){
            fin >> v[j];
        }
        if(n < 500000 && mx < 1000000000){
            auto start = high_resolution_clock::now();
            bubblesort(0,n,v);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            if( check_sort(n, v) == 1){
                cout << "SORTARE REUSITA";
            }
            else
            {
               cout << "SORTARE ESUATA";
            }
            cout << "\n" << "TESTUL " << i << "\n";
            cout << "Timp de executie: " << duration.count() << " milisecunde" << endl;
        }
        else
        {
            cout << "NU POATE SORTA\n";
        }
    }
}
