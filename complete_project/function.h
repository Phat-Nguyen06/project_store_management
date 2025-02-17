//khai bao ham

//ham chinh
void mainMenu();

// hoi y kien nguoi dung
void askGoBackOrExit();

//ham trong category
void categoryMenu();
void displayCategories();
void addCategory();
void editCategory();
void deleteCategory();
void searchCategoryByName();
void sortCategoriesByName();
void loadCategoriesFromFile();
void saveCategoriesToFile();

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
void getPasswordInput(char *password, int maxLen);
void adminLogin();
