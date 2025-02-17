// trien khai cac ham
#include<stdio.h>
#include<string.h>
#include "datatype.h"
#include"function.h"
#include<stdlib.h>
#include <conio.h>

struct Category *categories = NULL;
struct Product *products = NULL;
int categoryCount = 0;
int productCount = 0;

void categoryMenu()
{
    int choice;
    do
    {
        printf("\n\n========= PORTFOLIO MANAGEMENT =========\n");
        printf("[1]. Show category list\n");
        printf("[2]. Add category\n");
        printf("[3]. Edit category\n");
        printf("[4]. Delete category\n");
        printf("[5]. Search category by name\n");
        printf("[6]. Sort category by name\n");
        printf("[0]. Return to main menu\n");
        printf("Enter your selection: ");
        scanf("%d", &choice);
        system("cls");
        switch (choice)
        {
        case 1:
            displayCategories();
            break;
        case 2:
            addCategory();
            break;
        case 3:
    		editCategory();
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
        printf("\n\n========= STORE MANAGEMENT SYSTEM =========\n");
        printf("[1]. Category Management\n");
        printf("[2]. Product Management\n");
        printf("[0]. Exit the program\n");
        printf("Enter your selection: ");
        scanf("%d", &choice);
        system("cls");
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
		    free(products);
		    break;
        default:
            printf("\nInvalid selection! Please re-enter.\n");
        }
    } while (choice != 0);
}

void displayCategories()
{
	printf("%35s\n", "--- Show category list ---");
	if(categoryCount == 0)
	{
		printf("There are currently no categories.\n");
		return;
	}
	
 	printf("+------------+--------------------------------+\n");
    printf("| %-10s | %-30s |\n", "ID", "NAME");
    printf("+------------+--------------------------------+\n");
	for(int i = 0; i < categoryCount; i++)
	{
		printf("| %-10s | %-30s |\n", categories[i].CategoryId, categories[i].CategoryName);
		printf("+------------+--------------------------------+\n");
	}
	askGoBackOrExit();
}

void addCategory()
{
    struct Category newCategory;
    int isDuplicate;

    while (1) 
    {
    	getchar();
        printf("\nEnter Category ID: ");
        fgets(newCategory.CategoryId, sizeof(newCategory.CategoryId), stdin);
        newCategory.CategoryId[strcspn(newCategory.CategoryId, "\n")] = '\0';

        if (strlen(newCategory.CategoryId) == 0 || strlen(newCategory.CategoryId) > 9) 
        {
            printf("Error: Category ID cannot be empty or exceed %d characters.\n", 9);
            printf("Please press enter again to confirm input.\n");
            continue;
        }

        isDuplicate = 0;
        for (int i = 0; i < categoryCount; i++) 
        {
            if (strcmp(categories[i].CategoryId, newCategory.CategoryId) == 0) 
            {
                printf("Error: Category ID already exists! Please enter a unique ID.\n");
                printf("Please press enter again to confirm input.\n");
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate)
        {
			break;
		}
    }

    while (1) 
    {
        printf("Enter Category Name: ");
        fgets(newCategory.CategoryName, sizeof(newCategory.CategoryName), stdin);
        newCategory.CategoryName[strcspn(newCategory.CategoryName, "\n")] = '\0';

        if (strlen(newCategory.CategoryName) == 0 || strlen(newCategory.CategoryName) > 9) 
        {
            printf("Error: Category Name cannot be empty or exceed %d characters.\n", 9);
            continue;
        }

        isDuplicate = 0;
        for (int i = 0; i < categoryCount; i++) 
        {
            if (strcmp(categories[i].CategoryName, newCategory.CategoryName) == 0) 
            {
                printf("Error: Category Name already exists! Please enter a unique name.\n");
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) break;
    }

    categories = (struct Category *)realloc(categories, (categoryCount + 1) * sizeof(struct Category));
    if (categories == NULL)
    {
        printf("Memory allocation error!\n");
        exit(1);
    }

    categories[categoryCount] = newCategory;
    categoryCount++;
    printf("Category added successfully!\n");
    saveCategoriesToFile();
    askGoBackOrExit();
}

void editCategory() 
{
    if (categoryCount == 0) 
    {
        printf("There are currently no categories.\n");
        return;
    }

    char id[10];
    int found = -1;
    
    while (1) 
    {
        printf("Enter the category code to edit: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = '\0'; 

        for (int i = 0; i < categoryCount; i++) 
        {
            if (strcmp(id, categories[i].CategoryId) == 0) 
            {
                found = i;
                break;
            }
        }

        if (found != -1) 
        {
            break;
        } 
        else 
        {
            printf("There is no category with this ID. Please try again.\n");
        }
    }

    printf("Current information of ID %s\n", id);
    printf("+------------+--------------------------------+\n");
    printf("| %-10s | %-30s |\n", "ID", "NAME");
    printf("+------------+--------------------------------+\n");
    printf("| %-10s | %-30s |\n", categories[found].CategoryId, categories[found].CategoryName);
    printf("+------------+--------------------------------+\n");

    while (1) 
    {
        printf("Enter new category name: ");
        fgets(categories[found].CategoryName, sizeof(categories[found].CategoryName), stdin);
        categories[found].CategoryName[strcspn(categories[found].CategoryName, "\n")] = '\0';
        
        if (strlen(categories[found].CategoryName) == 0) 
        {
            printf("Error: Category Name cannot be empty.\n");
            continue;
        }
        
        if (strlen(categories[found].CategoryName) > 9) 
        {
            printf("Error: Category Name cannot exceed 9 characters.\n");
            continue;
        }
        
        int isDuplicate = 0;
        for (int i = 0; i < categoryCount; i++) 
        {
            if (i != found && strcmp(categories[i].CategoryName, categories[found].CategoryName) == 0) 
            {
                printf("Error: Category Name already exists! Please enter a unique name.\n");
                isDuplicate = 1;
                break;
            }
        }
        if (!isDuplicate) break; 
    }
    
    printf("Category edited successfully!\n");
    saveCategoriesToFile();
    askGoBackOrExit();
}


void deleteCategory()
{
	if(categoryCount == 0)
	{
		printf("There are currently no categories.\n");
		return;
	}
	
		printf("--- Show category list ---\n");
	 	printf("+------------+--------------------------------+\n");
	    printf("| %-10s | %-30s |\n", "ID", "NAME");
	    printf("+------------+--------------------------------+\n");
		for(int i = 0; i < categoryCount; i++)
		{
			printf("| %-10s | %-30s |\n", categories[i].CategoryId, categories[i].CategoryName);
			printf("+------------+--------------------------------+\n");
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
	
	if (categoryCount > 0)
	{
	    categories = (struct Category *)realloc(categories, categoryCount * sizeof(struct Category));
	    if (categories == NULL && categoryCount > 0)
	    {
	    	saveCategoriesToFile();
	        printf("Memory allocation error!\n");
	        exit(1);
	    }
	}
	
	printf("Delete category successfully\n");
	saveCategoriesToFile();
	askGoBackOrExit();
}

void searchCategoryByName()
{
    if (categoryCount == 0)
    {
        printf("There are currently no categories.\n");
        return;
    }

    char name[10];
    printf("Enter the category name to search: ");
    scanf("%s", name);
    getchar();

    int found = -1;

    printf("+------------+--------------------------------+\n");
    printf("| %-10s | %-30s |\n", "ID", "NAME");
    printf("+------------+--------------------------------+\n");

    for (int i = 0; i < categoryCount; i++)
    {
        if (strcmp(name, categories[i].CategoryName) == 0)
        {
            printf("| %-10s | %-30s |\n", categories[i].CategoryId, categories[i].CategoryName);
            found = 1;
        }
    }

    if (found == -1)
    {
        printf("| %-10s | %-30s |\n", "N/A", "No matching category found.");
    }

    printf("+------------+--------------------------------+\n");
}

void sortCategoriesByName() {
    printf("1. Ascending order\n");
    printf("2. Descending order\n");
    printf("Select: ");
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

    printf("Category sorting successful!\n");
    saveCategoriesToFile();
    displayCategories();
}

void loadCategoriesFromFile() 
{
    FILE *file = fopen("category.bin", "rb");
    if (file == NULL) 
    {
        printf("No category data found. Starting fresh.\n");
        return;
    }

    fread(&categoryCount, sizeof(int), 1, file);

    if (categoryCount > 0) 
    {
        if (categories != NULL) 
        {
            free(categories);
        }

        categories = (struct Category*)malloc(categoryCount * sizeof(struct Category));

        if (categories == NULL) 
        {
            printf("Memory allocation error!\n");
            fclose(file);
            return;
        }

        fread(categories, sizeof(struct Category), categoryCount, file);
    }

    fclose(file);
    printf("Loaded %d categories from file.\n", categoryCount);
}


void saveCategoriesToFile() 
{
    FILE *file = fopen("category.bin", "wb");
    if (file == NULL) 
	{
        printf("Error saving category data!\n");
        return;
    }
	
    fwrite(&categoryCount, sizeof(int), 1, file);
    if (categoryCount > 0) 
	{
        fwrite(categories, sizeof(struct Category), categoryCount, file);
    }

    fclose(file);
    printf("Saved categories to file successfully!\n");
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

void printProductMenu()
{
	int choice;
    do
    {
    	printf("===== PRODUCT MANAGEMENT =====\n");
		printf("[1]. Display product list\n");
		printf("[2]. Add products\n");
		printf("[3]. Edit product information\n");
		printf("[4]. Delete product\n");
		printf("[5]. Search for products by name\n");
		printf("[6]. Sort products by price\n");
		printf("[7]. Filter products\n");
		printf("[0]. Return to main menu\n");
		printf("Enter your selection: ");
        scanf("%d", &choice);
        system("cls");
        switch (choice)
        {
        case 1:
            showProducts();
            break;
        case 2:
        	addProduct();
        	break;
        case 3:
        	editProduct();
        	break;
        case 4:
        	deleteProduct();
        	break;
        case 5:
        	searchProductByName();
        	break;
        case 6:
        	SortProductsByPrice();
        	break;
        case 7:
        	filterProducts();
        	break;
        case 0:
            printf("\nBack to main menu...\n");
            break;
        default:
            printf("\nInvalid selection! Please re-enter.\n");
        }
    } while (choice != 0);
}

void showProducts() {
    printf("\n%55s\n", "===== PRODUCT LIST =====");
    
    if (productCount == 0) {
        printf("There are currently no products available.\n");
        return;
    }

    printf("+-----------------+--------------------+--------------------+------------+------------+\n");
    printf("| %-15s | %-18s | %-18s | %-10s | %-10s |\n", 
           "Product Code", "Category Code", "Product Name", "Quantity", "Price");
    printf("+-----------------+--------------------+--------------------+------------+------------+\n");
    
    for (int i = 0; i < productCount; i++) {
        printf("| %-15s | %-18s | %-18s | %-10d | %-10d |\n", 
               products[i].productId, 
               products[i].categoryId,
               products[i].productName, 
               products[i].quantity, 
               products[i].price);
    }

    printf("+-----------------+--------------------+--------------------+------------+------------+\n");
    askGoBackOrExit();
}


void addProduct()
{
    struct Product newProduct;

    while (1)
    {
        getchar();

        while (1)
        {
            printf("Enter product code: ");
            fgets(newProduct.productId, sizeof(newProduct.productId), stdin);
            newProduct.productId[strcspn(newProduct.productId, "\n")] = '\0';

            if (strlen(newProduct.productId) == 0)
            {
                printf("Error: Product ID cannot be empty. Please re-enter.\n");
                continue;
            }

            int duplicate = 0;
            for (int i = 0; i < productCount; i++)
            {
                if (strcmp(newProduct.productId, products[i].productId) == 0)
                {
                    printf("Error: Duplicate product ID detected: %s. Please re-enter.\n", newProduct.productId);
                    duplicate = 1;
                    break;
                }
            }

            if (!duplicate)
                break;
        }

        while (1)
        {
            printf("Enter category code: ");
            fgets(newProduct.categoryId, sizeof(newProduct.categoryId), stdin);
            newProduct.categoryId[strcspn(newProduct.categoryId, "\n")] = '\0';

            int categoryExists = 0;
            for (int i = 0; i < categoryCount; i++)
            {
                if (strcmp(categories[i].CategoryId, newProduct.categoryId) == 0)
                {
                    categoryExists = 1;
                    break;
                }
            }
            if (categoryExists)
                break;
            printf("Error: Category code does not exist. Please re-enter.\n");
        }

        while (1)
        {
            printf("Enter product name: ");
            fgets(newProduct.productName, sizeof(newProduct.productName), stdin);
            newProduct.productName[strcspn(newProduct.productName, "\n")] = '\0';

            if (strlen(newProduct.productName) == 0)
            {
                printf("Error: Product name cannot be empty. Please re-enter.\n");
                continue;
            }
            if (strlen(newProduct.productName) > 9)
            {
                printf("Error: Product name is too long (maximum 9 characters). Please re-enter.\n");
                continue;
            }

            int duplicate = 0;
            for (int i = 0; i < productCount; i++)
            {
                if (strcmp(newProduct.productName, products[i].productName) == 0)
                {
                    printf("Error: Duplicate product name detected: %s. Please re-enter.\n", newProduct.productName);
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate)
                break;
        }

        while (1)
        {
            printf("Enter quantity: ");
            if (scanf("%d", &newProduct.quantity) != 1)
            {
                printf("Error: Invalid input. Please enter a valid number.\n");
                while (getchar() != '\n');
                continue;
            }
            if (newProduct.quantity < 0)
            {
                printf("Error: Product quantity cannot be less than 0. Please re-enter.\n");
                continue;
            }
            break;
        }

        while (1)
        {
            printf("Enter price: ");
            if (scanf("%d", &newProduct.price) != 1)
            {
                printf("Error: Invalid input. Please enter a valid number.\n");
                while (getchar() != '\n');
                continue;
            }
            if (newProduct.price < 0)
            {
                printf("Error: Product price cannot be lower than 0. Please re-enter.\n");
                continue;
            }
            break;
        }

        products = (struct Product *)realloc(products, (productCount + 1) * sizeof(struct Product));
        if (products == NULL)
        {
            printf("Memory allocation error!\n");
            exit(1);
        }

        products[productCount] = newProduct;
        productCount++;
        printf("Product added successfully!\n");
        saveProductToFile();
        askGoBackOrExit();
        return;
    }
}

void editProduct()
{
    if (productCount == 0)
    {
        printf("There are currently no products!!!\n");
        return;
    }

    char id[10];
    int found = -1;

	getchar();
    while (1)
    {
        printf("Enter the product code to be edited: ");
        fgets(id, sizeof(id), stdin);
        id[strcspn(id, "\n")] = '\0';

        if (strlen(id) == 0)
        {
            printf("Error: Product ID cannot be empty. Please re-enter.\n");
            continue;
        }

        for (int i = 0; i < productCount; i++)
        {
            if (strcmp(products[i].productId, id) == 0)
            {
                found = i;
                printf("Current information of ID %s\n", id);
                printf("+-----------------+--------------------+--------------------+------------+------------+\n");
				printf("| %-15s | %-18s | %-18s | %-10s | %-10s |\n", "Product Code", "Category Code", "Product Name", "Quantity", "Price");
				printf("+-----------------+--------------------+--------------------+------------+------------+\n");
                printf("| %-15s | %-18s | %-18s | %-10d | %-10d |\n",
				    products[i].productId, products[i].categoryId, products[i].productName, 
				    products[i].quantity, products[i].price);
				printf("+-----------------+--------------------+--------------------+------------+------------+\n");
                break;
            }
        }

        if (found != -1)
            break;
        else
            printf("No product found with this ID. Please try again.\n");
    }

    while (1)
    {
        printf("Enter new product name: ");
        fgets(products[found].productName, sizeof(products[found].productName), stdin);
        products[found].productName[strcspn(products[found].productName, "\n")] = '\0';

        if (strlen(products[found].productName) == 0)
        {
            printf("Error: Product name cannot be empty. Please re-enter.\n");
            continue;
        }
        if (strlen(products[found].productName) > 9)
        {
            printf("Error: Product name is too long (maximum 9 characters). Please re-enter.\n");
            continue;
        }

        int duplicate = 0;
        for (int i = 0; i < productCount; i++)
        {
            if (i != found && strcmp(products[found].productName, products[i].productName) == 0)
            {
                printf("Error: Duplicate product name detected: %s. Please re-enter.\n", products[found].productName);
                duplicate = 1;
                break;
            }
        }
        if (!duplicate)
            break;
    }

    while (1)
    {
        printf("Enter new quantity: ");
        if (scanf("%d", &products[found].quantity) != 1)
        {
            printf("Error: Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }
        if (products[found].quantity < 0)
        {
            printf("Error: Product quantity cannot be less than 0. Please re-enter.\n");
            continue;
        }
        break;
    }

    while (1)
    {
        printf("Enter new price: ");
        if (scanf("%d", &products[found].price) != 1)
        {
            printf("Error: Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }
        if (products[found].price < 0)
        {
            printf("Error: Product price cannot be lower than 0. Please re-enter.\n");
            continue;
        }
        break;
    }

    printf("Product edited successfully!\n");
    saveProductToFile();
    askGoBackOrExit();
}

void deleteProduct()
{
    if (productCount == 0)
    {
        printf("There are currently no products!!!\n");
        return;
    }

    char id[10];
    int found = 0;

    while (1)
    {
        printf("Enter the product code to delete: ");
        scanf("%s", id);

        for (int i = 0; i < productCount; i++)
        {
            if (strcmp(products[i].productId, id) == 0)
            {
                found = 1;
                printf("Are you sure you want to delete? (1: Yes, 0: No): ");
                int confirm;
                scanf("%d", &confirm);
                if (confirm == 1)
                {
                    for (int j = i; j < productCount - 1; j++)
                    {
                        products[j] = products[j + 1];
                    }
                    productCount--;
                    products = (struct Product*)realloc(products, productCount * sizeof(struct Product));

                    printf("Product deleted successfully!\n");
                    saveProductToFile();
                    askGoBackOrExit();
                }
                return;
            }
        }

        if (!found)
        {
            printf("Product code does not exist! Please try again.\n");
        }
    }
}

void searchProductByName()
{
    if (productCount == 0)
    {
        printf("There are currently no products!!!\n");
        return;
    }

    char name[50];
    int found = 0;

    while (1)
    {
        printf("Enter the product name you want to search for: ");
        getchar();
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        if (strlen(name) == 0)
        {
            printf("Error: Product name cannot be empty. Please re-enter.\n");
            continue;
        }

        printf("+-----------------+--------------------+--------------------+------------+------------+\n");
	    printf("| %-15s | %-18s | %-18s | %-10s | %-10s |\n", "Product Code", "Category Code", "Product Name", "Quantity", "Price");
	    printf("+-----------------+--------------------+--------------------+------------+------------+\n");

        found = 0;
        for (int i = 0; i < productCount; i++)
        {
            if (strstr(products[i].productName, name))
            {
                printf("| %-15s | %-18s | %-18s | %-10d | %-10d |\n",
                       products[i].productId, products[i].categoryId, products[i].productName, 
                       products[i].quantity, products[i].price);
            	printf("+-----------------+--------------------+--------------------+------------+------------+\n");
                found = 1;
                askGoBackOrExit();
            }
        }

        if (!found)
        {
            printf("No matching products found for the name '%s'. Please try again.\n", name);
        }
        else
        {
            break;
        }
    }
}

void SortProductsByPrice()
{
    if (productCount == 0)
    {
        printf("There are currently no products!!!\n");
        return;
    }

    printf("1. Ascending order\n");
    printf("2. Descending order\n");
    printf("Select: ");
    int choice;
    scanf("%d", &choice);

    for (int i = 0; i < productCount - 1; i++)
    {
        for (int j = i + 1; j < productCount; j++)
        {
            if ((choice == 1 && products[i].price > products[j].price) ||
                (choice == 2 && products[i].price < products[j].price))
            {
                struct Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }

    printf("Sorting completed!\n");
    saveProductToFile();
    showProducts();
}

void filterProducts() { 
    int choice;
    printf("\n===== FILTER PRODUCTS =====\n");
    printf("1. Filter by category\n");
    printf("2. Filter by price range\n");
    printf("Enter your selection: ");
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1: 
        {
            char checkCategoryId[10];
            int categoryExists = 0;

            while (1) 
            {
                printf("Enter category ID: ");
                scanf("%s", checkCategoryId);

                categoryExists = 0;
                for (int i = 0; i < categoryCount; i++) 
                {
                    if (strcmp(categories[i].CategoryId, checkCategoryId) == 0) 
                    {
                        categoryExists = 1;
                        break;
                    }
                }

                if (categoryExists) 
                {
                    break;
                }
                else 
                {
                    printf("Category ID does not exist! Please enter a valid Category ID.\n");
                }
            }

            int found = 0;
            printf("\nProducts in category %s:\n", checkCategoryId);
            printf("+-----------------+--------------------+--------------------+------------+------------+\n");
            printf("| %-15s | %-18s | %-18s | %-10s | %-10s |\n",
                   "Product Code", "Category Code", "Product Name", "Quantity", "Price");
            printf("+-----------------+--------------------+--------------------+------------+------------+\n");

            for (int i = 0; i < productCount; i++) 
            {
                if (strcmp(products[i].categoryId, checkCategoryId) == 0) 
                {
                    found = 1;
                    printf("| %-15s | %-18s | %-18s | %-10d | %-10d |\n",
                           products[i].productId, products[i].categoryId, products[i].productName,
                           products[i].quantity, products[i].price);
                    printf("+-----------------+--------------------+--------------------+------------+------------+\n");
                }
            }

            if (!found) 
            {
                printf("No products found in this category.\n");
            }

            askGoBackOrExit();
            break;
        }

        case 2: 
        {
            int startPrice, endPrice;

            while (1) 
            {
                printf("Enter start price: ");
                scanf("%d", &startPrice);
                printf("Enter end price: ");
                scanf("%d", &endPrice);

                if (startPrice >= 0 && endPrice >= 0 && startPrice <= endPrice) 
                {
                    break;
                } 
                else 
                {
                    printf("Invalid price range! Please enter valid prices.\n");
                }
            }

            int found = 0;
            printf("\nProducts in the price range %d - %d:\n", startPrice, endPrice);
            printf("+-----------------+--------------------+--------------------+------------+------------+\n");
            printf("| %-15s | %-18s | %-18s | %-10s | %-10s |\n",
                   "Product Code", "Category Code", "Product Name", "Quantity", "Price");
            printf("+-----------------+--------------------+--------------------+------------+------------+\n");

            for (int i = 0; i < productCount; i++) 
            {
                if (products[i].price >= startPrice && products[i].price <= endPrice) 
                {
                    found = 1;
                    printf("| %-15s | %-18s | %-18s | %-10d | %-10d |\n",
                           products[i].productId, products[i].categoryId, products[i].productName,
                           products[i].quantity, products[i].price);
                    printf("+-----------------+--------------------+--------------------+------------+------------+\n");
                }
            }

            if (!found) 
            {
                printf("No products found in this price range.\n");
            }

            askGoBackOrExit();
            break;
        }

        default:
            printf("Invalid selection! Please select 1 or 2.\n");
    }
}

void saveProductToFile()
{
    FILE *file = fopen("product.bin", "wb");
    if (file == NULL)
    {
        printf("Error saving product data!\n");
        return;
    }

    fwrite(&productCount, sizeof(int), 1, file);
    if (productCount > 0)
    {
        fwrite(products, sizeof(struct Product), productCount, file);
    }

    fclose(file);
    printf("Product data saved successfully!\n");
}

void loadProductFromFile()
{
    FILE *file = fopen("product.bin", "rb");
    if (file == NULL)
    {
        printf("No product data found. Starting fresh.\n");
        return;
    }

    fread(&productCount, sizeof(int), 1, file);

    if (productCount > 0)
    {
        if (products != NULL)
        {
            free(products);
        }

        products = (struct Product*)malloc(productCount * sizeof(struct Product));

        if (products == NULL)
        {
            printf("Memory allocation error for products!\n");
            fclose(file);
            return;
        }

        fread(products, sizeof(struct Product), productCount, file);
    }

    fclose(file);
    printf("Loaded %d products from file.\n", productCount);
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

#define USERNAME "Phatnguyen"
#define PASSWORD "2006"

void createDefaultAdminFile() 
{
    FILE *file = fopen("admin.bin", "wb");
    if (file == NULL) 
	{
        printf("Error creating admin file!\n");
        return;
    }
    struct Admin admin;
    strcpy(admin.username, USERNAME);
    strcpy(admin.password, PASSWORD);

    fwrite(&admin, sizeof(struct Admin), 1, file);
    fclose(file);
}

// Hàm nhap mat khau hien thi "*"
void getPasswordInput(char *password, int maxLen)
{
    int i = 0;
    char ch;
    while (1) 
	{
        ch = getch();
        if (ch == 13) 
		{ 
            password[i] = '\0';
            printf("\n");
            break;
        } else if (ch == 8 && i > 0) 
		{ 
            i--;
            printf("\b \b");
        } else if (i < maxLen - 1 && ch != 8) 
		{
            password[i++] = ch;
            printf("*");
        }
    }
}

void adminLogin() 
{
    struct Admin admin;
    FILE *file = fopen("admin.bin", "rb");

    if (file == NULL) 
    {
        printf("Admin credentials not found! Creating default credentials.\n");
        createDefaultAdminFile();
        file = fopen("admin.bin", "rb");
        if (file == NULL)
        {
            printf("Error reading admin file!\n");
            exit(1);
        }
    }

    fread(&admin, sizeof(struct Admin), 1, file);
    fclose(file);

    char inputUsername[50], passwordInput[50];

    while (1) 
    {
        system("cls");  // Xóa màn hình

        // Giao di?n d?p cho màn hình dang nh?p
        printf("\n\n");
        printf("%75s\n", "***Store Management System Using C***");
        printf("\n");
        printf("%58s\n", "LOGIN");
        printf("%72s\n", "===============================");
        printf("%60s", "Admin username: ");
        scanf("%s", inputUsername);
        printf("%65s", "Enter admin password: ");
        getPasswordInput(passwordInput, 50);
        printf("%72s\n", "===============================");

        // Ki?m tra tên ngu?i dùng và m?t kh?u
        if (strcmp(inputUsername, admin.username) == 0 && strcmp(passwordInput, admin.password) == 0) 
        {
            printf("\nLogin successful! Welcome, %s.\n", admin.username);
            break;
        }
        else 
        {
            // N?u nh?p sai, làm m?i màn hình và hi?n th? thông báo l?i
            printf("\nInvalid username or password. Please try again.\n");
            printf("Press any key to try again...");
            getchar();  // Ð? ch? ngu?i dùng nh?n phím
            getchar();  // Nh?n thêm m?t ký t? nh?p t? ngu?i dùng
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

void askGoBackOrExit()
{
    char choice;
    do
    {
        printf("Go back (b) or Exit (0)?: ");
        scanf(" %c", &choice);

        if (choice == '0')
        {
            printf("Exiting program...\n");
            printf("========= Thank You =========\n");
			printf("========= See You Soon =========\n");
            exit(0);
        }
        else if (choice == 'b')
        {
        	system("cls");
            return;
        }
        else
        {
            printf("Invalid input! Please enter 'b' to go back or '0' to exit.\n");
        }
    } while (1);
}
