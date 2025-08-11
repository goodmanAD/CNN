#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"


using namespace std;
using std::cout;
using std::endl;

void event_data_corr(int ntrack=50,int hpt=0,int total_events=10, const char* opfile="test.txt"){
  //Declaring the variables
  float px,py,a,b,r,x,y,y1,y2,x1,x2,x_2,y_2,x_1,y_1,z,i;
  int rd;
  float q,B,pt;
  float w=1.0;
  //int hpt,lpt;
  int lpt;
  float ranchar,rand_num;
  int event;//,total_events;

  //////// defining magnetic field
  B=1;

  /////  Turn on smearing
  bool SmearingOn = false;
  
  //////// creating the random number generator
  TRandom3 *grandom = new TRandom3();
   
  /*
    pt = tranverse momentum in GeV
    r = radius of trajectory of the particle
    rd = radius of detector layer
    x,y = coordinates of intersection point
    hpt = high pt track
    lpt = low pt track
   */

  //writting output in file
  fstream file;
  //file.open("event_data.txt", ios::out);
  file.open(opfile, ios::out);
  
  
  int notrk;
  //ntrack = 50;   //choose total number of tracks
  //hpt = 0;      //choose number of high pt tracks
  lpt = ntrack-hpt; //number of low pt tracks
  //total_events = 2000; //total number of events


  //Diagnostic
  TH1F *hstpt = new TH1F("trackpt","TrackPt",150,0,150);
  TH1F *hsteta = new TH1F("tracketa","TrackEta",60,-3,3);
  TH1F *hstphi = new TH1F("trackphi","TrackPhi",64,-3.2,3.2);
  TH1F *hstq = new TH1F("trackQ","TrackQ",3,-1,2);
    
  for(event = 1 ; event<total_events+1;event++){  

    //////////////////////
    //high pT track loop//
    //////////////////////
    
    for( int trk=1; trk < hpt+1; trk++){
      
      //assigning charge//
      ranchar = grandom->Uniform(0,1);
      if(ranchar < 0.5){
	q=1;
      }
      else{
	q=-1;
      }
      
      
      pt = grandom->Uniform(100,150);
      float phi = grandom->Uniform(-3.14,3.14);
      px = pt*TMath::Cos(phi);
      py = pt*TMath::Sin(phi);

      
      r = pow((px*px+py*py),0.5)/abs(q*B); 
      a = -py/abs(q*B);
      b = px/abs(q*B);
      z = 5.0;


      hstpt->Fill(pt);
      hstphi->Fill(TMath::ATan(py/px));
      hstq->Fill(q);
      
      //this condition make sure that there in no looper.
      if(abs(r)>10){
	
	for(rd=5;rd<21;rd++){
	  float temp = pow(((4*r*r)-(rd*rd)),0.5);
	  y1 = ((b*rd*rd)/(2*r*r)) + (((a*rd)/(2*r*r))*temp); //for clockwise rotaion
	  y2 = ((b*rd*rd)/(2*r*r)) - (((a*rd)/(2*r*r))*temp); // for counter clockwise rotation
	  x1 = ((rd*rd)/(2*a))-(b*y1/a);
	  x2 = ((rd*rd)/(2*a))-(b*y2/a);
	  


	  
	  if(q==1){

	    //////////////////
	    //Smearing Block//
	    //////////////////

	    for(int j=1;;j++){
	      i =  grandom->Uniform(-1000,1000)+(x2*1000); //change these values according to your amount of smearing
	      x_2 = i/1000;
	      if(abs(x_2)<rd){break;}
	    }
	    if(y2<0){
	      y_2 = -sqrt(pow(rd,2)-pow(x_2,2));}
	    else{
	      y_2 = sqrt(pow(rd,2)-pow(x_2,2));}
	    
	    if(SmearingOn) file <<fixed<<setprecision(2)<< x_2 <<"\t"<< y_2<<"\t";
	    else
	       file <<fixed<<setprecision(2)<< x2 <<"\t"<< y2<<"\t";
	    
	  }
	  
	  if(q==-1){

	    //////////////////
	    //Smearing Block//
	    //////////////////
	    
	    for(int j=1;;j++){
	      i =  grandom->Uniform(-1000,1000)+(x1*1000); //change these values according to your amount of smearing
	      x_1 = i/1000;
	      if(abs(x_1)<rd){break;}
	    }
	    if(y1>0){
	      y_1 = sqrt(pow(rd,2)-pow(x_1,2));}
	    else{
	      y_1 = -sqrt(pow(rd,2)-pow(x_1,2));}
	    
 
	    if(SmearingOn) file <<fixed<<setprecision(2)<< x_1 <<"\t"<< y_1<<"\t";
	    else
	      file <<fixed<<setprecision(2)<< x1 <<"\t"<< y1<<"\t";
	  
	  }
	}	
      }
    }

    
    
    for(int l_trk=1; l_trk<lpt+1 ;l_trk++){

      /////////////////////
      //low pT track loop//
      /////////////////////

      
      //assigning charge//
      ranchar = grandom->Uniform(0,1);
      if(ranchar < 0.5){
	q=1;
      }
      else{
	q=-1;
      }
      
      pt = grandom->Uniform(10.01,50);
      float phi = grandom->Uniform(-3.14,3.14);
      px = pt*TMath::Cos(phi);
      py = pt*TMath::Sin(phi);
      
      
      
      r = pow((px*px+py*py),0.5)/abs(q*B); 
      a = -py/abs(q*B);
      b = px/abs(q*B);
      z = 5.0;


      hstpt->Fill(pt);
      hstphi->Fill(TMath::ATan(py/px));
      hstq->Fill(q);

      if(abs(r)>10){

	for(rd=5;rd<21;rd++){
	  float temp = pow(((4*r*r)-(rd*rd)),0.5);
	  y1 = ((b*rd*rd)/(2*r*r)) + (((a*rd)/(2*r*r))*temp); //for clockwise
	  y2 = ((b*rd*rd)/(2*r*r)) - (((a*rd)/(2*r*r))*temp); //for counter clockwise
	  x1 = ((rd*rd)/(2*a))-(b*y1/a);
	  x2 = ((rd*rd)/(2*a))-(b*y2/a);

	  
	  
	  if(q==1){
	    
	    //////////////////
	    //Smearing block//
	    //////////////////
	    for(int j=1;;j++){
	      i =  grandom->Uniform(-1000,1000)+(x2*1000); //change these values according to your amount of smearing
	      x_2 = i/1000;
	      if(abs(x_2)<rd){break;}
	    }
	    if(y2<0){
	      y_2 = -sqrt(pow(rd,2)-pow(x_2,2));}
	    else{
	      y_2 = sqrt(pow(rd,2)-pow(x_2,2));}
	  
	    if(SmearingOn) file <<fixed<<setprecision(2)<< x_2 <<"\t"<< y_2<<"\t";
	    else
	      file <<fixed<<setprecision(2)<< x2 <<"\t"<< y2<<"\t";
	    
	  }
	  
	  if(q==-1){
	    
	    //////////////////
	    //Smearing block//
	    //////////////////
	    for(int j=1;;j++){
	      i =  grandom->Uniform(-1000,1000)+(x1*1000); //change these values according to your amount of smearing
	      x_1 = i/1000;
	      if(abs(x_1)<rd){break;}
	    }
	    if(y1>0){
	      y_1 = sqrt(pow(rd,2)-pow(x_1,2));}
	    else{
	      y_1 = -sqrt(pow(rd,2)-pow(x_1,2));}
	    
	    if(SmearingOn) file <<fixed<<setprecision(2)<< x_1 <<"\t"<< y_1<<"\t";
	    else
	      file <<fixed<<setprecision(2)<< x1 <<"\t"<< y1<<"\t";
	    
	  }
	}	
      }
    }
    file <<endl;
  }

  TCanvas *c1 = new TCanvas("c1","c1",800,600); hstpt->Draw();
  TCanvas *c2 = new TCanvas("c2","c2",1000,900);
  c2->Divide(1,2); c2->cd(1); hstphi->Draw();
  c2->cd(2); hstq->Draw();
  
  
}


