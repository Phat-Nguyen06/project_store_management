// thu vien, khai bao cac struct

struct Date
{
    int month, day, year;
};

struct Category
{
    char CategoryId[10];
    char CategoryName[10];
};

struct Product
{
    char productId[10];
    char categoryId[10];
    char productName[10];
    int quantity;
    int price;
};

struct Order
{
    char orderId[10];
    char customerId[20];
    struct Date date;
    struct Product product;
};
