#pragma once
#include <rack.hpp>

using namespace rack;


enum NoteEnum {
	NOTE_C,
	NOTE_C_SHARP,
	NOTE_D,
	NOTE_D_SHARP,
	NOTE_E,
	NOTE_F,
	NOTE_F_SHARP,
	NOTE_G,
	NOTE_G_SHARP,
	NOTE_A,
	NOTE_A_SHARP,
	NOTE_B,
	NUM_NOTES
};

std::string noteName(int note);

int noteValue(std::string name);

struct NoteParamQuantity : ParamQuantity {
	std::string getDisplayValueString();
	void setDisplayValueString(std::string s);
};
