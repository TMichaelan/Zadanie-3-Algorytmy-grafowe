#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <bitset>
#include <algorithm>

void GetNumbers(unsigned int *a, unsigned int *b, unsigned int limit = 4294967295);
unsigned int StringToInt(std::string x);
std::string IntToString(int x);
void DFSMain(std::vector<unsigned int> t[], int arraySize);
void DEL(long long **t, int arraySize);
void DFSMain(long long **t, int arraySize);
void DFS(unsigned int index, unsigned int visited[], std::vector<unsigned int> &stos, long long **t, bool *isCycle, int arraySize);

int main(void)
{
    unsigned int n, m;
    GetNumbers(&n, &m, 4294967291);
    long long **t = (long long**)calloc((n + 1) * (n + 4), 8);
    for (int i = 0; i < n + 1; i++)
    {
        t[i] = (long long*)calloc((n + 4), 8);
    }
    std::vector<unsigned int> Ln[n + 1], Lp[n + 1], Lb[n + 1];
    bool bit[n + 1][n + 1] = {{0}};
    unsigned int a, b;
    for (int i = 0; i < m; i++)
    {
        GetNumbers(&a, &b, n + 1);
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
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 4; j++)
        {
            std::cout << t[i][j] << " ";
        }
        std::cout << "\n";
    }

    DEL(t, n);
    DFSMain(t, n);
    free(t);
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
    unsigned int stopien[arraySize + 1] = {0};
    for (int i = 1; i <= arraySize; i++)
    {
        if (t[i][arraySize + 2] != 0)
        {
            unsigned int current = t[i][arraySize + 2];
            stopien[i]++;
            while (current != t[i][current] - arraySize)
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
    unsigned int wynik[arraySize + 1];
    while (!stos.empty())
    {
        current2 = stos.top();
        wynik[visited++] = current2;
        stos.pop();
        if (t[current2][arraySize + 1] != 0)
        {
            unsigned int current = t[current2][arraySize + 1];
            while (current != t[current2][current])
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
    else
    {
        for (int i = 0; i < arraySize; i++)
        {
            std::cout << wynik[i] << " ";
        }
        std::cout << "\n";
    }
    return;
}

void DFS(unsigned int index, unsigned int visited[], std::vector<unsigned int> &stos, long long **t, bool *isCycle, int arraySize)
{
    visited[index] = 1;
    if (t[index][arraySize + 1] != 0)
    {
        unsigned int current = t[index][arraySize + 1];
        while (current != t[index][current])
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
    unsigned int visited[arraySize + 1] = {0};
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
    else
    {
        for (int i = stos.size() - 1; i >= 0; i--)
        {
            std::cout << stos[i] << " ";
        }
        std::cout << "\n";
    }
}
