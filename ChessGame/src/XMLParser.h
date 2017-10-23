#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Parser.h"
#include "MiniMaxAlgorithm.h"


#define ROW_NUMBER 2

typedef enum xml_message_t {
	XML_PATH_FAIL, XML_OPEN_FILE_FAIL, XML_CLOSE_FILE_FAIL, XML_ERROR_WRITE_FAIL, XML_ERROR_READ_FAIL, XML_PASS,
}XML_MESSAGE;

/**
 * Save game to XML output file by convention
 * @param path output path of file
 * @param src input game
 * @return XML_MESSAGE_PASS if succeeded
 * o.w XML_ERROR message
 */
XML_MESSAGE SaveGameToXMLFile(char* path, Game* src);

/**
 * Load from XML input file to Game input object
 * @param path input file path
 * @param src output Game object
 * @return XML_MESSAGE_PATH if succeeded
 * o.w. XML_ERROR message
 */
XML_MESSAGE LoadGameFromXML(char* path, Game* src);

/**
 * Helper function to load data into game
 * @param clearedLine cleared line for pre-defined delimiters
 * @param src input game to be filled
 * @param generalExists flag to be turned on if general does not exists
 */
void FillGameWithData(char* clearedLine, Game* src, int* generalExists);



#endif
