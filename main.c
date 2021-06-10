#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxNumOfBooks    100    //The max number of books
#define maxLenOfBookName 200    //The max length of book name
int num_of_books = 0;           //The current number of books
FILE* list;

typedef struct book{int id ; char name [maxLenOfBookName] ; int quantity;}Book;

void insert_book                        (Book*);
int  search_by_id                       (Book* , int , int);
void delete_book_by_id                  (Book*);
void display_book_by_id                 (Book*);
void sort_by_name                       (Book*);
int  search_by_name                     (Book* , char*);
void display_book_by_name               (Book*);
void display_all_books_sorted_by_name   (Book*);
void display_all_books_as_entered       (Book*);
void fupdate                            (Book*);

int main()
{
        Book books [maxNumOfBooks] , books_sorted [maxNumOfBooks];
        list = fopen("list_of_books.txt" , "r");
        if(list != NULL){
        while (!feof(list)){
            fscanf(list , "%d\n" , &books[num_of_books].id);
            fgets(books[num_of_books].name ,  maxLenOfBookName ,  list);
            fscanf(list , "%d" , &books[num_of_books].quantity);
            num_of_books++;
        }
        num_of_books--;
        int count = 0;
        while (count<num_of_books){books_sorted[count]=books[count];count++;}//copying the array into another
        int choise;
        printf("USER MENU :\n");
        printf("Insert a book.\t\t\t\t\t\t(press  1)\n");
        printf("Delete a book by id.\t\t\t\t\t(press  2)\n");
        printf("Display book by id.\t\t\t\t\t(press  3)\n");
        printf("Display book by name.\t\t\t\t\t(press  4)\n");
        printf("Display all books sorted by name.\t\t\t(press  5)\n");
        printf("Display all books unsorted(as entered).\t\t\t(press  6)\n");
        char c;
        do{
            printf("?:");
            scanf("%d" , &choise);
            if (choise == 1){insert_book(books);}
            if (choise == 2){delete_book_by_id(books);}
            if (choise == 3){display_book_by_id(books);}
            if (choise == 4){display_book_by_name(books_sorted);}
            if (choise == 5){display_all_books_sorted_by_name(books_sorted);}
            if (choise == 6){display_all_books_as_entered(books);}
            if (choise != 1 && choise != 2 && choise != 3 && choise != 4 && choise != 5 && choise != 6){
                printf("Invalid value!\n");
            }
            count = 0;
            while (count<num_of_books){books_sorted[count]=books[count];count++;}//copying the array into another again;maybe the orginal array changed.
            do{
                printf("Do you want to perform another operation? (write (Y/y) or (N/n))");
                printf("?:");
                scanf(" %c" , &c);
                if (c != 'Y' && c != 'N' && c != 'y' && c != 'n')
                    printf("Invalid value!\n");
                if (c == 'N' || c == 'n')
                    exit(0);
            }while(c != 'Y' && c != 'N' && c != 'y' && c != 'n');
        }while (c == 'Y' || c == 'y');
    }
    else{
        printf("Failed to open the file!");
    }
    fclose(list);
    return 0;
}

void insert_book(Book* books){
    printf("ID: "); scanf("%d" , &books[num_of_books].id); getchar();
    printf("NAME: "); gets(books[num_of_books].name);
    int len = strlen(books[num_of_books].name);
    books[num_of_books].name[len] = '\n';
    books[num_of_books].name[len+1] = '\0';
    printf("QUANTITY: "); scanf("%d" , &books[num_of_books].quantity);
    num_of_books++;
    printf("INSERTED!\n");
    fupdate (books);
    return;
}

int search_by_id(Book* books , int id , int index){
    if (index==num_of_books && books[index].id != id)
        return -1;//To print NOT FOUND! later
    if (index<num_of_books){
        if (books[index].id == id)
            return index;
        else
            search_by_id(books , id , ++index);
    }
}

void delete_book_by_id(Book* books){
    int id;
    printf("Enter ID: ");
    scanf("%d" , &id);
    int index = search_by_id(books , id , 0);
    if (index == -1){
        printf("NOT FOUND!\n");
        return;
    }
    int nshifts = num_of_books - index;
    int i = 1 ;
    if (index<num_of_books-1){
        while (i<nshifts){
            books[index]=books[index+1];
            index++;
            i++;
        }
    num_of_books--;
    }
    if (index==num_of_books-1)
        num_of_books--;
    if (index == 0)
        num_of_books = 0;
    printf("DELETED!\n");
    fupdate (books);
    return;
}

void display_book_by_id(Book* books){
    int id;
    printf("Enter ID: ");
    scanf("%d" , &id);
    int index = search_by_id(books , id , 0);
    if (index == -1){
        printf("NOT FOUND!\n");
        return;
    }
    printf("-------------BOOK---------------\n");
    printf("ID: %d\nNAME: %sQUANTITY: %d\n" , books[index].id , books[index].name , books[index].quantity);
    printf("--------------------------------\n");
}

void sort_by_name (Book* books_sorted){
    for(int pass = 1 ; pass < num_of_books + 1 ; pass++){
        for(int i = 0 ; i < num_of_books - pass ; i++){
            int cmp = strcmp(books_sorted[i+1].name  ,  books_sorted[i].name);
            if (cmp < 0){
                //put i >> temp
                int tempi = books_sorted[i].id;
                char tempn [maxLenOfBookName] ;
                strcpy(tempn , books_sorted[i].name);
                int tempq = books_sorted[i].quantity;

                //put i >> i+1
                books_sorted[i].id = books_sorted[i+1].id;
                strcpy(books_sorted[i].name , books_sorted[i+1].name);
                books_sorted[i].quantity = books_sorted[i+1].quantity;

                //put temp >> i+1
                books_sorted[i+1].id = tempi;
                strcpy(books_sorted[i+1].name , tempn);
                books_sorted[i+1].quantity = tempq;
            }
        }
    }
}

int search_by_name(Book* books_sorted , char* name){
    int index = 0;
    int high = num_of_books-1;
    int low = 0;
    int meddle;
    while (low <= high){
        meddle = (high + low) / 2 ;
        if (strcmp(books_sorted[meddle].name , name) == 0){
            index = meddle;
            return index;
        }
        if (strcmp(books_sorted[meddle].name , name) > 0){
            high = meddle - 1 ;
        }
        if (strcmp(books_sorted[meddle].name , name) < 0){
            low = meddle + 1 ;
        }
    }
    return -1;//if not found
}

void display_book_by_name(Book* books_sorted){
    sort_by_name (books_sorted);
    char name [maxLenOfBookName];
    printf("NAME: ");
    getchar();
    fgets (name ,  maxLenOfBookName  ,  stdin);
    int index = search_by_name(books_sorted , name);
    if (index == -1){
        printf("NOT FOUND!\n");
        return;
    }
    printf("-------------BOOK---------------\n");
    printf("ID: %d\nNAME: %sQUANTITY: %d\n" , books_sorted[index].id , books_sorted[index].name , books_sorted[index].quantity);
    printf("--------------------------------\n");
}

void display_all_books_sorted_by_name(Book* books_sorted){
    sort_by_name (books_sorted);
    int j=0;
    if(num_of_books>0)
        printf("-------------BOOKS--------------\n");
    else
        printf("------------No BOOKS------------\n");
    while (j<num_of_books){
        fprintf(stdout , "ID: %d\nNAME: %sQUANTITY: %d\n" , books_sorted[j].id , books_sorted[j].name , books_sorted[j].quantity);
        printf("--------------------------------\n");
        j++;
    }
}

void display_all_books_as_entered(Book* books){
    int j=0;
    if(num_of_books>0)
        printf("-------------BOOKS--------------\n");
    else
        printf("------------No BOOKS------------\n");
    while (j<num_of_books){
        fprintf(stdout , "ID: %d\nNAME: %sQUANTITY: %d\n" , books[j].id , books[j].name , books[j].quantity);
        printf("--------------------------------\n");
        j++;
    }
}

void fupdate (Book* books){
    fclose(list);
    list = fopen("list_of_books.txt" , "w");
    int j = 0;
    while (j<num_of_books){
        fprintf(list , "%d\n" , books[j].id);
        fprintf(list , "%s" , books[j].name);
        fprintf(list , "%d\n" ,  books[j].quantity);
        j++;
    }
}
