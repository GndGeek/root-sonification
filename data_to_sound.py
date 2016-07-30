from mido import MidiFile, MidiTrack, Message
import ROOT

kNoteDuration = 64

def extract_data(filename, branchname):
	# Takes the name of a ROOT file and branch within that file.
	# Constructs a histogram and returns (values, bin_min, bin_max, bin_width).
	# Probably works by calling to a C++ ROOT macro.
	pass

def data_to_sound(values, bin_min, bin_max, bin_width):
	# Takes a list containing the number of events in each bin, ordered from lowest to highest. Also takes the bottom of the lowest bin, top of the highest bin, and width of each bin.
	# Returns a list of MIDI Messages.
	values_max = max(values)
	values_min = min(values)
	
	messages = []
	
	for value in values:
		note = int(value * 127 / values_max)
		messages.append(Message('note_on', note=note, time=kNoteDuration))
		messages.append(Message('note_off', note=note, time=kNoteDuration))

def output_messages(filename, messages):
	# Takes the name of a MIDI file to create and fill with the list of messages.
	# Returns nothing.
	with MidiFile() as outfile:
		track = MidiTrack()
		outfile.tracks.append(track)

		track.append(Message('program_change', program=12))
		
		for message in messages:
			track.append(message)
	outfile.save(filename)