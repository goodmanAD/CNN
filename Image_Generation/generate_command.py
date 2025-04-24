

ntracks = 50
nlayers = 16

vars_needed = ntracks*nlayers
thevars = ''

for i in range(1,vars_needed+1) :
    if i!=1 :
        thevars += ":"
    hitvar = "x"+str(i)+":y"+str(i)
    thevars += hitvar


textforrootscript = """
void makeMyTree(TString inputname, TString outputname){{
  //inputname=event_data.txt
  //outputname=training_testing.root
  TTree *MyTree = new TTree("TrackHit","TrackHit");
  MyTree->ReadFile(inputname,"{a}");
  MyTree->SaveAs(outputname);
}}
""".format(a=thevars)


#textforrootscript = """
#void makeMyTree(){{
#  TTree *MyTree = new TTree("TrackHit","TrackHit");
#  MyTree->ReadFile("event_data.txt","{a}");
#  MyTree->SaveAs("training_testing.root");
#}}
#""".format(a=thevars)

with open('makeMyTree.C','w') as myfile:
    myfile.write(textforrootscript)


print("Made file makeMyTree.C, run that in root")
    
#print("The root commands are:")
#print("TTree *MyTree = new TTree(\"TrackHit\",\"TrackHit\");")
#print("MyTree->ReadFile(\"event_data.txt\" ,\"",thevars,"\");")
#print("MyTree->SaveAs(\"training_testing.root\");")



