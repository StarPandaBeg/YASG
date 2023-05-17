#include "WorldGenerator.h"

#include "CrateGenerationStep.h"
#include "PortalGenerationStep.h"

generators::world::WorldGenerator::~WorldGenerator()
{
	for (auto step : _steps) {
		delete step;
	}
}

void generators::world::WorldGenerator::add(IGenerationStep* step)
{
	_steps.push_back(step);
}

void generators::world::WorldGenerator::run(grid::Grid* grid)
{
	for (auto step : _steps) {
		step->setSeed(_seed);
		step->process(grid);
	}
}

void generators::world::WorldGenerator::setSeed(int seed)
{
	_seed = seed;
}

generators::world::WorldGenerator* generators::world::WorldGenerator::fromConfig(GameConfig cfg)
{
	auto generator = new generators::world::WorldGenerator();
	if (cfg.allowWoodCrates())
		generator->add(new CrateGenerationStep(cfg.getWoodCrateAmount(), true));
	if (cfg.allowIronCrates())
		generator->add(new CrateGenerationStep(cfg.getIronCrateAmount(), false));
	if (cfg.allowPortals()) {
		generator->add(new PortalGenerationStep());
	}
	generator->setSeed(cfg.getSeed());
	return generator;
}
