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
        printf("1. Show category list\n");
        printf("2. Add category\n");
        printf("3. Edit category\n");
        printf("4. Delete category\n");
        printf("5. Search category by name\n");
        printf("6. Sort category by name\n");
        printf("0. Return to main menu\n");
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
        printf("1. Category Management\n");
        printf("2. Product Management\n");
        printf("0. Exit the program\n");
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
        	saveCategoriesToFile();
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
	printf("--- Show category list ---\n");
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

    while (1) 
	{
        printf("\nEnter Category ID: ");
        getchar();
        fgets(newCategory.CategoryId, sizeof(newCategory.CategoryId), stdin);
        newCategory.CategoryId[strcspn(newCategory.CategoryId, "\n")] = '\0';
        
        if (isCategoryIdDuplicate(newCategory.CategoryId) == 0) 
		{
            continue;
        }

        printf("Enter Category Name: ");
        fgets(newCategory.CategoryName, sizeof(newCategory.CategoryName), stdin);
        newCategory.CategoryName[strcspn(newCategory.CategoryName, "\n")] = '\0';
        
        if (isCategoryNameDuplicate(newCategory.CategoryName) == 0)
		{
            continue;
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
        break;
    }
}

void editCategory() 
{
    if (categoryCount == 0) 
    {
        printf("There are currently no categories.\n");
        return;
    }

    char id[10];
    printf("Enter the category code to edit: ");
    scanf("%s", id);
    int found = -1;

    for (int i = 0; i < categoryCount; i++) 
    {
        if (strcmp(id, categories[i].CategoryId) == 0) 
        {
            found = i;
            break;
        }
    }

    if (found == -1) 
    {
        printf("There is no category with this ID.\n");
        return;
    }

    printf("Current information of ID %s\n", id);
    printf("+------------+--------------------------------+\n");
    printf("| %-10s | %-30s |\n", "ID", "NAME");
    printf("+------------+--------------------------------+\n");
    printf("| %-10s | %-30s |\n", categories[found].CategoryId, categories[found].CategoryName);
    printf("+------------+--------------------------------+\n");

	struct Category editnewCategory;
    while (1) 
    {
        getchar();
        printf("Enter new category name: ");
        fgets(editnewCategory.CategoryName, sizeof(editnewCategory.CategoryName), stdin);
        editnewCategory.CategoryName[strcspn(editnewCategory.CategoryName, "\n")] = '\0';
		
        if (isCategoryNameDuplicate(editnewCategory.CategoryName) == 0) 
        {
            continue;
        }
    	
        strcpy(editnewCategory.CategoryId, categories[found].CategoryId);
        categories[found] = editnewCategory;

        printf("Category edited successfully!\n");
        saveCategoriesToFile();
        askGoBackOrExit();
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
    displayCategories();
}

int isCategoryIdDuplicate(const char *id) 
{
    if (strlen(id) == 0 || strlen(id) > 9) 
	{
        printf("Error: Category ID cannot be empty or exceed %d characters.\n", 9);
        return 0;
    }
    for (int i = 0; i < categoryCount; i++) 
	{
        if (strcmp(categories[i].CategoryId, id) == 0) 
		{
            printf("Error: Category ID already exists! Please enter a unique ID.\n");
            return 0;
        }
    }
    return 1;
}

int isCategoryNameDuplicate(const char *name) 
{
    if (strlen(name) == 0 || strlen(name) > 9) 
	{
        printf("Error: Category Name cannot be empty or exceed %d characters.\n", 9);
        return 0;
    }
    for (int i = 0; i < categoryCount; i++) 
	{
        if (strcmp(categories[i].CategoryName, name) == 0) 
		{
            printf("Error: Category Name already exists! Please enter a unique name.\n");
            return 0;
        }
    }
    
    return 1;
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
		printf("1. Display product list\n");
		printf("2. Add products\n");
		printf("3. Edit product information\n");
		printf("4. Delete product\n");
		printf("5. Search for products by name\n");
		printf("6. Sort products by price\n");
		printf("7. Filter products\n");
		printf("0. Return to main menu\n");
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
            printf("\n...\n");
            break;
        default:
            printf("\nInvalid selection! Please re-enter.\n");
        }
    } while (choice != 0);
}

void showProducts() {
    printf("\n===== PRODUCT LIST =====\n");
    
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
    printf("Enter the product code to be edited: ");
    scanf("%s", id);

    int found = -1;
    for (int i = 0; i < productCount; i++)
    {
        if (strcmp(products[i].productId, id) == 0)
        {
            found = i;
            printf("Current information of ID %s\n", id);
            printf("+------------+------------+--------------------------------+----------+----------+\n");
            printf("| %-10s | %-10s | %-30s | %-8s | %-8s |\n",
                   "Product ID", "Category ID", "Product Name", "Quantity", "Price");
            printf("+------------+------------+--------------------------------+----------+----------+\n");
            printf("| %-10s | %-10s | %-30s | %-8d | %-8d |\n",
                   products[i].productId, products[i].categoryId, products[i].productName,
                   products[i].quantity, products[i].price);
            printf("+------------+------------+--------------------------------+----------+----------+\n");
            break;
        }
    }

    if (found == -1)
    {
        printf("There is no ID for this product.\n");
        return;
    }

    struct Product tempProduct = products[found];

    while (1)
    {
        printf("Enter new product name: ");
        getchar();
        fgets(tempProduct.productName, sizeof(tempProduct.productName), stdin);
        tempProduct.productName[strcspn(tempProduct.productName, "\n")] = '\0';

        if (strlen(tempProduct.productName) == 0)
        {
            printf("Error: Product name cannot be empty. Please re-enter.\n");
            continue;
        }
        if (strlen(tempProduct.productName) > 9)
        {
            printf("Error: Product name is too long (maximum 9 characters). Please re-enter.\n");
            continue;
        }

        int duplicate = 0;
        for (int i = 0; i < productCount; i++)
        {
            if (i != found && strcmp(tempProduct.productName, products[i].productName) == 0)
            {
                printf("Error: Duplicate product name detected: %s. Please re-enter.\n", tempProduct.productName);
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
        if (scanf("%d", &tempProduct.quantity) != 1)
        {
            printf("Error: Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }
        if (tempProduct.quantity < 0)
        {
            printf("Error: Product quantity cannot be less than 0. Please re-enter.\n");
            continue;
        }
        break;
    }

    while (1)
    {
        printf("Enter new price: ");
        if (scanf("%d", &tempProduct.price) != 1)
        {
            printf("Error: Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');
            continue;
        }
        if (tempProduct.price < 0)
        {
            printf("Error: Product price cannot be lower than 0. Please re-enter.\n");
            continue;
        }
        break;
    }

    products[found] = tempProduct;
    printf("Product edited successfully!\n");
    saveProductToFile();
    askGoBackOrExit();
}


void deleteProduct()
{
	if(productCount == 0)
	{
		printf("There are currently no products!!!");
		return;
	}
	
    char id[10];
    printf("Enter the product code to delete: ");
    scanf("%s", id);

    for (int i = 0; i < productCount; i++)
	{
        if (strcmp(products[i].productId, id) == 0)
		{
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
    printf("Product code does not exist!\n");
    askGoBackOrExit();
}

void searchProductByName()
{
    if (productCount == 0)
    {
        printf("There are currently no products!!!\n");
        return;
    }

    char name[50];
    printf("Enter the product name you want to search for: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    int found = 0;

    printf("+------------+------------+--------------------------------+----------+----------+\n");
    printf("| %-10s | %-10s | %-30s | %-8s | %-8s |\n", 
           "Product ID", "Category ID", "Product Name", "Quantity", "Price");
    printf("+------------+------------+--------------------------------+----------+----------+\n");

    for (int i = 0; i < productCount; i++)
    {
        if (strstr(products[i].productName, name))
        {
            printf("| %-10s | %-10s | %-30s | %-8d | %-8d |\n",
                   products[i].productId, products[i].categoryId, products[i].productName, 
                   products[i].quantity, products[i].price);
            found = 1;
        }
    }

    if (!found)
    {
        printf("| %-10s | %-10s | %-30s | %-8s | %-8s |\n", 
               "N/A", "N/A", "No matching products found.", "-", "-");
    }

    printf("+------------+------------+--------------------------------+----------+----------+\n");
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
            printf("Enter category ID: ");
            scanf("%s", checkCategoryId);

            int categoryExists = 0;
            for (int i = 0; i < categoryCount; i++) 
			{
                if (strcmp(categories[i].CategoryId, checkCategoryId) == 0) 
				{
                    categoryExists = 1;
                    break;
                }
            }

            if (categoryExists == 0) 
			{
                printf("Category ID does not exist!\n");
                return;
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
                }
            }

            if (!found) 
			{
                printf("No products found in this category.\n");
            }
            break;
        }

        case 2: 
		{
            int startPrice, endPrice;
            printf("Enter start price: ");
            scanf("%d", &startPrice);
            printf("Enter end price: ");
            scanf("%d", &endPrice);

            if (startPrice < 0 || endPrice < 0 || startPrice > endPrice) 
			{
                printf("Invalid price range!\n");
                return;
            }

            int found = 0;
            printf("\nProducts in the price range %d - %d:\n", startPrice, endPrice);
            printf("+-----------------+--------------------+--------------------+------------+------------+\n");
            printf("| %-15s | %-18s | %-18s | %-10s | %-10s |\n",
                   "Product Code", "Category Code", "Product Name", "Quantity", "Price");
            printf("+-----------------+--------------------+--------------------+------------+------------+\n");

            for (int i = 0; i < productCount; i++) {
                if (products[i].price >= startPrice && products[i].price <= endPrice) 
				{
                    found = 1;
                    printf("| %-15s | %-18s | %-18s | %-10d | %-10d |\n",
                           products[i].productId, products[i].categoryId, products[i].productName,
                           products[i].quantity, products[i].price);
                }
            }

            if (!found) 
			{
                printf("No products found in this price range.\n");
            }
            break;
        }

        default:
            printf("Invalid selection!\n");
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
    printf("Saved product to file successfully!\n");
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
        printf("Enter admin username: ");
        scanf("%s", inputUsername);
        printf("Enter admin password: ");
        getPasswordInput(passwordInput, 50);

        if (strcmp(inputUsername, admin.username) == 0 && strcmp(passwordInput, admin.password) == 0) 
		{
            printf("Login successful! Welcome, %s.\n", admin.username);
            break;
        } 
		else 
		{
            printf("Invalid username or password. Please try again.\n");
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
            return;
        }
        else
        {
            printf("Invalid input! Please enter 'b' to go back or '0' to exit.\n");
        }
    } while (1);
}
