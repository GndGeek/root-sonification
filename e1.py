from mido import MidiFile, MidiTrack, Message
import ROOT, math

kNoteDuration = 640

ROOT.gROOT.LoadMacro("sound/sound.cpp")

def extract_data(filename, branchname):
	# Takes the name of a ROOT file and branch within that file.
	# Constructs a histogram and returns (values, bin_min, bin_max, bin_width).
	# Probably works by calling to a C++ ROOT macro.
	data = ROOT.generate_data()
	data_out = []
	i = 0
	for vec in data:
		if i == 0:
			for event in vec: data_out.append(event)
		i += 1
	return (data_out, 0, 0, 0)


def data_to_sound(values,values1, bin_min, bin_max, bin_width, n):
	# Takes a list containing the number of events in each bin, ordered from lowest to highest. Also takes the bottom of the lowest bin, top of the highest bin, and width of each bin.
	# Returns a list of MIDI Messages.
	values_max = max(values)
	values_min = min(values)
	values1_max = max(values1)
	values1_min = min(values1)
	print values_min, values_max, values1_max, values_min
	
	messages = [Message('program_change', program=1)]
	#messages1 = [Message('program_change', program=100)]
# 	for value in values:
# 		print value
# 		note = int(value * 63 / values_max + 32)
# 		print note
# 		messages.append(Message('note_on', note=note, time=kNoteDuration))
# 		messages.append(Message('note_off', note=note, time=kNoteDuration))
	
	i = 30
 
 if n == 2: #multiple histogram
     
	for v1,v2 in zip(values, values1):
		i += 1
		note = int(v1 * 63 / values_max + 32)
          note1 = int(v2 * 63 / values1_max + 32)
		messages.append(Message('note_on', note = i, time=0, velocity = note))
          messages.append(Message('note_on', note = i, time=0, velocity = note1))
	
	messages.append(Message('note_off', note = 30, time=kNoteDuration))
	i = 31
	for val1 in values:
		i += 1
		messages.append(Message('note_off', note = i, time=0))
     
     messages.append(Message('note_off', note1 = 30, time=kNoteDuration))
	i = 31
	for val2 in values1:
		i += 1
		messages.append(Message('note_off', note1 = i, time=0))
  return messages
	
	
 else :
     for value in values:
		i += 1
		note = int(value * 63 / values_max + 32)
		messages.append(Message('note_on', note = i, time=0, velocity = note))
	
	messages.append(Message('note_off', note = 30, time=kNoteDuration))
	i = 31
	for value in values:
		i += 1
		messages.append(Message('note_off', note = i, time=0))
  return messages


def output_messages(filename, messages):
	# Takes the name of a MIDI file to create and fill with the list of messages.
	# Returns nothing.
	with MidiFile() as outfile:
		track = MidiTrack()
		outfile.tracks.append(track)

		for message in messages:
			track.append(message)
	outfile.save(filename)

if __name__ == '__main__':
	d = extract_data("SA_test_ttH_ttHemjets10.root", "")
	s = data_to_sound(*d)
	output_messages('test.mid', s)