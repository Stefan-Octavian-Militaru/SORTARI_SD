#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;
void insertion_sort(vector<double>& bucket)
{
    for (int i = 1; i < bucket.size(); ++i)
    {
        double key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key)
        {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

void bucket_sort(vector<double>& v)
{   int n = v.size();
    double max_val = 0.0;
    double min_val = 0.0;
    vector<vector<double>> a;
    a.resize(n);
    if (!v.empty())
    {
        max_val = *max_element(v.begin(), v.end());
        min_val = *min_element(v.begin(), v.end());
    }

    double range = max_val - min_val;
    for (int i = 0; i < n; i++)
    {
        int k = (v[i] - min_val) / (range / (n - 1));
        a[k].push_back(v[i]);
    }
    for (int i = 0; i < n; i++)
    {
        insertion_sort(a[i]);
    }

    int index = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            v[index++] = a[i][j];
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
ifstream fin("input.txt");
   if (!fin)
   {
       cerr << "Nu s-a putut deschide fisierul";
       return 1;
   }

   int num_tests;
   fin >> num_tests;

   for (int test = 0; test < num_tests; ++test)
   {
       int num_elements;
       double max_value;

       fin >> num_elements >> max_value;
       vector<double> v;
       double x;


       for (int i = 0; i < num_elements; ++i)
       {
           fin >> x;
           v.push_back(x);
       }
       if(num_elements < 50000000 && max_value < 1000000000)
       {
           auto start = high_resolution_clock::now();

           bucket_sort(v);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            if( check_sort(num_elements, v) == 1){
                cout << "SORTARE REUSITA";
            }
            else
            {
               cout << "SORTARE ESUATA";
            }
            cout << "\n" << "TESTUL " << test << "\n";
            cout << "Timp de executie: " << duration.count() << " milisecunde" << endl;
       }
       else
       {
           cout << "NU POATE SORTA";
       }
   }

   return 0;
}

