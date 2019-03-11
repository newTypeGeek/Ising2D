#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "../header/input_check.h"


// Check if the input characters is positive integer
int is_pos_int(char *ch){
	int len = strlen(ch);
	for( int i = 0; i < len; i++ ){
		if ( isdigit(ch[i]) == 0 ){
			return 0;
		}
	}

	return 1;
}

// Check if the input characters is a real number
int is_number(char *ch){
	int len = strlen(ch);
	if ( ch[0] != '-' && isdigit(ch[0]) == 0 ){
		return 0;
	}

	int dot_flag = 0;
	for( int i = 1; i < len; i++ ){
		if ( ch[i] == '.' ){
			if ( dot_flag == 1 ){
				return 0;
			}
			dot_flag = 1;
		}
		else if ( isdigit(ch[i]) == 0 ){
			return 0;
		}
	}

	return 1;
}


// Check if the input characters is a positive number
int is_pos_number(char *ch){
	int len = strlen(ch);
	if ( isdigit(ch[0]) == 0 ){
		return 0;
	}

	int dot_flag = 0;
	for( int i = 1; i < len; i++ ){
		if ( ch[i] == '.' ){
			if ( dot_flag == 1 ){
				return 0;
			}
			dot_flag = 1;
		}
		else if ( isdigit(ch[i]) == 0 ){
			return 0;
		}
	}

	return 1;
}


// Check if the file is correct
int is_file(char *ch){

	// Check if it exists
	if( access(ch, F_OK) != -1 ){
		return 1;
	}
	else { // Open the file if it does not exist
		FILE *file = fopen(ch, "a+");
		if (file == NULL){
			printf("File to append result is not created correctly, errno = %d\n", errno);
			return 0;
		}
		fclose(file);
		return 1;
	}
}
		




// Check user input arguments
int check_input_type(char **argv){
	int chk1 = is_pos_int(argv[1]);
	int chk2 = is_number(argv[2]);
	int chk3 = is_pos_number(argv[3]);
	int chk4 = is_pos_int(argv[4]);
	int chk5 = is_pos_int(argv[5]);
	int chk6 = is_pos_int(argv[6]);
	int chk7 = is_file(argv[7]);

	if ( chk1 == 0 ){
		printf("1. Square lattice length type incorrect\n");
	}

	if ( chk2 == 0 ){
		printf("2. Nearest negihbour coupling type incorrect\n");
	}

	if ( chk3 == 0 ){
		printf("3. Temperature type incorrect\n");
	}
	
	if ( chk4 == 0 ){
		printf("4. Number of iteraction type incorrect\n");
	}

	if ( chk5 == 0 ){
		printf("5. Step to begin sampling type incorrect\n");
	}

	if ( chk6 == 0 ){
		printf("6. Sampling type incorrect\n");
	}

	return chk1*chk2*chk3*chk4*chk5*chk6*chk7;

}

