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


void plotmaker(int n=1600){ // here n is dependant on number of track. For example 100 track -> 16 layers -> 100*16=1600 coordinate pairs {(x,y)->1600}
  
  gROOT->SetBatch(kTRUE);
  gErrorIgnoreLevel = 20001;
  gStyle->SetOptFit(1011);
  
  float nentries;
 
  Float_t ntrk,trk,event;
  Float_t x[n+1],y[n+1],z[n+1], d[n+1]; // array size is n+1 because limitation of array's data handling. vectors can be used here as wel
  TFile* file = new TFile("training_testing.root","read"); // loading TFile
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
  
  for(int event=0; event<nentries; event++){
    
    tree->GetEntry(event); //getting the eventS

    TCanvas *c1 = new TCanvas("c1","xy",512+4,512+28); //adding number due to aspect ratio.

    TGraph *gr_1 = new TGraph(n,x,y);
    gr_1->GetYaxis()->SetRangeUser(-40,40); //only works for y axis
    gr_1->GetXaxis()->SetLimits(-40,40); // only works for x axis
    gr_1->SetMarkerStyle(6);
    gr_1->SetMarkerSize(0.5);
    gr_1->SetTitle(" ");
    gr_1->Draw("AP");
    
    ostringstream str1;
    
    // Sending a number as a stream into output 
    // string 
    str1 << event;
    
    // the str() coverts number into string 
    string temp_iname = "images/img"+str1.str()+".png"; 
    char* img_name=(char*) temp_iname.c_str();
    
    c1->SaveAs(img_name);
    c1->Clear();

    if(event%1000 == 0 && event!=0){
      cout << "Processed "<< event << " images." << event << "\n";
      cout.flush();
    }
  }
}


