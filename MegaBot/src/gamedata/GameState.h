#pragma once
#include <string>
#include <BWAPI.h>
#include <vector>
#include "SpottedObject.h"

using namespace std;
//using namespace BWAPI;

/** Stores relevant information of a game state */
class GameState {
	
	//static BWAPI::Player* enemy;
	//static string mapName;

	/** name of current strategy */
	//string currentStrategyName;

	/** current frame */
	int frame;

	/** Enemy 'units' even in fog of war */
	static map<int, SpottedObject> persistentEnemyObjects;

	/** Enemy 'units' within visual range */
	map<int, SpottedObject> currentEnemyObjects;

	/** My 'units' */
	map<int, SpottedObject> currentMyObjects;

	//resources
	int currentMinerals, currentGas;

	//supply
	int supplyUsed, supplyAvailable;

	//my score data
	int myUnitScore, myKillScore, 
		myBuildingScore, myRazingScore, 
		myGatheredMinerals, myGatheredGas, myTotalScore;

	// enemy score data
	/*int enemyUnitScore, enemyKillScore, 
		enemyBuildingScore, enemyRazingScore, 
		enemyGatheredMinerals, enemyGatheredGas, enemyTotalScore;*/


public:
	GameState(void);
	~GameState(void);

	/** Returns a map unitID -> SpottedObject with observed enemy units */
	static map<int, SpottedObject>& getSpottedEnemyUnits();

	/** Removes unit from persistentEnemyObjects */
	static void unitDestroyed(BWAPI::Unit* unit);
};

