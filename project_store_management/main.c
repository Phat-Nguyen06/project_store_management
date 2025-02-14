#include <stdio.h>
#include <stdlib.h>
#include"function.h"
#include"datatype.h"
#include <conio.h>


int main(int argc, char *argv[]) 
{
	adminLogin();
	loadCategoriesFromFile();
	loadProductFromFile();
	mainMenu();
	printf("========= Thank You =========\n");
	printf("========= See You Soon =========\n");
	return 0;
}
