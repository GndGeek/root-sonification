from mido import MidiFile, MidiTrack, Message
import ROOT, math, argparse

parser = argparse.ArgumentParser(description="Convert a ROOT file containing a histogram into a MIDI file containing its sonification.")
parser.add_argument("input", help="Name of ROOT file to read in.")
parser.add_argument("output", help="Name of MIDI file to generate.")
parser.add_argument("--duration", help="Duration of each note.", type=int, default=128)
args = parser.parse_args()

kNoteDuration = args.duration

ROOT.gROOT.LoadMacro("sound/sound.cpp")

def extract_data(filename, branchname):
	# Takes the name of a ROOT file and branch within that file.
	# Constructs a histogram and returns (values, bin_min, bin_max, bin_width).
	# Probably works by calling to a C++ ROOT macro.
	data = ROOT.volume(filename, branchname)
	return data


def data_to_sound(values, bin_min, bin_max, bin_width):
	# Takes a list containing the number of events in each bin, ordered from lowest to highest. Also takes the bottom of the lowest bin, top of the highest bin, and width of each bin.
	# Returns a list of MIDI Messages.
	values_max = max(values)
	values_min = min(values)
	
	print values_min, values_max
	
	messages = [Message('program_change', program=12)]
	
	for value in values:
		print value
		note = int(value * 63 / values_max + 32)
		print note
		messages.append(Message('note_on', note=note, time=0))
		messages.append(Message('note_off', note=note, time=kNoteDuration))
	
# 	i = 30
# 	for value in values:
# 		i += 1
# 		note = int(value * 63 / values_max + 32)
# 		messages.append(Message('note_on', note = i, time=0, velocity = note))
# 	
# 	messages.append(Message('note_off', note = 30, time=kNoteDuration))
# 	i = 31
# 	for value in values:
# 		i += 1
# 		messages.append(Message('note_off', note = i, time=0))
	
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
	d = extract_data(args.input, "h1")
	s = data_to_sound(d, 0, 0, 0)
	output_messages(args.output, s)