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
        printf("0. Return to main menu\n");
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

        printf("Enter Category Name: ");
        fgets(newCategory.CategoryName, sizeof(newCategory.CategoryName), stdin);
        newCategory.CategoryName[strcspn(newCategory.CategoryName, "\n")] = '\0';

        if(validateCategoryData(newCategory))
		{
            categories = (struct Category *)realloc(categories, (categoryCount + 1) * sizeof(struct Category));
            if (categories == NULL) 
			{
                printf("Memory allocation error!\n");
                exit(1);
            }
            categories[categoryCount] = newCategory;
            categoryCount++;
            printf("Category added successfully!\n");
            break;
        } else {
            printf("Invalid category data. Please re-enter.\n");
        }
    }
}

void editCategory()
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
	
	if (categoryCount > 0)
	{
	    categories = (struct Category *)realloc(categories, categoryCount * sizeof(struct Category));
	    if (categories == NULL && categoryCount > 0)
	    {
	        printf("Memory allocation error!\n");
	        exit(1);
	    }
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

    printf("Category sorting successful!\n");
    displayCategories();
}

void saveCategoriesToFile()
{
    FILE *file = fopen("category.bin", "w");
	if (file == NULL)
	{
	    perror("Error opening file");
	    return;
	}

    for (int i = 0; i < categoryCount; i++) 
	{
        fprintf(file, "%s %s\n", categories[i].CategoryId, categories[i].CategoryName);
    }

    fclose(file);
    printf("Save category to file successfully!\n");
}

int validateCategoryData(struct Category category) 
{
    if (strlen(category.CategoryId) == 0) 
	{
        printf("Error: Category ID cannot be empty.\n");
        return 0;
    }

    if (strlen(category.CategoryName) == 0) 
	{
        printf("Error: Category name cannot be empty.\n");
        return 0;
    }

    if (strlen(category.CategoryId) > 9) 
	{
        printf("Error: Category ID is too long (max 9 characters).\n");
        return 0;
    }

    if (strlen(category.CategoryName) > 9) 
	{
        printf("Error: Category name is too long (max 9 characters).\n");
        return 0;
    }

    for (int i = 0; i < categoryCount; i++) 
	{
        if (strcmp(categories[i].CategoryId, category.CategoryId) == 0) 
		{
            printf("Error: Duplicate category ID detected: %s.\n", category.CategoryId);
            return 0;
        }

        if (strcmp(categories[i].CategoryName, category.CategoryName) == 0) 
		{
            printf("Error: Duplicate category name detected: %s.\n", category.CategoryName);
            return 0;
        }
    }

    return 1;
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
        scanf("%d", &choice);
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
}


void addProduct()
{
    struct Product newProduct;

    getchar();

    printf("Enter product code: ");
    fgets(newProduct.productId, sizeof(newProduct.productId), stdin);
    newProduct.productId[strcspn(newProduct.productId, "\n")] = '\0';
    for (int i = 0; i < productCount; i++)
	{
        if (strcmp(products[i].productId, newProduct.productId) == 0) 
		{
            printf("Duplicate product code. Please re-enter!\n");
            return;
        }
    }

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
    if (!categoryExists) 
	{
        printf("Category code does not exist!\n");
        return;
    }

    printf("Enter product name: ");
    fgets(newProduct.productName, sizeof(newProduct.productName), stdin);
    newProduct.productName[strcspn(newProduct.productName, "\n")] = '\0';
	for (int i = 0; i < productCount; i++)
	{
        if (strcmp(products[i].productName, newProduct.productName) == 0) 
		{
            printf("Duplicate product name. Please re-enter!\n");
            return;
        }
    }

    printf("Enter quantity: ");
    if (scanf("%d", &newProduct.quantity) != 1 || newProduct.quantity < 0) 
	{
        printf("Invalid quantity. Please enter a non-negative number!\n");
        while (getchar() != '\n');
        return;
    }


    printf("Enter price: ");
    if (scanf("%d", &newProduct.price) != 1 || newProduct.price < 0) 
	{
        printf("Invalid price. Please enter a non-negative number!\n");
        while (getchar() != '\n');
        return;
    }

    products = (struct Product*)realloc(products, (productCount + 1) * sizeof(struct Product));
    if (products == NULL) 
	{
        printf("Memory allocation error!\n");
        exit(1);
    }

    products[productCount] = newProduct;
    productCount++;
    printf("Product added successfully!\n");
}


void editProduct()
{
	if(productCount == 0)
	{
		printf("There are currently no products!!!");
		return;
	}
	
	char id[10];
    printf("Enter the product code to be edited: ");
    scanf("%s", id);

    for (int i = 0; i < productCount; i++) 
	{
        if (strcmp(products[i].productId, id) == 0) 
		{
            printf("Current information: Product code: %s, Category code: %s, Product name: %s, Quantity: %d, Price: %d\n", 
                products[i].productId, products[i].categoryId, products[i].productName, products[i].quantity, products[i].price);
            printf("Enter new product name: ");
            scanf("%s", products[i].productName);
            printf("Enter new quantity: ");
            scanf("%d", &products[i].quantity);
            printf("Enter new price: ");
            scanf("%d", &products[i].price);
            printf("Product repair successful!\n");
            return;
        }
    }
    printf("Product code does not exist!\n");	
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
                printf("Product deleted successfully!\n");
            }
            return;
        }
    }
    printf("Product code does not exist!\n");
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
    for (int i = 0; i < productCount; i++)
    {
        if (strstr(products[i].productName, name))
        {
            printf("Product found: Product code: %s, Category code: %s, Product name: %s, Quantity: %d, Price: %d\n",
                   products[i].productId, products[i].categoryId, products[i].productName, products[i].quantity, products[i].price);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No products found with name containing '%s'.\n", name);
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
