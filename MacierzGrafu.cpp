#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <bitset>
#include <algorithm>
#include <fstream>
#include <chrono>

void GetNumbers(unsigned int *a, unsigned int *b, unsigned int limit = 4294967291);
void GetNumbersFromFile(unsigned int *a, unsigned int *b, std::string l, std::string k, unsigned int limit = 4294967291);
unsigned int StringToInt(std::string x);
std::string IntToString(int x);
void DFSMain(std::vector<unsigned int> t[], int arraySize);
void DEL(long long **t, int arraySize);
void DFSMain(long long **t, int arraySize);
void DFS(unsigned int index, unsigned int visited[], std::vector<unsigned int> &stos, long long **t, bool *isCycle, int arraySize);

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::fstream czasyDEL;
        std::fstream czasyDFS;
        czasyDEL.open("CzasyDELMacierzGrafu.txt", std::ios::in | std::ios::out | std::ios::trunc);
        czasyDFS.open("CzasyDFSMacierzGrafu.txt", std::ios::in | std::ios::out | std::ios::trunc);
        for (int ppp = 1; ppp < argc; ppp++)
        {
            std::cout << ppp << "\n";
            std::fstream plik;
            plik.open(argv[ppp], std::ios::in | std::ios::out);
            unsigned int n, m;
            std::string k, l;
            plik >> k >> l;
            GetNumbersFromFile(&n, &m, k, l, 4294967291);
            long long **t = (long long**)calloc((n + 1) * (n + 4), sizeof(long long*));
            for (int i = 0; i < n + 1; i++)
            {
                t[i] = (long long*)calloc((n + 4), 8);
            }
            std::vector<unsigned int> *Ln = new std::vector<unsigned int>[n + 1];
            std::vector<unsigned int> *Lp = new std::vector<unsigned int>[n + 1];
            std::vector<unsigned int> *Lb = new std::vector<unsigned int>[n + 1];
            char **bit = (char**)calloc((n + 1)*(n + 1), 1);
            for (int i = 0; i < n + 1; i++)
            {
                bit[i] = (char*)calloc(n + 1, 1);
            }
            unsigned int a, b;
            for (int i = 0; !plik.eof(); i++)
            {
                plik >> k >> l;
                GetNumbersFromFile(&a, &b, k, l, n + 1);
                bit[a][b] = 1;
                bit[b][a] = 1;
                Lp[b].push_back(a);
                Ln[a].push_back(b);
            }
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (!bit[i][j])
                    {
                        Lb[i].push_back(j);
                    }
                }
            }

            for (int i = 1; i <= n; i++)
            {
                std::sort(Lb[i].begin(), Lb[i].end());
                std::sort(Lp[i].begin(), Lp[i].end());
                std::sort(Ln[i].begin(), Ln[i].end());
            }
            for (int i = 1; i <= n; i++)
            {
                for (int j = 0; j < Ln[i].size(); j++)
                {
                    if (!j)
                    {
                        t[i][n + 1] += Ln[i][j];
                    }
                    if (Ln[i].size() - j > 1)
                    {
                        t[i][Ln[i][j]] += Ln[i][j + 1];
                    }
                    else
                    {
                        t[i][Ln[i][j]] += Ln[i][j];
                    }
                }
                for (int j = 0; j < Lp[i].size(); j++)
                {
                    if (!j)
                    {
                        t[i][n + 2] += Lp[i][j];
                    }
                    if (Lp[i].size() - j > 1)
                    {
                        t[i][Lp[i][j]] += Lp[i][j + 1] + n;
                    }
                    else
                    {
                        t[i][Lp[i][j]] += Lp[i][j] + n;
                    }
                }
                for (int j = 0; j < Lb[i].size(); j++)
                {
                    if (!j)
                    {
                        t[i][n + 3] = Lb[i][j];
                    }
                    if (Lb[i].size() - j > 1)
                    {
                        t[i][Lb[i][j]] -= Lb[i][j + 1];
                    }
                    else
                    {
                        t[i][Lb[i][j]] -= Lb[i][j];
                    }
                }
            }
            std::clock_t timestart = std::clock();
            DEL(t, n);
            std::clock_t timeend = std::clock();
            czasyDEL << 1000.0 * (timeend - timestart) / CLOCKS_PER_SEC << "\n";
            timestart = std::clock();
            DFSMain(t, n);
            timeend = std::clock();
            czasyDFS << 1000.0 * (timeend - timestart) / CLOCKS_PER_SEC << "\n";
            free(bit);
            for (int ppp = 0; ppp <= n; ppp++)
            {
                free(t[ppp]);
            }
            free(t);
            delete Lp;
            delete Lb;
            delete Ln;
        }
        czasyDEL.close();
        czasyDFS.close();
    }
    else
    {
        unsigned int n, m;
        GetNumbers(&n, &m, 4294967291);
        long long **t = (long long**)calloc((n + 1) * (n + 4), 8);
        for (int i = 0; i < n + 1; i++)
        {
            t[i] = (long long*)calloc((n + 4), 8);
        }
        std::vector<unsigned int> *Ln = new std::vector<unsigned int>[n + 1];
        std::vector<unsigned int> *Lp = new std::vector<unsigned int>[n + 1];
        std::vector<unsigned int> *Lb = new std::vector<unsigned int>[n + 1];
        char **bit = (char**)calloc((n + 1)*(n + 1), 1);
        for (int i = 0; i < n + 1; i++)
        {
            bit[i] = (char*)calloc(n + 1, 1);
        }
        unsigned int a, b;
        for (int i = 0; i < m; i++)
        {
            GetNumbers(&a, &b, n + 1);
            if (bit[a][b] != 0 || bit[b][a] != 0)
            {
                std::cout << "Wykryto multigraf.\n";
                return 1;
            }
            bit[a][b] = 1;
            bit[b][a] = 1;
            Lp[b].push_back(a);
            Ln[a].push_back(b);
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (!bit[i][j])
                {
                    Lb[i].push_back(j);
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            std::sort(Lb[i].begin(), Lb[i].end());
            std::sort(Lp[i].begin(), Lp[i].end());
            std::sort(Ln[i].begin(), Ln[i].end());
        }
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j < Ln[i].size(); j++)
            {
                if (!j)
                {
                    t[i][n + 1] = Ln[i][j];
                }
                if (Ln[i].size() - j > 1)
                {
                    t[i][Ln[i][j]] += Ln[i][j + 1];
                }
                else
                {
                    t[i][Ln[i][j]] += Ln[i][j];
                }
            }
            for (int j = 0; j < Lp[i].size(); j++)
            {
                if (!j)
                {
                    t[i][n + 2] = Lp[i][j];
                }
                if (Lp[i].size() - j > 1)
                {
                    t[i][Lp[i][j]] += Lp[i][j + 1] + n;
                }
                else
                {
                    t[i][Lp[i][j]] += Lp[i][j] + n;
                }
            }
            for (int j = 0; j < Lb[i].size(); j++)
            {
                if (!j)
                {
                    t[i][n + 3] = Lb[i][j];
                }
                if (Lb[i].size() - j > 1)
                {
                    t[i][Lb[i][j]] -= Lb[i][j + 1];
                }
                else
                {
                    t[i][Lb[i][j]] -= Lb[i][j];
                }
            }
        }
        DEL(t, n);
        DFSMain(t, n);
        delete Ln;
        delete Lp;
        delete Lb;
        free(bit);
        for (int ppp = 0; ppp <= n; ppp++)
        {
            free(t[ppp]);
        }
        free(t);
    }
}

std::string IntToString(int x)
{
    std::stringstream y;
    y << x;
    std::string z;
    y >> z;
    return z;
}

unsigned int StringToInt(std::string x)
{
    std::stringstream y;
    y << x;
    unsigned int z;
    y >> z;
    return z;
}

void GetNumbers(unsigned int *a, unsigned int *b, unsigned int limit)
{
    unsigned int n, m;
    for (;;)
    {
        std::string l, k;
        std::cin >> l >> k;
        n = StringToInt(l);
        if (IntToString(n) != l || n > limit || n == 0)
        {
            std::cout << "Bledne dane.\n";
            continue;
        }
        m = StringToInt(k);
        if (IntToString(m) != k || m > limit || m == 0)
        {
            std::cout << "Bledne dane.\n";
            continue;
        }
        break;
    }
    *a = n;
    *b = m;
    return;
}

void GetNumbersFromFile(unsigned int *a, unsigned int *b, std::string l, std::string k, unsigned int limit)
{
    unsigned int n, m;
    for (;;)
    {
        n = StringToInt(l);
        if (IntToString(n) != l || n > limit)
        {
            std::cout << "Bledne dane.\n";
            continue;
        }
        m = StringToInt(k);
        if (IntToString(m) != k || m > limit)
        {
            std::cout << "Bledne dane.\n";
            continue;
        }
        break;
    }
    *a = n;
    *b = m;
    return;
}

void DEL(long long **t, int arraySize)
{
    unsigned int *stopien = (unsigned int*)calloc(arraySize + 1, 4);
    for (int i = 1; i <= arraySize; i++)
    {
        if (t[i][arraySize + 2] != 0)
        {
            long long current = t[i][arraySize + 2];
            stopien[i]++;
            while (current != t[i][current] - arraySize && t[i][current] > arraySize && t[i][current] <= 2 * arraySize)
            {
                stopien[i]++;
                current = t[i][current] - arraySize;
            }
        }
    }
    unsigned int visited = 0;
    std::stack<unsigned int> stos;
    for (int i = 1; i <= arraySize; i++)
    {
        if (stopien[i] == 0)
        {
            stos.push(i);
        }
    }
    unsigned int current2;
    unsigned int *wynik = (unsigned int*)calloc(arraySize + 1, 4);
    while (!stos.empty())
    {
        current2 = stos.top();
        wynik[visited++] = current2;
        stos.pop();
        if (t[current2][arraySize + 1] != 0)
        {
            unsigned int current = t[current2][arraySize + 1];
            while (current != t[current2][current] && t[current2][current] > 0 && t[current2][current] <= arraySize)
            {
                if (--stopien[current] == 0)
                    stos.push(current);
                current = t[current2][current];
            }
            if (--stopien[current] == 0)
                    stos.push(current);
        }
    }
    if (visited != arraySize)
    {
        std::cout << "Graf ma cykl.\n";
    }
    /*else
    {
        std::cout << "DEL: ";
        for (int i = 0; i < arraySize; i++)
        {
            std::cout << wynik[i] << " ";
        }
        std::cout << "\n";
    }*/
    free(wynik);
    free(stopien);
    return;
}

void DFS(unsigned int index, unsigned int *visited, std::vector<unsigned int> &stos, long long **t, bool *isCycle, int arraySize)
{
    visited[index] = 1;
    if (t[index][arraySize + 1] != 0)
    {
        unsigned int current = t[index][arraySize + 1];
        while (current != t[index][current] && t[index][current] > 0 && t[index][current] <= arraySize)
        {
            if (visited[current] == 1)
            {
                *isCycle = true;
            }
            else if (visited[current] == 0)
            {
                DFS(current, visited, stos, t, isCycle, arraySize);
            }
            current = t[index][current];
        }
        if (visited[current] == 1)
        {
            *isCycle = true;
        }
        else if (visited[current] == 0)
        {
            DFS(current, visited, stos, t, isCycle, arraySize);
        }
    }
    visited[index] = 2;
    stos.push_back(index);
}

void DFSMain(long long **t, int arraySize)
{
    std::vector<unsigned int> stos;
    unsigned int *visited = (unsigned int*)calloc(arraySize + 1, 4);
    bool isCycle = false;
    for (int i = 1; i <= arraySize; i++)
    {
        if (!visited[i])
        {
            DFS(i, visited, stos, t, &isCycle, arraySize);
        }
    }
    if (isCycle)
    {
        std::cout << "Graf ma cykl.\n";
    }
    /*else
    {
        std::cout << "DFS: ";
        for (int i = stos.size() - 1; i >= 0; i--)
        {
            std::cout << stos[i] << " ";
        }
        std::cout << "\n";
    }*/
}
