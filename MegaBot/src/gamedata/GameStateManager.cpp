#include "GameStateManager.h"
#include <BWAPI.h>
#include "GameState.h"
#include "../data/Configuration.h"
#include "../utils/Logging.h"

GameStateManager* GameStateManager::instance = NULL;

GameStateManager::GameStateManager(void) : frequency(500) {
	//TODO write files with increasing number, just like logging
	stateDumpFile = Configuration::OUTPUT_DIR + 
		"states_MegaBot-vs-" + 
		BWAPI::Broodwar->enemy()->getName();

}


GameStateManager::~GameStateManager(void) {

}

GameStateManager* GameStateManager::getInstance(){
	if (instance == NULL) {
		instance = new GameStateManager();
	}
	return instance;
}

void GameStateManager::onFrame(){
	
	//updates spottedEnemies with currently seen enemies:
	map<int, SpottedObject>& spottedEnemies = GameState::getSpottedEnemyUnits();
	//adds all enemy units as spotted objects
	set<BWAPI::Unit*> enemyUnits = BWAPI::Broodwar->enemy()->getUnits();
	set<BWAPI::Unit*>::iterator uit;
	
	for(uit = enemyUnits.begin(); uit != enemyUnits.end(); uit++){
		//updates only if I can see unit or CompleteMapInformation is enabled
		if((*uit)->isVisible() || BWAPI::Broodwar->isFlagEnabled(BWAPI::Flag::CompleteMapInformation)){
			//code below works even if SpottedObject is not present at the map (a default one is created then updated)
			spottedEnemies[(*uit)->getID()].update(*uit); 
		}
	}
	
	//draws information of observed units

	//Logging::getInstance()->log("[%d] I spotted %d enemies", BWAPI::Broodwar->getFrameCount(), spottedEnemies.size());

	//for (auto enemyUnit : spottedEnemies) {
	map<int, SpottedObject>::iterator it; 
	for(it = spottedEnemies.begin(); it != spottedEnemies.end(); it++){
		SpottedObject& enemyUnit = (*it).second;
		enemyUnit.draw();
		//enemyUnit.second.draw();
	}
	
	//only record game state on the required frequency, skips 1st frame as well
	int thisFrame = BWAPI::Broodwar->getFrameCount();
	
	if(thisFrame % frequency == 0 && thisFrame != 0){
		recordState();
	}	
}

void GameStateManager::recordState(){
	int thisFrame = BWAPI::Broodwar->getFrameCount();

	if ( gameStates.find(thisFrame) != gameStates.end() ){
		//already stored this game state, will skip
		Logging::getInstance()->log(
			"Already recorded state at frame %d. Skipping...", thisFrame
		);
		return;
	}
	
	Logging::getInstance()->log("Recording game state.");
	gameStates.insert(make_pair(thisFrame, GameState()));
	
}
