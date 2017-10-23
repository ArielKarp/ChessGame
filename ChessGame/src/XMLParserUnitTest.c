/*
 * XMLParserUnitTest.c
 *
 *      Author: Ariel
 */

#include "unit_test_util.h"
#include "XMLParser.h"
#include <stdbool.h>


static bool xmlSaveGame1(){
	// Sanity test of save
	char* path = "../test1";
	Game* game = GameCreate(3);
	ASSERT_TRUE(SaveGameToXMLFile(path, game) == XML_PASS);
	GameDestroy(game);
	return true;
}


static bool loadGameFromTest1() {
	// Sanity for load
	char* path = "../test1";
	Game* game = GameCreate(3);
	ASSERT_TRUE(LoadGameFromXML(path, game) == XML_PASS);
	GameDestroy(game);
	return true;
}

static bool loadGameFromExample() {
	// Load game from example
	char* path = "../example";
	Game* game = GameCreate(3);
	ASSERT_TRUE(LoadGameFromXML(path, game) == XML_PASS);
	GameDestroy(game);
	return true;
}

static bool loadGameFromExampleAndSaveGame() {
	// Load game from example and save afterwards
	char* pathLoad = "../example";
	char* pathSave = "../example_save";
	Game* game = GameCreate(3);
	ASSERT_TRUE(LoadGameFromXML(pathLoad, game) == XML_PASS);
	ASSERT_TRUE(SaveGameToXMLFile(pathSave, game) == XML_PASS);
	GameDestroy(game);
	return true;
}

static bool loadGameFromExamplePlus() {
	// Load game from example
	char* path = "../example2";
	Game* game = GameCreate(3);
	ASSERT_TRUE(LoadGameFromXML(path, game) == XML_PASS);
	ASSERT_TRUE(game->whiteKingLocation[0] == 1);
	ASSERT_TRUE(game->whiteKingLocation[1] == 5);
	ASSERT_TRUE(game->blackKingLocation[0] == 7);
	ASSERT_TRUE(game->blackKingLocation[1] == 5);
	GameDestroy(game);
	return true;
}

int main() {
	RUN_TEST(xmlSaveGame1);
	RUN_TEST(loadGameFromTest1);
	RUN_TEST(loadGameFromExample);
	RUN_TEST(loadGameFromExampleAndSaveGame);
	RUN_TEST(loadGameFromExamplePlus);
}
