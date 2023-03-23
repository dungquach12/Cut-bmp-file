#include"ReadBitMap.h"

int main(int argc, char* argv[]) {
	
	printf("Program name is: %s", argv[0]);
	cout << endl;
	printf("You have entered %d arguments:\n", argc);
	cout << endl;

	if (argc == 1)
		printf("\nNo Extra Command Line Argument Passed "
			"Other Than Program Name");
	if (argc == 4) {
		int Height = 1;
		int Width = 1;
		if (*(argv[2] + 1) != 'h' && *(argv[2] + 1) != 'w') {

			cout << "Syntax error!" << endl;
			return 0;
		}
		if (*(argv[2] + 1) == 'h') {
			Height = atoi(argv[3]);
		}
		if (*(argv[2] + 1) == 'w') {
			Width = atoi(argv[3]);
		}
		outputImg(argv[1], Height, Width);
	}

	if (argc == 6) {
		int Height = 1;
		int Width = 1;
		if (*(argv[2] + 1) == 'h') {
			Height = atoi(argv[3]);
		}
		if (*(argv[2] + 1) == 'w') {
			Width = atoi(argv[3]);
		}
		if (*(argv[4] + 1) == 'h') {
			Height = atoi(argv[5]);
		}
		if (*(argv[4] + 1) == 'w') {
			Width = atoi(argv[5]);
		}
		cout << Height << ' ' << Width << endl;
		outputImg(argv[1], Height, Width);
	}

	if (argc > 6) {
		cout << "Syntax error!" << endl;
		return 0;
	}

	return 0;
}