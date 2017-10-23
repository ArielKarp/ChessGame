/*
 * ArrayList.c
 *
 *      Author: Ariel Karpilovski 308552454
 *      		Ron Tabibian 308472596
 *
 */

#include "ArrayList.h"

ArrayList* ArrayListCreate(int maxSize) {
	if (maxSize <= 0) {
		return NULL;
	}
	ArrayList* returnList = (ArrayList*)malloc(sizeof(ArrayList));
	if (NULL == returnList) {
		return NULL;
	}
	returnList->maxSize = maxSize;
	returnList->actualSize = 0;
	returnList->elements = (DataMember*) calloc(maxSize, sizeof(DataMember));
	// If allocation fails, free memory and return NULL
	if (NULL == returnList->elements) {
		free(returnList);
		returnList = NULL;
		return NULL;
	}
	return returnList;
}

//copy arraylist to a new arraylist and return in
ArrayList* ArrayListCopy(ArrayList* src){
	if (NULL == src) {
		return NULL;
	}
	ArrayList* returnList = ArrayListCreate(src->maxSize);
	if (NULL == returnList) {
		return NULL;
	}
	returnList->actualSize = src->actualSize;
	copyDataMemberArray(src->elements, returnList->elements, src->maxSize);
	return returnList;
}

void copyDataMemberArray(DataMember* src, DataMember* dst, int size){
	int index = 0;
	for (; index < size; index++) {
		copyBetweenDataMembers(&src[index], &dst[index]);
	}
	return;
}

void copyBetweenDataMembers(DataMember* src, DataMember* dst) {
	if (NULL == src || NULL == dst) {
		return;
	}
	dst->i = src->i;
	dst->j = src->j;
	dst->player = src->player;
	dst->k = src->k;
	dst->l = src->l;
	dst->enemy = src->enemy;
}

bool copyArrayFromArrayList(ArrayList* src, ArrayList* dst) {
	int index = 0;
	bool rc = true;
	// Check that size if equal
	if (NULL == src || NULL == dst || src->maxSize != dst->maxSize) {
		rc = false;
		return rc;
	}
	for (; index < src->maxSize; index++) {
		copyBetweenDataMembers(&src->elements[index], &dst->elements[index]);
	}
	return rc;
}

//remove arraylist
void ArrayListDestroy(ArrayList* src) {
	if (NULL == src) {
		return;
	}
	if (NULL != src->elements) {
		free(src->elements);
	}
	src->elements = NULL;
	free(src);
	src = NULL;
}

ARRAY_LIST_MESSAGE ArrayListClear(ArrayList* src) {
	ARRAY_LIST_MESSAGE rc = ARRAY_LIST_SUCCESS;
	if (NULL == src) {
		rc = ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	clearDataMemberArr(src->elements, src->maxSize);
	src->actualSize = 0;
	return rc;
}

void clearDataMemberArr(DataMember* src, int size) {
	int index = 0;
	for (; index < size; index++) {
		clearDataMember(&src[index]);
	}
	return;
}

void clearDataMember(DataMember* src) {
	if (NULL == src) {
		return;
	}
	src->i = 0;
	src->j = 0;
	src->player = NONE;
	src->k = 0;
	src->l = 0;
	src->enemy = NONE;
}


ARRAY_LIST_MESSAGE ArrayListAddAt(ArrayList* src, int i, char j, ChessPiece player, int k, char l, ChessPiece enemy, int index) {
	ARRAY_LIST_MESSAGE rc = ARRAY_LIST_SUCCESS;
	// Check index is not out of bounds
	if (NULL == src || index < 0 || index > src->actualSize) {
		rc = ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	// Check array is not full
	if (src->actualSize == src->maxSize) {
		rc = ARRAY_LIST_FULL;
		return rc;
	}
	// Place elem at the end of the array, not shift is required
	if (index == src->actualSize) {
		insertDataToElem(&src->elements[index], i, j, player, k, l, enemy);
		src->actualSize++;
		return rc;
	}
	// Shift elements to right
	int p = src->actualSize;
	for(; p > index; p--){
		src->elements[p] = src->elements[p-1];
	}
	insertDataToElem(&src->elements[index], i, j, player, k, l, enemy);
	src->actualSize++;
	return rc;
}

void insertDataToElem(DataMember* src, int i, char j, ChessPiece player, int k, char l, ChessPiece enemy) {
	if (NULL == src) {
		return;
	}
	src->i = i;
	src->j = j;
	src->player = player;
	src->k = k;
	src->l = l;
	src->enemy = enemy;
}

ARRAY_LIST_MESSAGE ArrayListAddFirst(ArrayList* src, int i, char j, ChessPiece player, int k, char l, ChessPiece enemy) {
	return ArrayListAddAt(src, i ,j ,player, k, l, enemy, 0);
}

ARRAY_LIST_MESSAGE ArrayListAddLast(ArrayList* src,  int i, char j, ChessPiece player, int k, char l, ChessPiece enemy) {
	if (NULL == src) {
		ARRAY_LIST_MESSAGE rc = ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	return ArrayListAddAt(src, i ,j ,player, k, l, enemy, src->actualSize);
}

ARRAY_LIST_MESSAGE ArrayListRemoveAt(ArrayList* src, int index) {
	// Check index is not out of bounds
	ARRAY_LIST_MESSAGE rc = ARRAY_LIST_SUCCESS;
	if (NULL == src || index < 0 || index > src->actualSize) {
		rc = ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	if (index == src->actualSize && index != 0) {
		rc = ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	if (src->actualSize == 0) {
		rc = ARRAY_LIST_EMPTY;
		return rc;
	}
	// If index is at the list
	if (index == (src->actualSize -1)) {
		clearDataMember(&src->elements[index]);
		src->actualSize--;
		return rc;
	}
	// Shift to left
	int i = index;
	for (; i < (src->actualSize - 1); i++) {
		src->elements[i] = src->elements[i+1];
	}
	clearDataMember(&src->elements[src->actualSize - 1]);
	src->actualSize--;
	return rc;
}

ARRAY_LIST_MESSAGE ArrayListRemoveFirst(ArrayList* src) {
	return ArrayListRemoveAt(src, 0);
}

ARRAY_LIST_MESSAGE ArrayListRemoveLast(ArrayList* src) {
	if (NULL == src) {
		ARRAY_LIST_MESSAGE rc = ARRAY_LIST_INVALID_ARGUMENT;
		return rc;
	}
	if (src->actualSize == 0) {
		ARRAY_LIST_MESSAGE rc = ARRAY_LIST_EMPTY;
		return rc;
	}
	return ArrayListRemoveAt(src, src->actualSize - 1);
}

DataMember* ArrayListGetAt(ArrayList* src, int index) {
	if (NULL == src || index < 0 || index >= src->actualSize) {
		return NULL;
	}
	return &(src->elements[index]);
}

DataMember* ArrayListGetFirst(ArrayList* src) {
	return ArrayListGetAt(src, 0);
}

DataMember* ArrayListGetLast(ArrayList* src) {
	if (NULL == src) {
		return NULL;
	}
	return ArrayListGetAt(src, src->actualSize - 1);
}

int ArrayListMaxCapacity(ArrayList* src) {
	if (NULL == src) {
		return -1;
	}
	return src->maxSize;
}

int ArrayListSize(ArrayList* src) {
	if (NULL == src) {
		return -1;
	}
	return src->actualSize;
}

bool ArrayListIsFull(ArrayList* src) {
	if (NULL == src || src->actualSize < src->maxSize) {
		return false;
	}
	return true;
}

bool ArrayListIsEmpty(ArrayList* src) {
	if (NULL == src || src->actualSize > 0) {
		return false;
	}
	return true;
}

void PrintDataElement(DataMember src){
	printf("DataMember, [ i: %d, j: %d, Player: %d ] [ k: %d, l: %d, Enemy: %d] \n", src.i, src.j, src.player, src.k, src.l, src.enemy);
}
