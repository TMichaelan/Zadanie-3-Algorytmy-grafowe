#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

void GetNumbers(unsigned int *a, unsigned int *b, unsigned int limit = 4294967295);
unsigned int StringToInt(std::string x);
std::string IntToString(int x);
void DFSMain(std::vector<unsigned int> t[], int arraySize);
void DEL(std::vector<unsigned int> t[], int arraySize);

int main(void)
{
    unsigned int n, m;
    GetNumbers(&n, &m);
    std::vector<unsigned int> t[n + 1];
    unsigned int a, b;
    for (int i = 0; i < m; i++)
    {
        GetNumbers(&a, &b, n + 1);
        t[a].push_back(b);
    }
    DEL(t, n);
    DFSMain(t, n);
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

void DEL(std::vector<unsigned int> t[], int arraySize)
{
    unsigned int stopien[arraySize + 1] = {0};
    for (int i = 1; i <= arraySize; i++)
    {
        for (int j = 0; j < t[i].size(); j++)
        {
            stopien[t[i][j]]++;
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
    unsigned int wynik[arraySize];
    while (!stos.empty())
    {
        current = stos.top();
        wynik[visited++] = current;
        stos.pop();
        for (int i = 0; i < t[current].size(); i++)
        {
            if (--stopien[t[current][i]] == 0)
            {
                stos.push(t[current][i]);
            }
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

void DFS(unsigned int index, unsigned int visited[], std::vector<unsigned int> &stos, std::vector<unsigned int> t[], bool *isCycle)
{
    visited[index] = 1;
    for (int i = 0; i < t[index].size(); i++)
    {
        if (visited[t[index][i]] == 1)
        {
            *isCycle = true;
        }
        else if (visited[t[index][i]] == 0)
        {
            DFS(t[index][i], visited, stos, t, isCycle);
        }
    }
    visited[index] = 2;
    stos.push_back(index);
}

void DFSMain(std::vector<unsigned int> t[], int arraySize)
{
    std::vector<unsigned int> stos;
    unsigned int visited[arraySize + 1] = {0};
    bool isCycle = false;
    for (int i = 1; i <= arraySize; i++)
    {
        if (!visited[i])
        {
            DFS(i, visited, stos, t, &isCycle);
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
