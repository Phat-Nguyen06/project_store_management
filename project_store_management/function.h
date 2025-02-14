//khai bao ham

//ham trong category
void categoryMenu();
void mainMenu();
void displayCategories();
void addCategory();
void editCategory();
void deleteCategory();
void searchCategoryByName();
void sortCategoriesByName();
void loadCategoriesFromFile();
void saveCategoriesToFile();
int isCategoryIdDuplicate(const char *id);
int isCategoryNameDuplicate(const char *name);

// ham trong product
void printProductMenu();
void showProducts();
void addProduct();
void editProduct();
void deleteProduct();
void searchProductByName();
void SortProductsByPrice();
void filterProducts();
void saveProductToFile();
void loadProductFromFile();

//dang nhap amin
void createDefaultAdminFile();
void adminLogin();
