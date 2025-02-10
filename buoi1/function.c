// trien khai cac ham
#include<stdio.h>
#include<string.h>
#include "datatype.h"

struct Category *categories = NULL;
struct Product *products = NULL;
int categoryCount = 0;
int productCount = 0;

void categoryMenu()
{
    int choice;
    do
    {
        printf("\n========= PORTFOLIO MANAGEMENT =========\n");
        printf("1. Show category list\n");
        printf("2. Add category\n");
        printf("3. Edit category\n");
        printf("4. Delete category\n");
        printf("5. Search category by name\n");
        printf("6. Sort category by name\n");
        printf("7. Save the list to file\n");
        printf("0. 	Return to main menu\n");
        printf("Enter your selection: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            displayCategories();
            break;
        case 2:
            addCategory();
            break;
        case 3:
    		editProduct();
            break;
        case 4:
            deleteCategory();
            break;
        case 5:
            searchCategoryByName();
            break;
        case 6:
            sortCategoriesByName();
            break;
        case 7:
        	saveCategoriesToFile();
        	break;
        case 0:
            printf("\nBack to main menu...\n");
            break;
        default:
            printf("\nInvalid selection! Please re-enter.\n");
        }
    } while (choice != 0);
}

void mainMenu()
{
    int choice;
    do
    {
        printf("\n========= STORE MANAGEMENT SYSTEM =========\n");
        printf("1. Category Management\n");
        printf("2. Product Management\n");
        printf("0. Exit the program\n");
        printf("Enter your selection: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            categoryMenu();
            break;
        case 2:
        	printProductMenu();
        	break;
        case 0:
            printf("\nExit program...\n");
            free(categories);
            break;
        default:
            printf("\nInvalid selection! Please re-enter.\n");
        }
    } while (choice != 0);
}

void displayCategories()
{
	printf("--- Show category list ---\n");
	if(categoryCount == 0)
	{
		printf("There are currently no categories.\n");
		return;
	}
	
	printf("ID\tCategory name\n");
	for(int i = 0; i < categoryCount; i++)
	{
		printf("%s\t%s\n", categories[i].CategoryId, categories[i].CategoryName);
	}
}

void addCategory()
{
	categories = (struct Category*)realloc(categories, (categoryCount + 1) *sizeof(struct Category));
	if(categories == NULL)
	{
		printf("Memory allocation error!");
		exit(1);
	}
	
	getchar();
	printf("Enter Category ID: ");
	fgets(categories[categoryCount].CategoryId, sizeof(categories[categoryCount].CategoryId), stdin);
	categories[categoryCount].CategoryId[strcspn(categories[categoryCount].CategoryId, "\n")] = '\0';
	
	printf("Enter category name: ");
	fgets(categories[categoryCount].CategoryName, sizeof(categories[categoryCount].CategoryName), stdin);
	categories[categoryCount].CategoryName[strcspn(categories[categoryCount].CategoryName, "\n")] = '\0';
	
	categoryCount++;
	
	printf("\nCategory added successfully!\n");
}

void editProduct()
{
	if(categoryCount == 0)
	{
		printf("There are currently no categories.\n");
		return;
	}
	
	char id[10];
	printf("Enter the category code to edit:  ");
	scanf("%s", id);
	int found = -1;
	
	for(int i = 0; i < categoryCount; i++)
	{
		if(strcmp(id, categories[i].CategoryId) == 0)
		{
			found = i;
			printf("Current information: ID: %s, Category name: %s\n", categories[i].CategoryId, categories[i].CategoryName);
			printf("Enter new category name: ");
			scanf("%s", categories[i].CategoryName);
			printf("Edit category successfully!\n");
			return;
		}
	}
	
	if(found == -1)
	{
		printf("There is no id for this category.\n");
		return;
	}
}

void deleteCategory()
{
	if(categoryCount == 0)
	{
		printf("There are currently no categories.\n");
		return;
	}
	
	char id[10];
	printf("Enter the category code to delete:  ");
	scanf("%s", id);
	getchar();
	
	int found = -1;
	
	for(int i = 0; i < categoryCount; i++)
	{
		if(strcmp(id, categories[i].CategoryId) == 0)
		{
			found = i;
		}
	}
	
	if(found == -1)
	{
		printf("There is no id for this category.\n");
		return;
	}
	
	for(int i = found; i < categoryCount - 1; i++)
	{
		categories[i] = categories[i + 1];
	}
	categoryCount--;
	
	categories = (struct Category*)realloc(categories, categoryCount *sizeof(struct Category));
	if(categories == NULL)
	{
		printf("Memory allocation error!");
		exit(1);
	}
	
	printf("Delete category successfully\n");
}

void searchCategoryByName()
{
	if(categoryCount == 0)
	{
		printf("There are currently no categories.\n");
		return;
	}
	
	char name[10];
	printf("Enter the category code to delete:  ");
	scanf("%s", name);
	getchar();
	
	int found = -1;
	
	for(int i = 0; i < categoryCount; i++)
	{
		if(strcmp(name, categories[i].CategoryName) == 0)
		{
			found = i;
			printf("found name %s\n", name);
			printf("ID: %s, Category name: %s\n", categories[i].CategoryId, categories[i].CategoryName);
			return;
		}
	}
	
	if(found == -1)
	{
		printf("There is no id for this category.\n");
		return;
	}
}

void sortCategoriesByName() {
    printf("1. Sap xep tang dan\n");
    printf("2. Sap xep giam dan\n");
    printf("Lua chon: ");
    int choice;
    scanf("%d", &choice);

    for (int i = 0; i < categoryCount - 1; i++) {
        for (int j = i + 1; j < categoryCount; j++) 
		{
            if ((choice == 1 && strcmp(categories[i].CategoryName, categories[j].CategoryName) > 0) ||
                (choice == 2 && strcmp(categories[i].CategoryName, categories[j].CategoryName) < 0)) 
			{
                struct Category temp = categories[i];
                categories[i] = categories[j];
                categories[j] = temp;
            }
        }
    }

    printf("Sap xep danh muc thanh cong!\n");
    displayCategories();
}

void saveCategoriesToFile()
{
    FILE *file = fopen("category.bin", "w");
    if (file == NULL) {
        printf("Khong the mo file de luu!\n");
        return;
    }

    for (int i = 0; i < categoryCount; i++) 
	{
        fprintf(file, "%s %s\n", categories[i].CategoryId, categories[i].CategoryName);
    }

    fclose(file);
    printf("Luu danh muc vao file thanh cong!\n");
}

void printProductMenu()
{
	int choice;
    do
    {
    	printf("===== PRODUCT MANAGEMENT =====\n");
		printf("1. Display product list\n");
		printf("2. Add products\n");
		printf("3. Edit product information\n");
		printf("4. Delete product\n");
		printf("5. Search for products by name\n");
		printf("6. Sort products by price\n");
		printf("7. Filter products\n");
		printf("0. Return to main menu\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            //
            break;
        case 2:
        	//
        	break;
        case 3:
        	//
        	break;
        case 4:
        	//
        	break;
        case 5:
        	//
        	break;
        case 6:
        	//
        	break;
        case 7:
        	//
        	break;
        case 0:
            printf("\n...\n");
            break;
        default:
            printf("\nInvalid selection! Please re-enter.\n");
        }
    } while (choice != 0);
}


