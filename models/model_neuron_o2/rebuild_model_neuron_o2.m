function rebuild_model_neuron_o2()
modelName = 'model_neuron_o2';
amimodel.compileAndLinkModel(modelName, '', [], [], [], []);
amimodel.generateMatlabWrapper(10, 5, 4, 2, 5,  , [], ['simulate_' modelName '.m'], 'model_neuron_o2', 'log10', 1, 1);
end
