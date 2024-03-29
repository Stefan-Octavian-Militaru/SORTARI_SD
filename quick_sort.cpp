#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <random>
#include <iomanip>

std::ifstream fin("input.txt");
void mediana (std::vector<double>& v, int a, int b, int c)
{
    if (v[a] > v[b])
        std::swap(v[a], v[b]);
    if (v[b] > v[c])
        std::swap(v[b],v[c]);
    if (v[a] > v[b])
        std::swap(v[a],v[b]);
}

void partition (std::vector<double>& v,int& lowp, int& highp, double pivot)
{
    int mid = lowp;
    while (mid <= highp)
    {
        if (v[mid] < pivot)
            std::swap(v[mid++], v[lowp++]);
        else if (v[mid] > pivot)
            std::swap(v[mid], v[highp--]);
        else if (v[mid] == pivot)
            mid++;
    }
}

void quicksort(std::vector<double>& v, int first, int last)
{
    while (first < last)
    {
        int lowp = first, highp = last;
        int middle = first + (last - first + 1) / 2;
        mediana(v, first, middle, last);
        double pivot = v[middle];
        partition(v,lowp, highp, pivot);

        if (lowp - first < last - highp)
        {
            quicksort(v, first, lowp - 1);
            first = highp + 1;
        }
        else
        {
            quicksort(v,highp + 1, last);
            last = lowp - 1;
        }
    }
}


int main()
{
    std::vector <double> v;
    int t;
    fin >> t;
    for(int contor = 0; contor < t; contor++){
        int n, maxim;
        fin >> n >> maxim;

        v.resize(n);
        for (int i = 0; i < n; ++i)
            fin >> v[i];
        if(n < 50000000 && maxim < 1000000000)
        {
            auto start1 = std::chrono::high_resolution_clock::now();

            quicksort(v, 0, v.size()-1);

            auto finish1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed1 = finish1 - start1;
            bool ok = true; int poz;

            for (int i = 0; (i < v.size() - 1) && ok; ++i)
                if (v[i] > v[i+1])
                    { ok = false; poz = i; break;}

            if (ok)
                std::cout << "Sortare corecta\n";
            else
                std::cout << "Sortare incorecta " << poz << '\n';

            std::cout << "Elapsed time: " << elapsed1.count() << " s\n";
        }
        else
        {
            std::cout << "NU POATE SORTA\n";
        }
    }


}
