#include "plugin.hpp"
#include "utils/note.hpp"
#include "utils/chord.hpp"


int currentStep = 0;

struct Arpsichord : Module {
	enum ParamId {
		STEPS_PARAM,
		OFFSET_PARAM,
		SCALE_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		NOTE_INPUT,
		CLK_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		NOTE_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Arpsichord() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(STEPS_PARAM, 1.f, 16.f, 8.f, "Steps");
		configParam(OFFSET_PARAM, -16.f, 16.f, 0.f, "Step offset");
		configParam<ChordParamQuantity>(SCALE_PARAM, 0, NUM_CHORDS - 1, MINOR, "Chord");
		configInput(NOTE_INPUT, "1V/octave pitch");
		configInput(CLK_INPUT, "Clock");
		configOutput(NOTE_OUTPUT, "1V/octave pitch");
		configBypass(NOTE_INPUT, NOTE_OUTPUT);
	}

	dsp::SchmittTrigger clkTrigger;

	void process(const ProcessArgs& args) override {
		int steps = getParam(STEPS_PARAM).getValue();
		int offset = getParam(OFFSET_PARAM).getValue();
		int scale = getParam(SCALE_PARAM).getValue();

		if (clkTrigger.process(getInput(CLK_INPUT).getVoltage(), .1f, 2.f)) {
			currentStep += 1;
		}
		currentStep %= steps * 2;

		int shiftSteps = (currentStep < steps ? currentStep : (steps * 2 - currentStep)) + offset;

		int channels = getInput(NOTE_INPUT).getChannels();
		getOutput(NOTE_OUTPUT).setChannels(channels);
		for (int c = 0; c < channels; c++) {
			float inputNote = getInput(NOTE_INPUT).getVoltage(c);
			float outputNote = shiftChordNote(inputNote, scale, shiftSteps);
			getOutput(NOTE_OUTPUT).setVoltage(outputNote, c);
		}
	}
};


struct ArpsichordWidget : ModuleWidget {
	ArpsichordWidget(Arpsichord* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/arpsichord.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(15.24, 55.88)), module,
			Arpsichord::STEPS_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(35.56, 55.88)), module,
			Arpsichord::OFFSET_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(25.4, 76.2)), module,
			Arpsichord::SCALE_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.18, 30.48)), module,
			Arpsichord::NOTE_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(35.56, 30.48)), module,
			Arpsichord::CLK_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(25.4, 106.68)), module,
			Arpsichord::NOTE_OUTPUT));
	}
};


Model* modelArpsichord = createModel<Arpsichord, ArpsichordWidget>("arpsichord");
