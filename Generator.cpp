#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

void Calculate(int ilosc, std::ifstream &ifs, std::ofstream &ofs1, std::ofstream &ofs2);
std::string IntToString(int x);
int main(void)
{
    std::ofstream averageListDEL("SrednieListaDEL"), averageListDFS("SrednieListaDFS"), averageMatrixDEL("SrednieMacierzSasiedztwaDEL"), averageMatrixDFS("SrednieMacierzSasiedztwaDFS"), averageGraphDEL("SrednieMacierzGrafuDEL"), averageGraphDFS("SrednieMacierzGrafuDFS");
    std::ofstream odchylenieListDEL("OdchyleniaListaDEL"), odchylenieListDFS("OdchyleniaListaDFS"), odchylenieMatrixDEL("OdchyleniaMacierzSasiedztwaDEL"), odchylenieMatrixDFS("OdchyleniaMacierzSasiedztwaDFS"), odchylenieGraphDEL("OdchyleniaMacierzGrafuDEL"), odchylenieGraphDFS("OdchyleniaMacierzGrafuDFS");
    std::ifstream czasDELLista("CzasyDELLista.txt"), czasDFSLista("CzasyDFSLista.txt"), czasDELMacierz("CzasyDELMacierzSasiedztwa.txt"), czasDFSMacierz("CzasyDFSMacierzSasiedztwa.txt"), czasDELGraf("CzasyDELMacierzGrafu.txt"), czasDFSGraf("CzasyDELMacierzGrafu.txt");
    srand(time(NULL));
    std::string fileName;
    std::vector<std::string> fileNames;
    for (int j = 500; j <= 500; j += 500)
    {
        for (int i = 0; i < 10; i++)
        {
            fileName = "Graph" + IntToString(i) + "N" + IntToString(j) + ".in";
            fileNames.push_back(fileName);
            std::ofstream file(fileName);
            std::cout << fileName << "\n";
            std::vector<int> toAdd;
            for (int k = 1; k <= j; k++)
            {
                toAdd.push_back(k);
            }
            file << j << " " << j*(j - 1)/4 << "\n";
            for (int k = 1; k < toAdd.size(); k++)
            {
                for (int zupa = k - 1; zupa > k / 2; zupa--)
                {
                    file << toAdd[k] << " " << toAdd[zupa];
                    if (k + 1 < toAdd.size() || k / 2 + 1 < zupa)
                    {
                        file << "\n";
                    }
                }
            }
            file.close();
        }
        std::string ultimateString1 = "Lista.exe ";
        std::string ultimateString2 = "MacierzGrafu.exe ";
        std::string ultimateString3 = "MacierzSasiedztwa.exe ";
        for (int i = 0; i < 10; i++)
        {
            ultimateString1 += fileNames[i];
            ultimateString2 += fileNames[i];
            ultimateString3 += fileNames[i];
            ultimateString1 += " ";
            ultimateString2 += " ";
            ultimateString3 += " ";
        }
        system(ultimateString2.c_str());
        system(ultimateString1.c_str());
        system(ultimateString3.c_str());
        Calculate(j, czasDELLista, averageListDEL, odchylenieListDEL);
        Calculate(j, czasDFSLista, averageListDFS, odchylenieListDFS);
        Calculate(j, czasDELMacierz, averageMatrixDEL, odchylenieMatrixDEL);
        Calculate(j, czasDFSMacierz, averageMatrixDFS, odchylenieMatrixDFS);
        Calculate(j, czasDELGraf, averageGraphDEL, odchylenieGraphDEL);
        Calculate(j, czasDFSGraf, averageGraphDFS, odchylenieGraphDFS);
        std::cout << "Press enter to continue.\n";
        getchar();
    }
}

void Calculate(int ilosc, std::ifstream &ifs, std::ofstream &ofs1, std::ofstream &ofs2)
{
    double t[10];
    std::string y[10];
    for (int i = 0; i < 10; i++)
    {
        ifs >> y[i];
        t[i] = std::stod(y[i]);
    }
    ifs.seekg(0, ifs.beg);
    double sum = 0;
    double av = 0;
    for (int i = 0; i < 10; i++)
    {
        sum += t[i];
    }
    av = sum / 10;
    ofs1 << ilosc << " " << av << "\n";
    double wariancja = 0;
    for (int i = 0; i < 10; i++)
    {
        wariancja += (t[i] - av) * (t[i] - av);
    }
    wariancja /= 10;
    wariancja = sqrt(wariancja);
    ofs2 << ilosc << " " << wariancja << "\n";
}


std::string IntToString(int x)
{
    std::stringstream y;
    y << x;
    std::string z;
    y >> z;
    return z;
}
