#include "plugin.hpp"
#include "utils/note.hpp"
#include "utils/scale.hpp"


// copied from https://github.com/jeremywen/JW-Modules - Quantizer

struct Quantize : Module {
	enum ParamId {
		NOTE_PARAM,
		SCALE_PARAM,
		OCTAVE_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		NOTE_IN_INPUT,
		SCALE_IN_INPUT,
		OCTAVE_IN_INPUT,
		CV_IN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		CV_OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Quantize() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam<NoteParamQuantity>(NOTE_PARAM, 0, NUM_NOTES - 1, NOTE_C, "Root Note");
		configParam<ScaleParamQuantity>(SCALE_PARAM, 0, NUM_SCALES - 1, MINOR, "Scale");
		configParam(OCTAVE_PARAM, -5, 5, 0, "Octave Shift");
		configInput(NOTE_IN_INPUT, "Note");
		configInput(SCALE_IN_INPUT, "Scale");
		configInput(OCTAVE_IN_INPUT, "Octave");
		configInput(CV_IN_INPUT, "CV");
		configOutput(CV_OUT_OUTPUT, "Quantized");
		configBypass(CV_IN_INPUT, CV_OUT_OUTPUT);
	}

	void process(const ProcessArgs& args) override {
		int rootNote = params[NOTE_PARAM].getValue()
			+ rescale(inputs[NOTE_IN_INPUT].getVoltage(), 0, 10, 0, NUM_NOTES - 1);
		int scale = params[SCALE_PARAM].getValue()
			+ rescale(inputs[SCALE_IN_INPUT].getVoltage(), 0, 10, 0, NUM_SCALES - 1);
		int octaveShift = params[OCTAVE_PARAM].getValue()
			+ clamp(inputs[OCTAVE_IN_INPUT].getVoltage(), -5.f, 5.f);

		int channels = inputs[CV_IN_INPUT].getChannels();
		for (int c = 0; c < channels; c++) {
			float volts = closestVoltageInScale(inputs[CV_IN_INPUT].getVoltage(c), rootNote, scale);
			outputs[CV_OUT_OUTPUT].setVoltage(volts + octaveShift, c);
		}
		outputs[CV_OUT_OUTPUT].setChannels(channels);
	}
};


struct QuantizeWidget : ModuleWidget {
	QuantizeWidget(Quantize* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/quantize.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(25.4, 30.48)), module, Quantize::NOTE_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(25.4, 60.96)), module, Quantize::SCALE_PARAM));
		addParam(createParamCentered<RoundBlackSnapKnob>(mm2px(Vec(25.4, 91.44)), module, Quantize::OCTAVE_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.4, 40.7)), module, Quantize::NOTE_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.4, 71.12)), module, Quantize::SCALE_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.4, 101.6)), module, Quantize::OCTAVE_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.16, 116.84)), module, Quantize::CV_IN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(40.64, 116.84)), module, Quantize::CV_OUT_OUTPUT));
	}
};


Model* modelQuantize = createModel<Quantize, QuantizeWidget>("quantize");
