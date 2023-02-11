#pragma once
#include <rack.hpp>

using namespace rack;


enum ScaleEnum {
	AEOLIAN,
	BLUES,
	CHROMATIC,
	DIATONIC_MINOR,
	DORIAN,
	HARMONIC_MINOR,
	INDIAN,
	LOCRIAN,
	LYDIAN,
	MAJOR,
	MELODIC_MINOR,
	MINOR,
	MIXOLYDIAN,
	NATURAL_MINOR,
	PENTATONIC,
	PHRYGIAN,
	TURKISH,
	NONE,
	NUM_SCALES
};

float closestVoltageInScale(float voltsIn, int rootNote, int currScale);

std::string scaleName(int scale);

int scaleValue(std::string name);

struct ScaleParamQuantity : ParamQuantity {
	std::string getDisplayValueString();
	void setDisplayValueString(std::string s);
};
