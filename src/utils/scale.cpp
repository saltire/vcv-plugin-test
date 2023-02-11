#include "scale.hpp"


// copied & fixed these scales http://www.grantmuller.com/MidiReference/doc/midiReference/ScaleReference.html
// more scales http://lawriecape.co.uk/theblog/index.php/archives/881
int SCALE_AEOLIAN        [8] = {0, 2, 3, 5, 7, 8, 10, 12};
int SCALE_BLUES          [7] = {0, 3, 5, 6, 7, 10, 12}; //FIXED!
int SCALE_CHROMATIC      [13]= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int SCALE_DIATONIC_MINOR [8] = {0, 2, 3, 5, 7, 8, 10, 12};
int SCALE_DORIAN         [8] = {0, 2, 3, 5, 7, 9, 10, 12};
int SCALE_HARMONIC_MINOR [8] = {0, 2, 3, 5, 7, 8, 11, 12};
int SCALE_INDIAN         [8] = {0, 1, 1, 4, 5, 8, 10, 12};
int SCALE_LOCRIAN        [8] = {0, 1, 3, 5, 6, 8, 10, 12};
int SCALE_LYDIAN         [8] = {0, 2, 4, 6, 7, 9, 11, 12};
int SCALE_MAJOR          [8] = {0, 2, 4, 5, 7, 9, 11, 12};
int SCALE_MELODIC_MINOR  [10] = {0, 2, 3, 5, 7, 8, 9, 10, 11, 12};
int SCALE_MINOR          [8] = {0, 2, 3, 5, 7, 8, 10, 12};
int SCALE_MIXOLYDIAN     [8] = {0, 2, 4, 5, 7, 9, 10, 12};
int SCALE_NATURAL_MINOR  [8] = {0, 2, 3, 5, 7, 8, 10, 12};
int SCALE_PENTATONIC     [6] = {0, 2, 4, 7, 9, 12};
int SCALE_PHRYGIAN       [8] = {0, 1, 3, 5, 7, 8, 10, 12};
int SCALE_TURKISH        [8] = {0, 1, 3, 5, 7, 10, 11, 12};

// long printIter = 0;
float closestVoltageInScale(float voltsIn, int rootNote, int currScale) {
	int *curScaleArr;
	int notesInScale = 0;
	switch(currScale){
		case AEOLIAN:        curScaleArr = SCALE_AEOLIAN;       notesInScale=LENGTHOF(SCALE_AEOLIAN); break;
		case BLUES:          curScaleArr = SCALE_BLUES;         notesInScale=LENGTHOF(SCALE_BLUES); break;
		case CHROMATIC:      curScaleArr = SCALE_CHROMATIC;     notesInScale=LENGTHOF(SCALE_CHROMATIC); break;
		case DIATONIC_MINOR: curScaleArr = SCALE_DIATONIC_MINOR;notesInScale=LENGTHOF(SCALE_DIATONIC_MINOR); break;
		case DORIAN:         curScaleArr = SCALE_DORIAN;        notesInScale=LENGTHOF(SCALE_DORIAN); break;
		case HARMONIC_MINOR: curScaleArr = SCALE_HARMONIC_MINOR;notesInScale=LENGTHOF(SCALE_HARMONIC_MINOR); break;
		case INDIAN:         curScaleArr = SCALE_INDIAN;        notesInScale=LENGTHOF(SCALE_INDIAN); break;
		case LOCRIAN:        curScaleArr = SCALE_LOCRIAN;       notesInScale=LENGTHOF(SCALE_LOCRIAN); break;
		case LYDIAN:         curScaleArr = SCALE_LYDIAN;        notesInScale=LENGTHOF(SCALE_LYDIAN); break;
		case MAJOR:          curScaleArr = SCALE_MAJOR;         notesInScale=LENGTHOF(SCALE_MAJOR); break;
		case MELODIC_MINOR:  curScaleArr = SCALE_MELODIC_MINOR; notesInScale=LENGTHOF(SCALE_MELODIC_MINOR); break;
		case MINOR:          curScaleArr = SCALE_MINOR;         notesInScale=LENGTHOF(SCALE_MINOR); break;
		case MIXOLYDIAN:     curScaleArr = SCALE_MIXOLYDIAN;    notesInScale=LENGTHOF(SCALE_MIXOLYDIAN); break;
		case NATURAL_MINOR:  curScaleArr = SCALE_NATURAL_MINOR; notesInScale=LENGTHOF(SCALE_NATURAL_MINOR); break;
		case PENTATONIC:     curScaleArr = SCALE_PENTATONIC;    notesInScale=LENGTHOF(SCALE_PENTATONIC); break;
		case PHRYGIAN:       curScaleArr = SCALE_PHRYGIAN;      notesInScale=LENGTHOF(SCALE_PHRYGIAN); break;
		case TURKISH:        curScaleArr = SCALE_TURKISH;       notesInScale=LENGTHOF(SCALE_TURKISH); break;
		case NONE:           return voltsIn;
	}

	//C1 == -2.00, C2 == -1.00, C3 == 0.00, C4 == 1.00
	//B1 == -1.08, B2 == -0.08, B3 == 0.92, B4 == 1.92
	float closestVal = 10.0;
	float closestDist = 10.0;
	float scaleNoteInVolts = 0;
	float distAway = 0;
	int octaveInVolts = int(floorf(voltsIn));
	float voltMinusOct = voltsIn - octaveInVolts;
	for (int i=0; i < notesInScale; i++) {
		scaleNoteInVolts = curScaleArr[i] / 12.0;
		distAway = fabs(voltMinusOct - scaleNoteInVolts);
		if(distAway < closestDist){
			closestVal = scaleNoteInVolts;
			closestDist = distAway;
		}

		// if(printIter%100000==0){
		// 	printf("i:%i, rootNote:%i, voltsIn:%f, octaveInVolts:%i, closestVal:%f, closestDist:%f\n",
		// 	        i,    rootNote,    voltsIn,    octaveInVolts,    closestVal,    closestDist);
		// 	printIter = 0;
		// }
	}
	// printIter++;
	float voltsOut = octaveInVolts + rootNote/12.0 + closestVal;
	// if(printIter%100000==0){
	// 	printf("voltsIn:%f, voltsOut:%f, closestVal:%f\n",
	// 			voltsIn,    voltsOut,    closestVal);
	// 	printIter = 0;
	// }
	return voltsOut;
}

std::string scaleName(int scale) {
	switch(scale){
		case AEOLIAN:        return "Aeolian";
		case BLUES:          return "Blues";
		case CHROMATIC:      return "Chromatic";
		case DIATONIC_MINOR: return "Diatonic Minor";
		case DORIAN:         return "Dorian";
		case HARMONIC_MINOR: return "Harmonic Minor";
		case INDIAN:         return "Indian";
		case LOCRIAN:        return "Locrian";
		case LYDIAN:         return "Lydian";
		case MAJOR:          return "Major";
		case MELODIC_MINOR:  return "Melodic Minor";
		case MINOR:          return "Minor";
		case MIXOLYDIAN:     return "Mixolydian";
		case NATURAL_MINOR:  return "Natural Minor";
		case PENTATONIC:     return "Pentatonic";
		case PHRYGIAN:       return "Phrygian";
		case TURKISH:        return "Turkish";
		case NONE:           return "None";
		default:             return "";
	}
}

int scaleValue(std::string name) {
	if (name == "aeolian")        return AEOLIAN;
	if (name == "blues")          return BLUES;
	if (name == "chromatic")      return CHROMATIC;
	if (name == "diatonic minor") return DIATONIC_MINOR;
	if (name == "dorian")         return DORIAN;
	if (name == "harmonic minor") return HARMONIC_MINOR;
	if (name == "indian")         return INDIAN;
	if (name == "locrian")        return LOCRIAN;
	if (name == "lydian")         return LYDIAN;
	if (name == "major")          return MAJOR;
	if (name == "melodic minor")  return MELODIC_MINOR;
	if (name == "minor")          return MINOR;
	if (name == "mixolydian")     return MIXOLYDIAN;
	if (name == "natural minor")  return NATURAL_MINOR;
	if (name == "pentatonic")     return PENTATONIC;
	if (name == "phrygian")       return PHRYGIAN;
	if (name == "turkish")        return TURKISH;
	if (name == "none")           return NONE;
	return -1;
}

std::string ScaleParamQuantity::getDisplayValueString() {
	return scaleName(int(getDisplayValue()));
}

void ScaleParamQuantity::setDisplayValueString(std::string s) {
	int v = scaleValue(string::lowercase(s));
	if (v == -1) return;
	setDisplayValue(v);
}