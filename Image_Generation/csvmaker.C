#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TROOT.h"
#include "TMath.h"


using namespace std;
using std::cout;
using std::endl;

void csvmaker(int n=1600, TString inputfile="testing_training.root"){
  // here n is dependant on number of track. For example 100 track -> 16 layers -> 100*16=1600 coordinate pairs {(x,y)->1600}
  
  gROOT->SetBatch(kTRUE);
  gErrorIgnoreLevel = 20001;
  gStyle->SetOptFit(1011);
  
  float nentries;

   float nentries;
 
  Float_t ntrk,trk,event;
  Float_t x[n+1],y[n+1],z[n+1], d[n+1]; // array size is n+1 because limitation of array's data handling. vectors can be used here as wel
  TFile* file = new TFile(inputfile,"read"); // loading TFile
  TTree *tree = (TTree*)file->Get("TrackHit"); //reading tree
  
  ///////////////////////////////////////////////////////
  //following block assign arrays to branches from tree//
  ///////////////////////////////////////////////////////
  
  for(int i=1;i<n+1;i++){
    ostringstream branch_num;
    branch_num << i;
    string temp_x = "x" + branch_num.str();
    string temp_y = "y" + branch_num.str();
    
    char* xbranch_addr = (char*) temp_x.c_str();
    char* ybranch_addr = (char*) temp_y.c_str();

    //cout<<xbranch_addr<<" "<<ybranch_addr<<endl;
    tree->SetBranchAddress(xbranch_addr,&x[i-1]);
    tree->SetBranchAddress(ybranch_addr,&y[i-1]);
  }

  //reading total entries from Ttree file
  
  nentries = tree->GetEntries();
  cout<<"Total entries is "<<nentries<<". Putting "<<nentries/2<<" in training, rest in testing."<<endl;
  
  
  for(int event=0; event<nentries; event++){
    
    tree->GetEntry(event); //getting the eventS


  }


}
