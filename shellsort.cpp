#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>
#include <iomanip>

std::ifstream fin("input.txt");

void ShellSort(std::vector<double>& v, int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            double aux = v[i];
            int j;
            for (j = i; (j >= gap && v[j-gap] > aux); j -= gap)
                v[j] = v[j-gap];
            v[j] = aux;
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
        if(n < 50000000 && maxim < 1000000000){
            auto start = std::chrono::high_resolution_clock::now();

            ShellSort(v, n);

            auto finish = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = finish - start;

            fout << "Sirul sortat complet este:\n";
            for (int i = 0; i < v.size(); ++i)
                fout << std::setprecision(10) << v[i] << " ";
            fout << "\n";

            bool ok = true;
            int poz;
            for (int i = 0; (i < v.size() - 1) && ok; ++i)
                if (v[i] > v[i+1])
                    { ok = false; poz = i; break;}

            if (ok)
                std::cout << "Sortare corecta\n";
            else
                std::cout << "Sortare incorecta " << poz << '\n';

            std::cout << "Elapsed time: " << elapsed.count() * 1000 << " milisecunde\n";
        }
        else
        {
            std::cout << "NU SORTEAZA";
        }
    }

}
