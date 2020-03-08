#include <TFile.h>
#include <TTree.h>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

class motree
{
public:
  motree(TTree* genp);
  void printmo(int j);
  void printda(int j);

  int gsize() { return (*fpt).size(); }
  float pt(int j) { return (*fpt)[j]; }
  int pdgId(int j) { return (*fpdgId)[j]; }
private:
  TTree* fgenp;
  std::vector<int>* ftr1 = 0;
  std::vector<int>* ftr2 = 0;
  std::vector<int>* ftr3 = 0;
  std::vector<int>* ftr4 = 0;

  std::vector<float>* fpt = 0;
  std::vector<float>* fphi = 0;
  std::vector<int>* fpdgId = 0;
  std::vector<int>* fstatus = 0;
  std::vector<int>* fmo1 = 0;
  std::vector<int>* fmo2 = 0;
  std::vector<int>* fmo3 = 0;
  std::vector<int>* fmo4 = 0;
  std::vector<int>* fda1 = 0;
  std::vector<int>* fda2 = 0;
  std::vector<int>* fda3 = 0;
  std::vector<int>* fda4 = 0;
  std::vector<bool> flastll;

  void showmo(int me, int layer, std::vector<bool> lastll);
  void printline(int j);
  void drawline(int layer, bool lastornot, std::vector<bool> lastll);
};

motree::motree(TTree* genp) : fgenp(genp)
{
  fgenp->SetBranchAddress("pt", &fpt);
  fgenp->SetBranchAddress("phi", &fphi);
  fgenp->SetBranchAddress("pdgId", &fpdgId);
  fgenp->SetBranchAddress("status", &fstatus);
  fgenp->SetBranchAddress("mo1", &fmo1);
  fgenp->SetBranchAddress("mo2", &fmo2);
  fgenp->SetBranchAddress("mo3", &fmo3);
  fgenp->SetBranchAddress("mo4", &fmo4);
  fgenp->SetBranchAddress("da1", &fda1);
  fgenp->SetBranchAddress("da2", &fda2);
  fgenp->SetBranchAddress("da3", &fda3);
  fgenp->SetBranchAddress("da4", &fda4);
}

void motree::printmo(int j)
{
  flastll.clear();
  flastll.push_back(true);

  ftr1 = fmo1;
  ftr2 = fmo2;
  ftr3 = fmo3;
  ftr4 = fmo4;

  printline(j);
  showmo(j, 1, flastll); 
  std::cout<<std::endl;
}

void motree::printda(int j)
{
  flastll.clear();
  flastll.push_back(true);

  ftr1 = fda1;
  ftr2 = fda2;
  ftr3 = fda3;
  ftr4 = fda4;

  printline(j);
  showmo(j, 1, flastll); 
  std::cout<<std::endl;
}

void motree::drawline(int layer, bool lastornot, std::vector<bool> lastll)
{
  for(int i=0; i<layer; i++) 
    {
      std::cout<<(lastll[i]?"    ":"\u2502   ");
    }
  std::cout<<(lastornot?"\u2514":"\u251C")<<"\u2500\u2500 ";
}

void motree::printline(int j)
{
  std::cout<<"\e[32m"<<j<<"\e[0m \e[2m=>\e[0m \e[1m"<<(*fpdgId)[j]<<"\e[0m \e[33m("<<(*fstatus)[j]<<")\e[0m \e[34m.. "<<(*fpt)[j]<<", "<<(*fphi)[j]/M_PI<<"\e[0m"<<std::endl;
}

void motree::showmo(int me, int layer, std::vector<bool> lastll)
{
  if((*ftr1)[me] >= 0) 
    {
      int imo1 = (*ftr1)[me];
      drawline(layer, (*ftr2)[me]<0, lastll);
      printline(imo1);
      std::vector<bool> lastmo1(lastll); lastmo1.push_back((*ftr2)[me]<0);
      showmo(imo1, layer+1, lastmo1);
    }
  if((*ftr2)[me] >= 0) 
    {
      int imo2 = (*ftr2)[me];
      drawline(layer, (*ftr3)[me]<0, lastll);
      printline(imo2);
      std::vector<bool> lastmo2(lastll); lastmo2.push_back((*ftr3)[me]<0);
      showmo(imo2, layer+1, lastmo2);
    }
  if((*ftr3)[me] >= 0) 
    {
      int imo3 = (*ftr3)[me];
      drawline(layer, (*ftr4)[me]<0, lastll);
      printline(imo3);
      std::vector<bool> lastmo3(lastll); lastmo3.push_back((*ftr4)[me]<0);
      showmo(imo3, layer+1, lastmo3);
    }
  if((*ftr4)[me] >= 0) 
    {
      int imo4 = (*ftr4)[me];
      drawline(layer, true, lastll);
      printline(imo4);
      std::vector<bool> lastmo4(lastll); lastmo4.push_back(true);
      showmo(imo4, layer+1, lastmo4);
    }
}
