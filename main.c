/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
int quickSort(int *a, int n);

int hashCode(int key);

int hashing(int *a, int **ht);

int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
    printf("[----- [김상수] [2018038078] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

/**
 * @brief 배열을 만들고 랜덤값으로 초기화해주는 함수이다.
 * 
 * @param a 
 * @return int 
 */
int initialize(int** a)
{
	int *temp = NULL;

	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;
	} else
		temp = *a;

	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

/**
 * @brief 배열을 할당 해제해주는 함수이다.
 * 
 * @param a 
 * @return int 
 */
int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

/**
 * @brief 배열을 인덱스순으로 출력해주는 함수이다.
 * 
 * @param a 
 */
void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

/**
 * @brief 선택정렬이다.
 * 
 * @param a 
 * @return int 
 */
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

    /**
     * 작은 인덱스부터 크기를 비교하고 그 중에서 가장 작은 값과 위치를 바꿔준다.
     * 그 후 다음 인덱스부터 같은 과정을 반복한다.
     * 
     */
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // 현재 인덱스를 최솟값으로 설정(작은 인덱스부터, i가 0부터 시작하니..)
		min = a[i]; // 가장 작은 값을 저장할 변수 설정(현재 minindex의 값)
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) // 선택한 인덱스의 다음 부터 배열의 끝까지 크기를 비교한다.
		{
			if (min > a[j]) // 가장 작은 값을 저장한 변수보다 작은 값이 있으면
			{
				min = a[j]; // 가장 작은 값을 저장한 변수를 바꿔주고
				minindex = j; // 가장 작은 값의 인덱스도 바꿔준다.
			}
		} // 배열을 한번 다 훑어 본 후
		a[minindex] = a[i]; // 가장 작은 값이 저장되어 있는 곳에는 현재 비교중인 인덱스에 저장되어 있는 값을
		a[i] = min; // 현재 비교중인 인덱스에 저장되어 있는 값에는 찾아온 가장 작은 값을 넣어준다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

/**
 * @brief 삽입정렬이다.
 * 
 * @param a 
 * @return int 
 */
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

    // 첫번째 인덱스(0)의 경우에는 하나밖에 없으니 정렬이 되어 있다치고 2번쨰 인덱스부터 시작.
    // 정렬된 일부분을 만들면서 최종적으로 정렬된 배열을 만든다.
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; // 현재원소를 임시로 저장
		j = i; // 현재 원소의 인덱스를 저장
        // 현재 원소가 이전 원소보다 작고 인덱스가 0보다클 동안 루프를 실행
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1]; // 이전 원소를 현재 위치에 복사
			j--; // 인덱스 하나를 감소
		}
		a[j] = t; // 임시 변수의 값을 삽입 위치에 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

/**
 * @brief 버블정렬이다.
 * 
 * @param a 
 * @return int 
 */
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
        // 인근 두개의 값을 비교하면서 큰 값을 배열의 끝으로 몰고 가면서 정렬해준다.
		for (j = 0; j < MAX_ARRAY_SIZE-i-1; j++)
		{
            // 다음 인덱스에 저장된 값이 더 작으면 교환해준다.
			if (a[j] > a[j+1])
			{
				t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

/**
 * @brief 셸정렬입니다.
 * 
 * @param a 
 * @return int 
 */
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

    // 배열의 절반 크기에서 시작하여 간격 H를 1까지 줄여나갑니다.
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
        // 각 간격에 대해
		for (i = 0; i < h; i++)
		{
            // h만큼 떨어진 원소에 대해
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
                // 인덱스와 값 저장
				v = a[j];
				k = j;
                // 현재 원소가 이전 원소보다 작고 인덱스가 h-1보다 클 동안
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h]; // 이전 원소를 현재 위치에 넣고 인덱스를 줄인다.
					k -= h;
				}
				a[k] = v; // 임의의 값을 삽입할 위치에 저장
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

/**
 * @brief 퀵소트입니다.
 * 
 * @param a 
 * @param n 
 * @return int 
 */
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

    
	if (n > 1)
	{
    v = a[n-1]; // 피벗으로 배열의 마지막 원소를 선택
    i = -1; // i는 배열의 왼쪽 끝에서 시작
    j = n - 1; // j는 피벗의 위치에서 시작

    while(1)
    {
        while(a[++i] < v); // 피벗보다 크거나 같은 원소를 찾을 때까지 i를 오른쪽으로 이동
        while(a[--j] > v); // 피벗보다 작거나 같은 원소를 찾을 때까지 j를 왼쪽으로 이동

        if (i >= j) break; // i와 j가 교차하면 종료
        // swap
        t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
    // 피벗 교환
    t = a[i];
    a[i] = a[n-1];
    a[n-1] = t;
    // 피벗을 기준으로 배열을 나눠서 재귀적으로 돌린다.
    quickSort(a, i);
    quickSort(a+i+1, n-i-1);
	}


	return 0;
}

// 키 값을 해시 테이블의 크기로 나눈 나머지 값을 반환하는 함수
int hashCode(int key) {
    return key % MAX_HASH_TABLE_SIZE;
}

// 주어진 배열을 해시 테이블로 변환하는 함수
int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

    // 초기화되어 있지 않다면 공간을 할당해준다.
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;
	} else {
		hashtable = *ht;
	}

    // 해시 테이블의 모든 요소를 -1로 초기화한다.
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; // 키 값을 가져오고
		hashcode = hashCode(key); // 키 값을 해쉬화(?) 한다.

        // 해시 테이블의 해당 위치에 값이 없다면 키를 삽입
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
        // 값이 있다면 다음 위치에서 공간을 찾는다.
		} else 	{

			index = hashcode;

            // -1이 빈 공간이라는 뜻이니까.
			while(hashtable[index] != -1)
			{
                // 빈공간을 찾을 떄까지 하나씩 늘려가면서 찾아준다.
				index = (++index) % MAX_HASH_TABLE_SIZE;
			}
            // 빈 공간에 키를 삽입한다.
			hashtable[index] = key;
		}
	}

	return 0;
}

// 해시테이블에서 해당 키의 위치를 반환한다.
int search(int *ht, int key)
{
	int index = hashCode(key); // 키 값을 해쉬화(?)한다.

    // 만약 해시 테이블의 해당 위치에 키가 있다면 그 위치를 반환한다.
	if(ht[index] == key)
		return index;
    // 만약 해시 테이블의 해당 위치에 없다면 다음 위치로 이동해서 키를 찾는다. 
	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}