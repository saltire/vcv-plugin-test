#include "note.hpp"


std::string noteName(int note) {
	switch(note){
		case NOTE_C:       return "C";
		case NOTE_C_SHARP: return "C#";
		case NOTE_D:       return "D";
		case NOTE_D_SHARP: return "D#";
		case NOTE_E:       return "E";
		case NOTE_F:       return "F";
		case NOTE_F_SHARP: return "F#";
		case NOTE_G:       return "G";
		case NOTE_G_SHARP: return "G#";
		case NOTE_A:       return "A";
		case NOTE_A_SHARP: return "A#";
		case NOTE_B:       return "B";
		default: return "";
	}
}

int noteValue(std::string name) {
	if (name == "C")  return NOTE_C;
	if (name == "C#") return NOTE_C_SHARP;
	if (name == "D")  return NOTE_D;
	if (name == "D#") return NOTE_D_SHARP;
	if (name == "E")  return NOTE_E;
	if (name == "F")  return NOTE_F;
	if (name == "F#") return NOTE_F_SHARP;
	if (name == "G")  return NOTE_G;
	if (name == "G#") return NOTE_G_SHARP;
	if (name == "A")  return NOTE_A;
	if (name == "A#") return NOTE_A_SHARP;
	if (name == "B")  return NOTE_B;
	return -1;
}

std::string NoteParamQuantity::getDisplayValueString() {
	return noteName(int(getDisplayValue()));
}

void NoteParamQuantity::setDisplayValueString(std::string s) {
	int v = noteValue(string::uppercase(s));
	if (v == -1) return;
	setDisplayValue(v);
}
