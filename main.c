#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


//Structure for managing the library users data
typedef struct users{
	char fname[15];
	char lname[15];
	char college[20];
	char field[10];
	char book[20];
	int book_id;
	char date[10];
}users;
// adding data
void add(){
	printf("----------------------------|____CAREFULLY FILL IN THE INFORMATIONS____|--------------------------------\n");
	users user;
	FILE *up = fopen("info.txt", "a+"); // up stands for user pointer
	printf("Enter first name: ");
	scanf("%s", user.fname);
	printf("Enter last name: ");
	scanf("%s",user.lname);
	printf("Enter the name of the college: ");
	scanf("%s", user.college);
	printf("Enter the field of studies: ");
	scanf("%s", user.field);
	printf("Enter the title of the book: ");
	scanf("%s", user.book);
	printf("Enter the book id: ");
	scanf("%d", &user.book_id);
	fwrite(&user, sizeof(users), 1, up);
	fclose(up);
	printf("Record successfully added\n");

}

// fonction to display all data in a table structure
void display(){
	users user;
	int recordInfo = totalRecord(); //this variable indicate the status of the record in the info file, if it is empty or not
	FILE *up = fopen("info.txt", "r");
	printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n","FIRST NAME","LAST NAME","COLLEGE","FOS","BOOK TITLE","BOOK ID","DATE ISSUED","TIME");
	printf("----------     ---------     ----------      ----          ------------    --------       ------------   ------\n");
	if (recordInfo == 0)
	{
		printf("EMPTY DATABASE\n\n");
	}
	else{
		while(fread(&user, sizeof(users), 1, up)){
			printf("%-15s%-15s%-15s%-15s%-20s%-15d%-15s%-15s\n", user.fname,user.lname,user.college,user.field,user.book,user.book_id, __DATE__, __TIME__);
		}
	}
	fclose(up);
}
// search fonction to search a specfic user in the database using the id of the book
void search(){
	users user;
	FILE *up = fopen("info.txt", "r");
	int found = 0;
	int search_id;
	printf("Enter the book id: \n");
	scanf("%d", &search_id);
		while(fread(&user, sizeof(users), 1, up)){

			if(user.book_id == search_id){
				found = 1;
				printf("%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n","FIRST NAME","LAST NAME","COLLEGE","FOS","BOOK TITLE","BOOK ID","DATE ISSUED","TIME");
				printf("----------     ---------     ----------      ----          ------------    --------       ------------   ------\n");
				printf("%-15s%-15s%-15s%-15s%-15s%-15d%-15s%-15s\n", user.fname,user.lname,user.college,user.field,user.book,user.book_id, __DATE__, __TIME__);

			}

		}
		if(user.book_id != search_id){
			printf("Record not found!!\n");
		}
	fclose(up);
}

		// Getting total number of record

int totalRecord(){
	users user;
	FILE *up = fopen("info.txt", "r");
	fseek(up, 0, SEEK_END);
	int reNO = ftell(up)/sizeof(user);
	fclose(up);
	return reNO;
}

        // updating to system

void update(){
	users user;
	FILE *up = fopen("info.txt", "r");
	FILE *up1 = fopen("temp.txt", "w");
	int found = 0;
	int id;
	printf("Enter the book id: \n");
	if(scanf("%d", &id) == 1){
		while(fread(&user, sizeof(users), 1, up)){
			if(user.book_id == id){
				found = 1;
				printf("Enter new first name: ");
				scanf("%s", user.fname);
				printf("Enter new last name: ");
				scanf("%s", user.lname);
				printf("Enter the college: ");
				scanf("%s", user.college);
				printf("Enter the field of studies: ");
				scanf("%s", user.field);
				printf("Enter the title of the book: ");
				scanf("%s", user.book);
				user.book_id = user.book_id;
			}
			fwrite(&user, sizeof(users), 1, up1);
		}
		//the code below read data from the temp file and write it in the info file
		fclose(up);
		fclose(up1);

		if(found){
			up1 = fopen("temp.txt", "r");
			up = fopen("info.txt", "w");
			while(fread(&user, sizeof(users), 1, up1)){
				fwrite(&user, sizeof(users), 1, up);
			}
			fclose(up);
			fclose(up1);
		}
		else{
			printf("\nRecord not fine\n");
		}
	}
	

}

void delete(){
	users user;
	FILE *up = fopen("info.txt", "r");
	FILE *up1 = fopen("temp.txt", "w");
	int found = 0;
	int id;
	printf("Enter the id of the book to delete: \n");
	scanf("%d", &id);
		while(fread(&user, sizeof(users), 1, up)){
			if(user.book_id == id){

				found = 1;
			}
			else{
				fwrite(&user, sizeof(users), 1, up1);
			}
		}
		fclose(up);
		fclose(up1);

		if(found){ //when the record is found 
			up1 = fopen("temp.txt", "r");
			up = fopen("info.txt", "w");
			while(fread(&user, sizeof(users), 1, up1)){
				fwrite(&user, sizeof(users), 1, up);
			}
			printf("Record Deleted successfully\n");
			fclose(up);
			fclose(up1);
		}
		else{
			printf("Record to be deleted not found!");
		}

}


int main()
{
	printf("------------------------------------------------------------------------------------------------------\n");
	printf("|                                    LIBRARY MANAGEMENT SYSTEM                                        |\n");
	printf("-------------------------------------------------------------------------------------------------------\n");

	int choice,returnValue;
	do{
		printf("\n\n\n1. ADD\n");
		printf("2. DISPLAY ALL DATA\n");
		printf("3. SEARCH\n");
		printf("4. TOTAL RECORD\n");
		printf("5. UPDATE\n");
		printf("6. DELETE\n");
		printf("0. QUITE\n");

		printf("\nEnter your choice from the options above: ");
		returnValue = scanf("%d", &choice);
		if(returnValue == 0)
		{
			printf("\nInvalid input! Your input is not a number.");
			printf("\nThis can harm the system from processing properly.");
			printf("\nPlease follow the instructions.");
            exit(-1);		
		}	
		else if (returnValue == 1){
									
			if(choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6){

				printf("Your choice is not part of the options.\n");
			}
			else {			
				switch(choice){
					case 1:
						add();
					break;
					case 2:
						display();
					break;
					case 3:
						search();
					break;
					case 4:
						printf("Total Record: %d", totalRecord());
					break;
					case 5:
						update();
					break;
					case 6:
						delete();
					break;
					default:
						printf("Thanks! You can use me anytime.\n");
				}
			}

		}


	}while(choice != 0);

}





