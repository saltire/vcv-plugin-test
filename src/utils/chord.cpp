#include "chord.hpp"


int CHORD_MAJOR      [3] = { 0, 4, 7 };
int CHORD_MINOR      [3] = { 0, 3, 7 };
int CHORD_DIMINISHED [3] = { 0, 3, 6 };
int CHORD_AUGMENTED  [3] = { 0, 4, 8 };
int CHORD_MAJOR_7    [4] = { 0, 4, 7, 11 };
int CHORD_MINOR_7    [4] = { 0, 3, 7, 10 };
int CHORD_DOMINANT_7 [4] = { 0, 4, 7, 10 };

// long printIter = 0;

float shiftChordNote(float voltsIn, int chord, int steps) {
	int octave = (int)floorf(voltsIn);
	int note = (int)roundf((voltsIn - octave) * 12);

	// if (printIter % 100000 == 0) {
	// 	DEBUG("voltsIn:%f, scale:%i, steps:%i, octave:%i, note:%i",
	// 		voltsIn, chord, steps, octave, note);
	// 	printIter = 0;
	// }
	// printIter += 1;

	int *notes;
	int noteCount = 0;
	switch(chord) {
		case MAJOR:      notes = CHORD_MAJOR;      noteCount = LENGTHOF(CHORD_MAJOR);      break;
		case MINOR:      notes = CHORD_MINOR;      noteCount = LENGTHOF(CHORD_MINOR);      break;
		case DIMINISHED: notes = CHORD_DIMINISHED; noteCount = LENGTHOF(CHORD_DIMINISHED); break;
		case AUGMENTED:  notes = CHORD_AUGMENTED;  noteCount = LENGTHOF(CHORD_AUGMENTED);  break;
		case MAJOR_7:    notes = CHORD_MAJOR_7;    noteCount = LENGTHOF(CHORD_MAJOR_7);    break;
		case MINOR_7:    notes = CHORD_MINOR_7;    noteCount = LENGTHOF(CHORD_MINOR_7);    break;
		case DOMINANT_7: notes = CHORD_DOMINANT_7; noteCount = LENGTHOF(CHORD_DOMINANT_7); break;
		case NONE:       return voltsIn;
	}

	int shiftOctaves = eucDiv(steps, noteCount);
	int shiftNotes = eucMod(steps, noteCount);

	return octave + shiftOctaves + (note + notes[shiftNotes]) / 12.f;
}

std::string chordName(int chord) {
	switch(chord){
		case MAJOR:      return "Major";
		case MINOR:      return "Minor";
		case DIMINISHED: return "Diminished";
		case AUGMENTED:  return "Augmented";
		case MAJOR_7:    return "Major 7th";
		case MINOR_7:    return "Minor 7th";
		case DOMINANT_7: return "Dominant 7th";
		case NONE:       return "None";
		default:         return "";
	}
}

int chordValue(std::string name) {
	if (name == "major")        return MAJOR;
	if (name == "minor")        return MINOR;
	if (name == "diminished")   return DIMINISHED;
	if (name == "augmented")    return AUGMENTED;
	if (name == "major 7th")    return MAJOR_7;
	if (name == "minor 7th")    return MINOR_7;
	if (name == "dominant 7th") return DOMINANT_7;
	if (name == "none")         return NONE;
	return -1;
}

std::string ChordParamQuantity::getDisplayValueString() {
	return chordName(int(getDisplayValue()));
}

void ChordParamQuantity::setDisplayValueString(std::string s) {
	int v = chordValue(string::lowercase(s));
	if (v == -1) return;
	setDisplayValue(v);
}
