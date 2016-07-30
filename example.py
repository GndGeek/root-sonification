import ROOT
tb = ROOT.TBrowser()
f = ROOT.TFile("/afs/cern.ch/user/y/yijiang/SA_test_ttH_ttHemjets10.root")
t = f.Get("METree")
for event in t:
 n1= event.ME_Sig_Max_Likelihoods

import mido
from mido import Message, MidiFile, MidiTrack

with MidiFile() as mid:
 track = MidiTrack()
 mid.tracks.append(track)
 track.append(mido.Message('program_change', program=12, time=0))
 for val in n1 :
  track.append(mido.Message('note_on', note=int(val), velocity=64, time=100))
  track.append(mido.Message('note_off', note=int(val), velocity=127, time=100))
 mid.save('/afs/cern.ch/user/y/yijiang/new_song.mid')