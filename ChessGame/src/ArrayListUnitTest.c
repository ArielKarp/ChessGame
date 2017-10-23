#include "unit_test_util.h"
#include "ArrayList.h"
#include <stdbool.h>

#define CAPACITY_SIZE 3


static bool ArrayListBasicGetTest() {
	ArrayList* list = ArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	int i=0, j = 0, k = 1, l =2;
	for (i = 0; i < CAPACITY_SIZE; i++) {
	ASSERT_TRUE(ArrayListAddLast(list, i, j , PAWN, k, l, BISHOP) == ARRAY_LIST_SUCCESS);
	}
	for (i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(ArrayListGetAt(list, i)->i == i);
	}
	ArrayListDestroy(list);
	return true;
}

static bool ArrayListBasicCopyTest() {
	ArrayList* list = ArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	int i=0, j = 0, k = 1, l =2;
	for (i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(ArrayListAddFirst(list, i, j , PAWN, k, l, BISHOP) == ARRAY_LIST_SUCCESS);
	}
	ArrayList* copyList = ArrayListCopy(list);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(ArrayListGetAt(copyList, i)->i == ArrayListGetAt(list, i)->i);
		ASSERT_TRUE(ArrayListGetAt(copyList, i)->j == ArrayListGetAt(list, i)->j);
		ASSERT_TRUE(ArrayListGetAt(copyList, i)->k == ArrayListGetAt(list, i)->k);
		ASSERT_TRUE(ArrayListGetAt(copyList, i)->l == ArrayListGetAt(list, i)->l);
		ASSERT_TRUE(ArrayListGetAt(copyList, i)->player == ArrayListGetAt(list, i)->player);
		ASSERT_TRUE(ArrayListGetAt(copyList, i)->enemy == ArrayListGetAt(list, i)->enemy);
	}
	ArrayListDestroy(list);
	ArrayListDestroy(copyList);
	return true;
}

static bool ArrayListBasicRemoveTest() {
	ArrayList* list = ArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	int i=0, j = 0, k = 1, l =2;
	for (i = 0; i < CAPACITY_SIZE; i++) {
	ASSERT_TRUE(ArrayListAddFirst(list, i, j , BISHOP, k, l, QUEEN) == ARRAY_LIST_SUCCESS);
		ASSERT_TRUE(ArrayListSize(list) == i + 1);
	}
	ASSERT_TRUE(ArrayListSize(list) == CAPACITY_SIZE);
	for (int i = 0; i < CAPACITY_SIZE; i++) {
		ASSERT_TRUE(ArrayListRemoveFirst(list) == ARRAY_LIST_SUCCESS);
		ASSERT_TRUE(ArrayListSize(list) == CAPACITY_SIZE - i - 1);
	}
	ASSERT_TRUE(ArrayListIsEmpty(list));
	ArrayListDestroy(list);
	return true;
}


static bool ArrayListBasicAddTest() {
	ArrayList* list = ArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list!=NULL);
	int i=0, j = 0, k = 1, l =2;
	for (i = 0; i < CAPACITY_SIZE; i++) {
	ASSERT_TRUE(ArrayListAddFirst(list, i, j , PAWN, k, l, BISHOP) == ARRAY_LIST_SUCCESS);
	ASSERT_TRUE(ArrayListSize(list) == i + 1);
	}
	ASSERT_TRUE(ArrayListSize(list) == CAPACITY_SIZE);
	ArrayListDestroy(list);
	return true;
}

static bool ArrayListCreateTest() {
	ArrayList* list = ArrayListCreate(CAPACITY_SIZE);
	ASSERT_TRUE(list != NULL);
	ArrayListDestroy(list);
	return true;
}

int main() {
	RUN_TEST(ArrayListCreateTest);
	RUN_TEST(ArrayListBasicAddTest);
	RUN_TEST(ArrayListBasicRemoveTest);
	RUN_TEST(ArrayListBasicGetTest);
	RUN_TEST(ArrayListBasicCopyTest);
	ArrayList* list = ArrayListCreate(CAPACITY_SIZE);
	int i = 0;
	for (; i < CAPACITY_SIZE; i++) {
		PrintDataElement(list->elements[i]);
	}
	ARRAY_LIST_MESSAGE rc = ARRAY_LIST_SUCCESS;
	if (rc == ARRAY_LIST_SUCCESS) {
		printf("Good rc code\n");
	}
	ArrayListDestroy(list);
	printf("\n");

//	int arr[3][1];
//	memcpy(arr, (int[][1]) {{2},{3},{4}}, sizeof arr);
//
//	int arr2[5] = {-1};
//	printf("%d", arr2[0]);
//
//	for (i = 0; i < 3; i++) {
//		int* arr = (int*)calloc(i, sizeof(int));
//		if (i > 0) {
//			arr[i - 1] = 3;
//		}
//		if (NULL != arr){
//			free(arr);
//			arr = NULL;
//		}
//
//	}
	printf("Str-toking bitch\n");
	char str[] = "5,4,3,2,5";
	//int len = 5;
	const char delim[2] = ",";

	printf("%s %s\n", str, delim);

	char* test = NULL;
	test = 	strtok(str, delim);
	printf("%s\n", test);

	return 0;
}
