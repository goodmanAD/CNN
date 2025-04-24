Every folder name represents its content.
First go through the README files in the folder before going to the scripts.

Order in which one should go through folders :
      Event_Generation -> Image_Generation -> Network


List of commands

Event_generation/
root -q -l -b 'event_data_corr.C(50,1,20000,"event_data_hipt.txt")'
root -q -l -b 'event_data_corr.C(50,0,20000,"event_data_lopt.txt")'

Image_generation/
python generate_command.py
root -q -l -b 'makeMyTree.C("event_data_hipt.txt","tree_hipt.root")'
root -q -l -b 'makeMyTree.C("event_data_lopt.txt","tree_lopt.root")'

root -q -l -b 'plotmaker2.C(800,"tree_hipt.root")'
root -q -l -b 'plotmaker2.C(800,"tree_lopt.root")'



Event_generation_v2
Here we do the same as Event_generation, but the output parameters are going
to be hits (r, phi) (instead of x,y).

Image_generation_v2
Now we want to visualize a usual image but using r, phi this time.
