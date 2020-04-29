#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <fstream>
#include <ctime>
#include <chrono>

void GetNumbers(unsigned int *a, unsigned int *b, unsigned int limit = 4294967295);
void GetNumbersFromFile(unsigned int *a, unsigned int *b, std::string l, std::string k, unsigned int limit = 4294967295);
unsigned int StringToInt(std::string x);
std::string IntToString(int x);
void DFSMain(char **t, int arraySize);
void DEL(char **t, int arraySize);

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        std::fstream czasyDEL;
        std::fstream czasyDFS;
        czasyDEL.open("CzasyDELMacierzSasiedztwa.txt", std::ios::in | std::ios::out | std::ios::trunc);
        czasyDFS.open("CzasyDFSMacierzSasiedztwa.txt", std::ios::in | std::ios::out | std::ios::trunc);
        for (int i = 1; i < argc; i++)
        {
            std::cout << i << "\n";
            std::fstream plik;
            plik.open(argv[i], std::ios::in | std::ios::out);
            unsigned int n, m;
            std::string k, l;
            plik >> k >> l;
            GetNumbersFromFile(&n, &m, k, l, 4294967291);
            char **t = (char**)calloc((n + 1) * (n + 1), sizeof(char(*)));
            for (int ppp = 0; ppp < n + 1; ppp++)
            {
                t[ppp] = (char*)calloc(n + 1, 1);
            }
            unsigned int a, b;
            for (int j = 0; !plik.eof(); j++)
            {
                plik >> k >> l;
                GetNumbersFromFile(&a, &b, k, l, n + 1);
                t[a][b] = 1;
                t[b][a] = -1;
            }
            std::clock_t timestart = std::clock();
            DEL(t, n);
            std::clock_t timeend = std::clock();
            czasyDEL << 1000.0 * (timeend - timestart) / CLOCKS_PER_SEC << "\n";
            timestart = std::clock();
            DFSMain(t, n);
            timeend = std::clock();
            czasyDFS << 1000.0 * (timeend - timestart) / CLOCKS_PER_SEC << "\n";
            for (int ppp = 0; ppp <= n; ppp++)
            {
                free(t[ppp]);
            }
            free(t);
        }
        czasyDEL.close();
        czasyDFS.close();
    }
    else
    {
        unsigned int n, m;
        GetNumbers(&n, &m);
        char **t = (char**)calloc((n + 1) * (n + 1), sizeof(char(*)));
        for (int ppp = 0; ppp < n + 1; ppp++)
        {
            t[ppp] = (char*)calloc(n + 1, 1);
        }
        unsigned int a, b;
        for (int i = 0; i < m; i++)
        {
            GetNumbers(&a, &b, n + 1);
            if (t[a][b] != 0)
            {
                std::cout << "Wykryto multigraf.\n";
                return 1;
            }
            t[a][b] = 1;
            t[b][a] = 2;
        }
        DEL(t, n);
        DFSMain(t, n);
        for (int ppp = 0; ppp <= n; ppp++)
        {
            free(t[ppp]);
        }
        free(t);
    }
    return 0;
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

void DEL(char **t, int arraySize)
{
    unsigned int *stopien = (unsigned int*)calloc(arraySize + 1, 4);
    for (int i = 1; i <= arraySize; i++)
    {
        for (int j = 1; j <= arraySize; j++)
        {
            if (t[i][j] == 2)
            {
                stopien[i]++;
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
    unsigned int current;
    unsigned int *wynik = (unsigned int*)calloc(arraySize, 4);
    while (!stos.empty())
    {
        current = stos.top();
        wynik[visited++] = current;
        stos.pop();
        for (int i = 1; i <= arraySize; i++)
        {
            if (t[current][i] == 1)
            {
                if (--stopien[i] == 0)
            {
                stos.push(i);
            }
            }
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
    free(stopien);
    free(wynik);
    return;

    return;
}

void DFS(unsigned int index, unsigned int *visited, std::vector<unsigned int> &stos, char **t, bool *isCycle, int arraySize)
{
    visited[index] = 1;
    for (int i = 1; i <= arraySize; i++)
    {
        if (t[index][i] == 1)
        {
            if (visited[i] == 1)
            {
                *isCycle = true;
            }
            else if (visited[i] == 0)
            {
                DFS(i, visited, stos, t, isCycle, arraySize);
            }
        }
    }
    visited[index] = 2;
    stos.push_back(index);
}

void DFSMain(char **t, int arraySize)
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
    free(visited);

}

