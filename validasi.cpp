#include <stdio.h>
#include <string.h>

// fungsinya buat cek kalo str1 dimulai dengan str2
// contoh: 
// ControllerTest, Controller ( true )
// ControllTest, Controller ( false )
bool startsWith(char str1[], char str2[]) {
	return strncmp(str1, str2, strlen(str2)) == 0;
}

// fungsinya buat cek kalo str1 diakhiri dengan str2
// contoh:
// TestController, Controller ( true )
// TestControl, Controller ( false )
bool endsWith(char str1[], char str2[]) {
	return strcmp(str1 + strlen(str1) - strlen(str2), str2) == 0;
}

// fungsinya buat cek kalo str2 ada di dalam str1
// contoh:
// TestControllerTest, Controller ( true )
// TestControlTest, Controller ( false )
bool contains(char str1[], char str2[]) {
	return strstr(str1, str2) != NULL;
}

// fungsinya buat cek ada berapa kata di dalam str1
// contoh:
// Toyota   Avanza Anjing ( 3 )
// Toyota ( 1 )
// Toyota Avanza ( 2 )
int countWords(char str1[]) {
	int count = 0;
	char* token = strtok(str1, " ");
	
	while (token != NULL) {
		count++;
		
		token = strtok(NULL, " ");
	}
	
	return count;
}

int main() {
	// fungsi startsWith
	char testStartsWith[] = "ControllerTest";
	char testStartsWithPrefix[] = "Controller";
	if (startsWith(testStartsWith, testStartsWithPrefix)) {
		puts("starts with true");
	} else {
		puts("starts with false");
	}
	
	// fungsi endsWith
	char testEndsWith[] = "TestController";
	char testEndsWithPrefix[] = "Controller";
	if (endsWith(testEndsWith, testEndsWithPrefix)) {
		puts("ends with true");
	} else {
		puts("ends with false");
	}
	
	// fungsi contains
	char testContains[] = "TestControllerTest";
	char testContainsString[] = "Controller";
	if (contains(testContains, testContainsString)) {
		puts("contains true");
	} else {
		puts("contains false");
	}
	
	// fungsi countWords
	char testCountWord[] = "Toyota Avanza";
	printf("%d\n", countWords(testCountWord));
	
	return 0;
}
