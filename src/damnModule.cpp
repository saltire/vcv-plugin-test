#include "plugin.hpp"


struct DamnModule : Module {
	enum ParamId {
		KNOBBIE_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		INNIE_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUTTIE_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		BLINKIE_LIGHT,
		LIGHTS_LEN
	};

	DamnModule() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(KNOBBIE_PARAM, 0.f, 1.f, 0.f, "");
		configInput(INNIE_INPUT, "");
		configOutput(OUTTIE_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
	}
};


struct DamnModuleWidget : ModuleWidget {
	DamnModuleWidget(DamnModule* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/damnModule.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(25.4, 39.713)), module, DamnModule::KNOBBIE_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(25.4, 80.0)), module, DamnModule::INNIE_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(25.4, 100.0)), module, DamnModule::OUTTIE_OUTPUT));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(25.4, 59.98)), module, DamnModule::BLINKIE_LIGHT));
	}
};


Model* modelDamnModule = createModel<DamnModule, DamnModuleWidget>("damnModule");