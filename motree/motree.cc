#include <TFile.h>
#include <TTree.h>
#include <string>
#include <iostream>
#include "motree.h"

void motree_main(std::string inputname, int ievent=0)
{
  TFile* inf = TFile::Open(inputname.c_str());
  TTree* genp = (TTree*)inf->Get("demo/genp");
  motree* mt = new motree(genp);
  int nentries = genp->GetEntries();

  if(ievent > 0 && ievent < nentries)
    {
      genp->GetEntry(ievent);
      for(int j=0; j<mt->gsize(); j++)
        {
          if((abs(mt->pdgId(j)) == 421 || abs(mt->pdgId(j)) == 411 || abs(mt->pdgId(j)) == 431 || abs(mt->pdgId(j)) == 4122)) 
            mt->print(j);
        }
    }
  else
    {
      for(int i=0; i<nentries; i++)
        {
          genp->GetEntry(i);
          std::cout<<"------------------------------"<<std::endl;
          for(int j=0; j<mt->gsize(); j++)
            {
              if((abs(mt->pdgId(j)) == 421 || abs(mt->pdgId(j)) == 411 || abs(mt->pdgId(j)) == 431 || abs(mt->pdgId(j)) == 4122) && mt->pt(j) > 2)
                mt->print(j);
            }
        }
    }
}

int main(int argc, char* argv[])
{
  if(argc==2) { motree_main("results_numEvent200.root", atoi(argv[1])); return 0; }
  return 1;
}
