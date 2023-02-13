#pragma once
#include <rack.hpp>

using namespace rack;


enum ChordEnum {
  MAJOR,
  MINOR,
  DIMINISHED,
  AUGMENTED,
  MAJOR_7,
  MINOR_7,
  DOMINANT_7,
  NONE,
  NUM_CHORDS,
};

float shiftChordNote(float voltsIn, int currScale, int steps);

std::string chordName(int chord);

int chordValue(std::string name);

struct ChordParamQuantity : ParamQuantity {
	std::string getDisplayValueString();
	void setDisplayValueString(std::string s);
};
