#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

void merge (vector<double>& v, int a, int b, int c)
{   int i,j,k;
    int n1 = b - a + 1;
    int n2 = c - b;

    vector<double> v1(n1), v2(n2);

    for (i = 0; i < n1; i++)
        v1[i] = v[a + i];

    for (j = 0; j < n2; j++)
        v2[j] = v[j + b + 1];

    i = j = 0;
    k = a;

    while (i < n1 && j < n2)
    {
        if (v1[i] <= v2[j])
        {
            v[k] = v1[i];
            i++;
        }
        else
        {
            v[k] = v2[j];
            j++;
        }
        k++;
    }

    while(i < n1)
    {
        v[k] = v1[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        v[k] = v2[j];
        j++;
        k++;
    }
}

void merge_sort(vector<double>& v, int st, int dr)
{
    if (st < dr)
    {
        int m = st + (dr - st) / 2;
        merge_sort(v, st, m);
        merge_sort(v, m + 1, dr);
        merge(v, st, m, dr);
    }

}
int check_sort(vector<double> v, int n){
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

           merge_sort(v, 0, num_elements - 1);
           auto stop = high_resolution_clock::now();
           auto duration = duration_cast<milliseconds>(stop - start);
           cout << "TESTUL " << test << endl;
           if(check_sort(v, num_elements) == 1){
                cout << "SORTARE REUSITA ";
           }
           else
           {
               cout << "SORTARE ESUATA ";
           }
           cout << "Timp de executie: " << duration.count() << " milisecunde" << endl;
       }
       else
       {
           cout << "NU POATE SORTA\n";
       }
   }

   return 0;
}
