CC = gcc
OBJS = MiniMaxAlgorithm.o Game.o XMLParser.o ArrayList.o Parser.o ConsoleMode.o Common.o Widget.o BasicButton.o BasicWindow.o BasicLabel.o MainWindow.o LoadWindow.o SettingWindow.o GameWindow.o GuiManager.o GuiMode.o main.o
EXEC = chessprog
GAME_TEST_OBJS = ArrayList.o Game.o GameUnitTest.o
ARRAY_LIST_TEST_OBJS = ArrayListUnitTest.o ArrayList.o
PARSER_TEST_OBJS = Parser.o ParserUnitTest.o
XML_PARSER_TEST_OBJ = ArrayList.o Game.o XMLParser.o XMLParserUnitTest.o 
CONSOLE_MODE_TEST_OBJ = ArrayList.o Parser.o Game.o XMLParser.o ConsoleMode.o ConsoleUnitTest.o MiniMaxAlgorithm.o
MINMAX_TEST_OBJ = MiniMaxAlgorithm.o MiniMaxUnitTest.o Game.o ArrayList.o
GUI_MODE_OBJ = Common.o Widget.o BasicButton.o BasicWindow.o BasicLabel.o  MainWindow.o LoadWindow.o SettingWindow.o GameWindow.o GuiManager.o GuiMode.o GuiModeUnitTest.o XMLParser.o Game.o ArrayList.o MiniMaxAlgorithm.o
COMP_FLAG = -std=c99 -g -Wall -Wextra \
-Werror -pedantic-errors
UNIT_TESTS = GameUnitTest XMLParserUnitTest  ArrayListUnitTest ParserUnitTest MiniMaxUnitTest GuiModeUnitTest
SDL_COMP_FLAG = -I/usr/include/SDL2 -D_REENTRANT
SDL_LIB = -L/usr/lib/x86_64-linux-gnu -Wl,-rpath,/usr/lib/x86_64-linux-gnu -Wl,--enable-new-dtags -lSDL2 -lSDL2main -lm
#SDL_COMP_FLAG = -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
#SDL_LIB = -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main -lm

all: $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o chessprog
$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(SDL_LIB) -o $@
GameUnitTest: $(GAME_TEST_OBJS)
	$(CC) $(GAME_TEST_OBJS) -o $@
ArrayListUnitTest: $(ARRAY_LIST_TEST_OBJS)
	$(CC) $(ARRAY_LIST_TEST_OBJS) -o $@
ParserUnitTest: $(PARSER_TEST_OBJS)
	$(CC) $(PARSER_TEST_OBJS) -o $@
MiniMaxUnitTest: $(MINMAX_TEST_OBJ)
	$(CC) $(MINMAX_TEST_OBJ) -o $@
XMLParserUnitTest: $(XML_PARSER_TEST_OBJ)
	$(CC) $(XML_PARSER_TEST_OBJ) -o $@
ConsoleUnitTest: $(CONSOLE_MODE_TEST_OBJ)
	$(CC) $(CONSOLE_MODE_TEST_OBJ) -o $@
GuiModeUnitTest: $(GUI_MODE_OBJ)
	$(CC) $(GUI_MODE_OBJ) $(SDL_LIB) -o $@
GameUnitTest.o: GameUnitTest.c unit_test_util.h ArrayList.h Game.h
	$(CC) $(COMP_FLAG) -c $*.c
ArrayListUnitTest.o: ArrayListUnitTest.c ArrayList.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
ParserUnitTest.o: ParserUnitTest.c Parser.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
MiniMaxUnitTest.o: MiniMaxUnitTest.c MiniMaxAlgorithm.h Game.h unit_test_util.h
	$(CC) $(COMP_FLAG) -c $*.c
ArrayList.o: ArrayList.h ArrayList.c
	$(CC) $(COMP_FLAG) -c $*.c
XMLParserUnitTest.o: XMLParserUnitTest.c unit_test_util.h Game.h ArrayList.h XMLParser.h 
	$(CC) $(COMP_FLAG) -c $*.c
ConsoleUnitTest.o: ConsoleUnitTest.c unit_test_util.h Parser.h Game.h ArrayList.h XMLParser.h ConsoleMode.h
	$(CC) $(COMP_FLAG) -c $*.c
GuiModeUnitTest.o: GuiModeUnitTest.c Common.o Widget.h BasicButton.h BasicWindow.h BasicLabel.h GuiManager.h unit_test_util.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Game.o: Game.c Game.h ArrayList.h
	$(CC) $(COMP_FLAG) -c $*.c
XMLParser.o: XMLParser.c XMLParser.h Game.h ArrayList.h
	$(CC) $(COMP_FLAG) -c $*.c
ConsoleMode.o: ConsoleMode.c ConsoleMode.h ArrayList.h Parser.h Game.h XMLParser.h MiniMaxAlgorithm.h
	$(CC) $(COMP_FLAG) -c $*.c
Parser.o: Parser.c Parser.h
	$(CC) $(COMP_FLAG) -c $*.c
MiniMaxAlgorithm.o: MiniMaxAlgorithm.c MiniMaxAlgorithm.h Game.h
	$(CC) $(COMP_FLAG) -c $*.c
Widget.o: Widget.c Widget.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
Common.o: Common.c Common.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
BasicButton.o: BasicButton.c BasicButton.h Widget.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
BasicWindow.o: BasicWindow.c BasicWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
BasicLabel.o: BasicLabel.c BasicLabel.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
MainWindow.o: MainWindow.c MainWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
LoadWindow.o: LoadWindow.c LoadWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
SettingWindow.o: SettingWindow.c SettingWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GameWindow.o: GameWindow.c GameWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GuiManager.o: GuiManager.c GuiManager.h MainWindow.h LoadWindow.h SettingWindow.h GameWindow.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
GuiMode.o: GuiMode.c GuiMode.h GuiManager.h
	$(CC) $(COMP_FLAG) $(SDL_COMP_FLAG) -c $*.c
main.o: main.c ConsoleMode.h Game.h MiniMaxAlgorithm.h
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)
