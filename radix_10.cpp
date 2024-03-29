#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
#include <cmath>
#include <chrono>
using namespace std;
using namespace std::chrono;
ifstream fin("input.txt");
void counting_sort(int stanga, int dreapta, vector<long long> &v, int cifra){
    if(stanga < dreapta){
        long long fr[10];
        vector<long long> aux;
        aux.resize(dreapta-stanga);
        for(int i = 0; i < 10; i++){
            fr[i] = 0;
        }
        for(int i = stanga; i < dreapta; i++){
            fr[v[i] / cifra % 10]++;
        }
        for(int i = 1; i < 10; i++){
            fr[i] = fr[i] + fr[i - 1];
        }
        for(int i = dreapta - 1; i >= stanga; i--){
            aux[--fr[v[i] / cifra % 10]] = v[i];
        }
        for(int i = stanga; i < dreapta; i++){
            v[i] = aux[i - stanga];
        }
    }
}
bool check_sort(int n, vector<double> v)
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
    long long t,n,mx;
    vector<long long> vect_normalizat;
    vector<double> vect_initial;
    fin >> t;
    for(int contor = 1; contor <= t; contor++){
        fin >> n >> mx;
        vect_normalizat.resize(n);
        vect_initial.resize(n);
        for(int i = 0; i < n; i++){
            fin >> vect_initial[i];
        }
        if(n < 50000000 && mx < 1000000000){
            auto start = high_resolution_clock::now();
            long long max_limit = 1;
            while(max_limit * 10 < INT_MAX / mx){
                max_limit = max_limit * 10;
            }
            mx = mx * max_limit;
            int stanga, dreapta;
            stanga = 0;
            dreapta = n-1;
            int index = 0;
            while(index < n){
                if(vect_initial[index] < 0){
                    vect_normalizat[stanga++] = abs(static_cast<long long>(vect_initial[index] * max_limit));
                }
                else
                {
                    vect_normalizat[dreapta--] = static_cast<long long>(vect_initial[index] * max_limit);
                }
                index++;
            }
            int ultimul_nr_neg;
            if(vect_normalizat[stanga] < 0){
                ultimul_nr_neg = stanga;
            }
            else
            {
                ultimul_nr_neg = stanga - 1;
            }
            for(long long cifra = 1; mx/cifra !=0 ; cifra = cifra * 10)
            {
                counting_sort(0, ultimul_nr_neg + 1, vect_normalizat, cifra);
            }
            for(long long cifra = 1; mx/cifra !=0 ; cifra = cifra * 10)
            {
                counting_sort(ultimul_nr_neg + 1, n, vect_normalizat, cifra);
            }
            for(int i = 0; i < (ultimul_nr_neg + 1)/2; i++){
                swap(vect_normalizat[i] , vect_normalizat[ultimul_nr_neg - i]);
            }
            for(int i = 0; i < n; i++){
                if(i <= ultimul_nr_neg){
                    vect_normalizat[i] = vect_normalizat[i] * -1;
                }
                vect_initial[i] = static_cast<double>(vect_normalizat[i]) / max_limit;
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            if( check_sort(n, vect_initial) == 1){
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
