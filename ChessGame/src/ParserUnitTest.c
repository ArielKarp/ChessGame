#include "unit_test_util.h"
#include "Parser.h"

static bool ParserCheckIsInt() {
	ASSERT_TRUE(ParserIsValidInt("1"));
	ASSERT_TRUE(ParserIsValidInt("4"));
	ASSERT_TRUE(ParserIsValidInt("7"));
	return true;
}
static bool ParserCheckParseLine() {
	Command cmd;
	cmd = ParserPraseLine("move <2,A> to <3,C>");
	ASSERT_TRUE(cmd.cmd == USER_MOVE && (cmd.lineStatus == VALID) && (cmd.xSource == 2) && (cmd.ySource == 'A') && (cmd.iDest == 3) && (cmd.jDest == 'C'));
	cmd = ParserPraseLine("move     <2,A> to <3,C>");
	ASSERT_TRUE(cmd.cmd == USER_MOVE && (cmd.lineStatus == VALID) && (cmd.xSource == 2) && (cmd.ySource == 'A') && (cmd.iDest == 3) && (cmd.jDest == 'C'));
	cmd = ParserPraseLine("move <2,A>      to <3,C>");
	ASSERT_TRUE(cmd.cmd == USER_MOVE && (cmd.lineStatus == VALID) && (cmd.xSource == 2) && (cmd.ySource == 'A') && (cmd.iDest == 3) && (cmd.jDest == 'C'));
	cmd = ParserPraseLine("move <2,A> to <3,C>    ");
	ASSERT_TRUE(cmd.cmd == USER_MOVE && (cmd.lineStatus == VALID) && (cmd.xSource == 2) && (cmd.ySource == 'A') && (cmd.iDest == 3) && (cmd.jDest == 'C'));
	cmd = ParserPraseLine("move <2,A> to <3,C>    ");
	ASSERT_TRUE(cmd.cmd == USER_MOVE && (cmd.lineStatus == VALID) && (cmd.xSource == 2) && (cmd.ySource == 'A') && (cmd.iDest == 3) && (cmd.jDest == 'C'));
	cmd = ParserPraseLine("     move <2,A> to <3,C>");
	ASSERT_TRUE(cmd.cmd == USER_MOVE && (cmd.lineStatus == VALID) && (cmd.xSource == 2) && (cmd.ySource == 'A') && (cmd.iDest == 3) && (cmd.jDest == 'C'));
	cmd = ParserPraseLine("move <22,A> to <3,C>");
	ASSERT_TRUE(cmd.cmd == USER_MOVE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("move <2,A> to <3,CDS>");
	ASSERT_TRUE(cmd.cmd == USER_MOVE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("move <2,a> to <3,C>");
	ASSERT_TRUE(cmd.cmd == USER_MOVE && (cmd.lineStatus == INVALID));

	cmd = ParserPraseLine("43");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("fadfds");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("aDddasdsa 432 312");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("432 312");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine(" ");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("move");
	ASSERT_TRUE(cmd.cmd == USER_MOVE && (cmd.lineStatus == INVALID));


	cmd = ParserPraseLine("quit");
	ASSERT_TRUE(cmd.cmd == QUIT && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("quitd");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("quit sfddsf");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("quit   ");
	ASSERT_TRUE(cmd.cmd == QUIT && (cmd.lineStatus == INVALID));

//	cmd = ParserPraseLine("save");
//	ASSERT_TRUE(cmd.cmd == USER_SAVE && (cmd.lineStatus == INVALID));
//	cmd = ParserPraseLine("save   ");
//	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));


	cmd = ParserPraseLine("undo");
	ASSERT_TRUE(cmd.cmd == USER_UNDO && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("undo sfddsf");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("undod");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("undo   ");
	ASSERT_TRUE(cmd.cmd == USER_UNDO && (cmd.lineStatus == INVALID));

	cmd = ParserPraseLine("reset");
	ASSERT_TRUE(cmd.cmd == USER_RESET && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("resetd");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("reset   ");
	ASSERT_TRUE(cmd.cmd == USER_RESET && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("reset dffd");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));

	cmd = ParserPraseLine("game_mode 1");
	ASSERT_TRUE(cmd.cmd == SETTINGS_GAME_MODE && (cmd.lineStatus == VALID) && (cmd.gameMode == 1));
	cmd = ParserPraseLine("game_mode 2");
	ASSERT_TRUE(cmd.cmd == SETTINGS_GAME_MODE && (cmd.lineStatus == VALID) && (cmd.gameMode == 2));
	cmd = ParserPraseLine("game_mode 3");
	ASSERT_TRUE(cmd.cmd == SETTINGS_GAME_MODE && (cmd.lineStatus == INVALID) && (cmd.gameMode == 0));
	cmd = ParserPraseLine("game_mode 0");
	ASSERT_TRUE(cmd.cmd == SETTINGS_GAME_MODE && (cmd.lineStatus == INVALID) && (cmd.gameMode == 0));
	cmd = ParserPraseLine("game_mode GSAD");
	ASSERT_TRUE(cmd.cmd == SETTINGS_GAME_MODE && (cmd.lineStatus == INVALID) && (cmd.gameMode == 0));

	cmd = ParserPraseLine("difficulty 1");
	ASSERT_TRUE(cmd.cmd == SETTINGS_DIFFICULTY && (cmd.lineStatus == VALID) && (cmd.difficulty == 1));
	cmd = ParserPraseLine("difficulty 2");
	ASSERT_TRUE(cmd.cmd == SETTINGS_DIFFICULTY && (cmd.lineStatus == VALID) && (cmd.difficulty == 2));
	cmd = ParserPraseLine("difficulty 4");
	ASSERT_TRUE(cmd.cmd == SETTINGS_DIFFICULTY && (cmd.lineStatus == VALID) && (cmd.difficulty == 4));
	cmd = ParserPraseLine("difficulty 5");
	ASSERT_TRUE(cmd.cmd == SETTINGS_DIFFICULTY && (cmd.lineStatus == EXPERT_NOT_SUPPORTED) && (cmd.gameMode == 0));
	cmd = ParserPraseLine("difficulty 0");
	ASSERT_TRUE(cmd.cmd == SETTINGS_DIFFICULTY && (cmd.lineStatus == INVALID) && (cmd.gameMode == 0));
	cmd = ParserPraseLine("difficulty GSAD");
	ASSERT_TRUE(cmd.cmd == SETTINGS_DIFFICULTY && (cmd.lineStatus == INVALID) && (cmd.gameMode == 0));


	cmd = ParserPraseLine("user_color 1");
	ASSERT_TRUE(cmd.cmd == SETTINGS_USER_COLOR && (cmd.lineStatus == VALID) && (cmd.gameMode == 1));
	cmd = ParserPraseLine("user_color 0");
	ASSERT_TRUE(cmd.cmd == SETTINGS_USER_COLOR && (cmd.lineStatus == VALID) && (cmd.gameMode == 0));
	cmd = ParserPraseLine("user_color 3");
	ASSERT_TRUE(cmd.cmd == SETTINGS_USER_COLOR && (cmd.lineStatus == INVALID) && (cmd.gameMode == 0));
	cmd = ParserPraseLine("user_color -1");
	ASSERT_TRUE(cmd.cmd == SETTINGS_USER_COLOR && (cmd.lineStatus == INVALID) && (cmd.gameMode == 0));
	cmd = ParserPraseLine("user_color GSAD");
	ASSERT_TRUE(cmd.cmd == SETTINGS_USER_COLOR && (cmd.lineStatus == INVALID) && (cmd.gameMode == 0));


//	cmd = ParserPraseLine("load");
//	ASSERT_TRUE(cmd.cmd == SETTINGS_LOAD && (cmd.lineStatus == INVALID));
//	cmd = ParserPraseLine("load   ");
//	ASSERT_TRUE(cmd.cmd == SETTINGS_LOAD && (cmd.lineStatus == INVALID));

	cmd = ParserPraseLine("default");
	ASSERT_TRUE(cmd.cmd == SETTINGS_DEFAULT && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("default sfddsf");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("defaultd");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("default   ");
	ASSERT_TRUE(cmd.cmd == SETTINGS_DEFAULT && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("      default   ");
	ASSERT_TRUE(cmd.cmd == SETTINGS_DEFAULT && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("      default");
	ASSERT_TRUE(cmd.cmd == SETTINGS_DEFAULT && (cmd.lineStatus == INVALID));

	cmd = ParserPraseLine("print_setting");
	ASSERT_TRUE(cmd.cmd == SETTINGS_PRINT_SETTING && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("print_setting sfddsf");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("print_settingd");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("print_setting   ");
	ASSERT_TRUE(cmd.cmd == SETTINGS_PRINT_SETTING && (cmd.lineStatus == INVALID));


	cmd = ParserPraseLine("start");
	ASSERT_TRUE(cmd.cmd == SETTINGS_START && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("start sfddsf");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("startd");
	ASSERT_TRUE(cmd.cmd == INVALID_LINE && (cmd.lineStatus == INVALID));
	cmd = ParserPraseLine("start   ");
	ASSERT_TRUE(cmd.cmd == SETTINGS_START && (cmd.lineStatus == INVALID));



	return true;


}
int main() {
	RUN_TEST(ParserCheckIsInt);
	RUN_TEST(ParserCheckParseLine);
	return 0;
}
