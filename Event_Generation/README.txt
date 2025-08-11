This is data generation script.

We give the number of events, the number of tracks, the number of high and low pT tracks and the amount
of smearing for the hits. The output is a text file (called event_data.txt at the moment).

Mostly every variable has an intuitive meaning. Function of every code block has been defined in the script.

Run root, and then run the script
>root -l
[].x event_data_corr.C(NTracksPerEvent,NumHiPtTracks,TotalEvents,OpFileName)

This produces event_data.txt

(Now move to the Image_Generation folder)
