#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

#define MAX_RESERVATION 40
#define TICKET_PRICE 1200.00  



void currentDate(char current_date[]) {
    time_t today = time(NULL);
    struct tm date = *localtime(&today);

    sprintf(current_date, "%02d_%02d_%d", date.tm_mon+1, date.tm_mday, date.tm_year + 1900);

}

void currentTime(char current_Time[]) {
    time_t today = time(NULL);
    struct tm date = *localtime(&today);
    sprintf(current_Time,"%02d:%02d", date.tm_hour,date.tm_min);
}    

struct BusReservation{
    char name[100];
    char contact_num[100];
    int seatNumber;
    char departure[100];
    char departure_time[10];
    char destination[100];
    char date[100]; 
    int bus_number;
    float price;
};

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readreservations(struct BusReservation reserve[], int bus_no, char date[]) {
    FILE *inputfile;
    char *filename;
    int count = 0;
    char fname[100];

    strcpy(fname, date);

    switch (bus_no) {
        case 1:
            strcat(fname, "bus1.txt");
            break;
        case 2:
            strcat(fname, "bus2.txt");
            break;
        case 3:
            strcat(fname, "bus3.txt");
            break;
        case 4:
            strcat(fname, "bus4.txt");
            break;
        case 5:
            strcat(fname, "bus5.txt");
            break;
        case 6:
            strcat(fname, "bus6.txt");
            break;
        case 7:
            strcat(fname, "bus7.txt");
            break;
        case 8:
            strcat(fname, "bus8.txt");
            break;
        case 9:
            strcat(fname, "bus9.txt");
            break;       
        default:
            printf("Invalid city code\n");
            return 0;
    }

        filename=fname;
    inputfile = fopen(filename, "r");

    char line[900];
    char d[]= ",";

    while(fgets(line, sizeof(line), inputfile)!=NULL){
         char *token = strtok(line, d );
        strcpy(reserve[count].name, token);
        token = strtok(NULL, d);
        strcpy(reserve[count].contact_num, token);
        token = strtok(NULL, d);
        reserve[count].seatNumber = atoi(token);
        token = strtok(NULL, d);
        strcpy(reserve[count].departure, token);
        token = strtok(NULL, d);
        strcpy(reserve[count].destination, token);
        token = strtok(NULL, d);
        strcpy(reserve[count].departure_time, token);
        token = strtok(NULL, d);
        strcpy(reserve[count].date, token);
        token = strtok(NULL, d);
        reserve[count].bus_number = atoi(token);
        token = strtok(NULL, d);
        reserve[count].price = atof(token);

        count++;
    }

    fclose(inputfile);
    
    return count;
}

void takeReservations(struct BusReservation reserve[], int count, int newRes, int bus_no, char date[]){
  
   
    FILE *outputfile, *readablefile;
    char *filename;
    char dest[100];
    char currtime[10];
    currentTime(currtime);
    char fname[20];
    char rfname[40]="read_";
    strcpy(fname, date);

    char depT[10];

    if(count+newRes>=MAX_RESERVATION){
      
        printf("%d seats remaining\n", MAX_RESERVATION-count);
        return;
    }else{

         switch (bus_no) {
        case 1:
            strcat(fname,"bus1.txt");
            strcpy(depT,"10:00 AM");
            strcpy(dest,"Sylhet");
            break;
        case 2:
            strcat(fname,"bus2.txt");
            strcpy(depT,"10:30 AM");
            strcpy(dest,"Chattogram");
            break;
        case 3:
            strcat(fname, "bus3.txt");
            strcpy(depT,"11:00 AM");
            strcpy(dest,"Khulna");
            break;
        case 4:
            strcat(fname, "bus4.txt");
            strcpy(depT,"11:30 AM");
            strcpy(dest,"Sylhet");
            break;
        case 5:
            strcat(fname, "bus5.txt");
            strcpy(depT,"12:00 PM");
            strcpy(dest,"Chattogram");
            break;
        case 6:
            strcat(fname, "bus6.txt");
            strcpy(depT,"12:30 PM");
            strcpy(dest,"Khulna");
            break;
        case 7:
            strcat(fname, "bus7.txt");
            strcpy(depT,"01:00 PM");
            strcpy(dest,"Sylhet");
            break;
        case 8:
            strcat(fname, "bus8.txt");
            strcpy(depT,"01:30 PM");
            strcpy(dest,"Chattogram");
            break;
        case 9:
            strcat(fname,"bus9.txt");
            strcpy(depT,"02:00 PM");
            strcpy(dest,"Khulna");
            break;       
        default:
            printf("Invalid Bus Number\n");
            return ;
    }
        filename=fname;
        strcat(rfname,filename);
        outputfile = fopen(filename, "a");
        readablefile = fopen(rfname, "a");
        if(readablefile==NULL){
            readablefile = fopen(rfname, "w");
        }
        if (outputfile == NULL) {
                printf("Error opening file for appending");
                return;
            }

            int i;
        for(i= count;i<count+newRes;i++){
            printf("\nReservation number %d \n", i + 1);

            printf("Passenger Name: ");
            fgets(reserve[i].name, sizeof(reserve[i].name), stdin);
            reserve[i].name[strlen(reserve[i].name) - 1] = '\0';
            fprintf(outputfile, "%s,", reserve[i].name);
            
            printf("Contact Number: ");
            fgets(reserve[i].contact_num, sizeof(reserve[i].contact_num), stdin);
            reserve[i].contact_num[strlen(reserve[i].contact_num) - 1] = '\0';
            fprintf(outputfile, "%s,", reserve[i].contact_num);
           
            reserve[i].seatNumber= i+1;
            fprintf(outputfile, "%d,", reserve[i].seatNumber);


            strcpy(reserve[i].departure,"Dhaka");
            fprintf(outputfile, "%s,", reserve[i].departure);
           
            strcpy(reserve[i].destination, dest);
            fprintf(outputfile, "%s,", reserve[i].destination);

            strcpy(reserve[i].departure_time, depT);
            fprintf(outputfile, "%s,", reserve[i].departure_time);
            
            strcpy(reserve[i].date, date);
            fprintf(outputfile, "%s,", reserve[i].date);

            reserve[i].bus_number = bus_no;
            fprintf(outputfile, "%d,", reserve[i].bus_number);

            reserve[i].price= TICKET_PRICE;
            fprintf(outputfile, "%.2f\n", reserve[i].price);

            printf("\n\n\n(Reservation number %d) \n", i + 1);
            printf("Passenger Name: %s\n", reserve[i].name);
            printf("Contact Number: %s\n", reserve[i].contact_num);
            printf("Seat Number: %d\n", reserve[i].seatNumber);
            printf("Departure City: %s\n", reserve[i].departure);
            printf("Destination City: %s\n", reserve[i].destination);
            printf("Departure Time: %s\n", reserve[i].departure_time);
            printf("Travel Date: %s\n", reserve[i].date);
            printf("Bus number: %d\n", bus_no);
            printf("Ticket Price: %.2f\n", TICKET_PRICE);
            printf("\n");


                    fprintf(readablefile, "(Reservation number %d) \n", i + 1);
                    fprintf(readablefile, "Passenger Name: %s\n", reserve[i].name);
                    fprintf(readablefile, "Contact Number: %s\n", reserve[i].contact_num);
                    fprintf(readablefile, "Seat Number: %d\n", reserve[i].seatNumber);
                    fprintf(readablefile, "Departure City: %s\n", reserve[i].departure);
                    fprintf(readablefile, "Destination City: %s\n", reserve[i].destination);
                    fprintf(readablefile, "Departure Time: %s\n", reserve[i].departure_time);
                    fprintf(readablefile, "Travel Date: %s\n", reserve[i].date);
                    fprintf(readablefile, "Bus number: %d\n", bus_no);
                    fprintf(readablefile, "Ticket Price: %.2f\n", TICKET_PRICE);
                    fprintf(readablefile, "\n\n");

        }


             printf("Reservation Done");
                fclose(outputfile);
                fclose(readablefile);
                return;
    
          
       
    }   
    
}

void searchbyPassenger(struct BusReservation reserve[], char passenger[], int count,int bus_no) {
    FILE *searchfile;
    searchfile = fopen("search_results.txt", "w");
      if (searchfile == NULL) {
        printf("Error opening file %s\n", "search_results.txt");
        return;
    }

    int len = strlen(passenger),i;
    
    if (len > 0 && passenger[len - 1] == '\n')
        passenger[len - 1] = '\0';

    for(i = 0; i < count; i++) {
        
        if(strcmp(reserve[i].name, passenger) == 0) {
            printf("Found result check %s \n", "search_results.txt");

            fprintf(searchfile, "(Reservation number %d) \n", i + 1);
            fprintf(searchfile, "Passenger Name: %s\n", reserve[i].name);
            fprintf(searchfile, "Contact Number: %s\n", reserve[i].contact_num);
            fprintf(searchfile, "Seat Number: %d\n", reserve[i].seatNumber);
            fprintf(searchfile, "Departure City: %s\n", reserve[i].departure);
            fprintf(searchfile, "Destination City: %s\n", reserve[i].destination);
            fprintf(searchfile, "Departure Time: %s\n", reserve[i].departure_time);
            fprintf(searchfile, "Travel Date: %s\n", reserve[i].date);
            fprintf(searchfile, "Bus number: %d\n", bus_no);
            fprintf(searchfile, "Ticket Price: %.2f\n", TICKET_PRICE);
            fprintf(searchfile, "\n");

            printf("\n\n\n(Reservation number %d) \n", i + 1);
            printf("Passenger Name: %s\n", reserve[i].name);
            printf("Contact Number: %s\n", reserve[i].contact_num);
            printf("Seat Number: %d\n", reserve[i].seatNumber);
            printf("Departure City: %s\n", reserve[i].departure);
            printf("Destination City: %s\n", reserve[i].destination);
            printf("Departure Time: %s\n", reserve[i].departure_time);
            printf("Travel Date: %s\n", reserve[i].date);
            printf("Bus number: %d\n", bus_no);
            printf("Ticket Price: %.2f\n", TICKET_PRICE);
            printf("\n");

            return;
        }
        
       
    }
    printf("\nNot Found\n");

           
    fclose(searchfile);
    return;
}

void searchbyContact(struct BusReservation reserve[], char contact[], int count, int bus_no) {
    FILE *searchfile;
    searchfile = fopen("search_results.txt", "w");
      if (searchfile == NULL) {
        printf("Error opening file %s\n", "search_results.txt");
        return;
    }
    int len = strlen(contact),i;
    if (len > 0 && contact[len - 1] == '\n')
        contact[len - 1] = '\0';

    for(i=0;i<count;i++){
        if(strcmp(reserve[i].contact_num, contact)==0) {
                    printf("Found result check %s \n", "search_result.txt");
                    
                    fprintf(searchfile, "(Reservation number %d) \n", i + 1);
                    fprintf(searchfile, "Passenger Name: %s\n", reserve[i].name);
                    fprintf(searchfile, "Contact Number: %s\n", reserve[i].contact_num);
                    fprintf(searchfile, "Seat Number: %d\n", reserve[i].seatNumber);
                    fprintf(searchfile, "Departure City: %s\n", reserve[i].departure);
                    fprintf(searchfile, "Destination City: %s\n", reserve[i].destination);
                    fprintf(searchfile, "Departure Time: %s\n", reserve[i].departure_time);
                    fprintf(searchfile, "Travel Date: %s\n", reserve[i].date);
                    fprintf(searchfile, "Bus number: %d\n", bus_no);
                    fprintf(searchfile, "Ticket Price: %.2f\n", TICKET_PRICE);
                    fprintf(searchfile, "\n");
                    printf("\n\n\n(Reservation number %d) \n", i + 1);
                    printf("Passenger Name: %s\n", reserve[i].name);
                    printf("Contact Number: %s\n", reserve[i].contact_num);
                    printf("Seat Number: %d\n", reserve[i].seatNumber);
                    printf("Departure City: %s\n", reserve[i].departure);
                    printf("Destination City: %s\n", reserve[i].destination);
                    printf("Departure Time: %s\n", reserve[i].departure_time);
                    printf("Travel Date: %s\n", reserve[i].date);
                    printf("Bus number: %d\n", bus_no);
                    printf("Ticket Price: %.2f\n", TICKET_PRICE);
                    printf("\n");
                    
                    return;
                }
                
    }
    printf("\nNot found\n");
    fclose(searchfile);
    return;
}

void cancelReservation(int bus_no, char date[]) {
    FILE *orgfile, *tempfile;
    char fname[1000];
    char tempfname[1000];

    strcpy(fname, date);

    int cancelResNum;
    printf("Enter Reservation Number(1-40): ");
    scanf("%d", &cancelResNum);
    clearInputBuffer();
    
    switch (bus_no) {
        case 1:
            strcat(fname, "bus1.txt");
            break;
        case 2:
            strcat(fname, "bus2.txt");
            break;
        case 3:
            strcat(fname, "bus3.txt");
            break;
        case 4:
            strcat(fname, "bus4.txt");
            break;
        case 5:
            strcat(fname, "bus5.txt");
            break;
        case 6:
            strcat(fname, "bus6.txt");
            break;
        case 7:
            strcat(fname, "bus7.txt");
            break;
        case 8:
            strcat(fname, "bus8.txt");
            break;
        case 9:
            strcat(fname, "bus9.txt");
            break;
        
        default:
            printf("Invalid bus number\n");
            return;
    }
     
    strcpy(tempfname, "temp____");
    strcat(tempfname, fname);

    orgfile = fopen(fname, "r");
    tempfile = fopen(tempfname, "w");
    
    

    if (orgfile == NULL || tempfile == NULL) {
        printf("Error opening files\n");
        return;
    }

    int currentLine = 1;
    char buffer[2048];
    
    while (fgets(buffer, sizeof(buffer), orgfile) != NULL) {
        if (currentLine != cancelResNum) {
            fputs(buffer, tempfile);
        }
        currentLine++;
    }



    fclose(orgfile);
    fclose(tempfile);

    remove(fname);
    rename(tempfname, fname);

    printf("Reservation canceled successfully\n");
}

int main(){
    struct BusReservation reserve[MAX_RESERVATION];
    int bus_no, menu,count; 
    char travelDate[100];
    char todayDate[100];
    char nowTime[20];
    currentDate(todayDate);
    currentTime(nowTime);
   
    FILE *inputfile;
    inputfile = fopen("intro.txt", "r");
    char intro[1000];
     
        while(fgets(intro,sizeof(intro), inputfile)){
            printf("%s", intro);
        }
    do{
        printf("\n\nMenu\n");
    printf("1. Book a seat\n");
    printf("2. Search by Passenger Name\n");
    printf("3. Search by Passenger Contact\n");
    printf("4. Cancel Reservation\n");
    printf("5. Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &menu);

     
    if(menu==5){
        printf("Exiting...\n");
        return 0;
    }else if(menu<1||menu>5){
        printf("Invalid Choice\n");
        continue;;
    }

        printf("\nChoose Bus Number(1-9): ");
        scanf("%d", &bus_no);
        clearInputBuffer();


    

        printf("\nEnter Travel Date(MM_DD_YYYY): ");
        scanf("%s", travelDate);
        clearInputBuffer();


        
        if((menu==1 && strcmp(travelDate,todayDate)==-1) || (menu==4 && strcmp(travelDate,todayDate)==-1) ){
            printf("Invalid Date");
            continue;
        }else{

        if(bus_no == 1&& strcmp(travelDate,todayDate)==0){
                if(strcmp(nowTime,"10:00")==1){
                printf("The bus left");
                continue;
                }
        }
        if(bus_no == 2&& strcmp(travelDate,todayDate)==0){
                if(strcmp(nowTime,"10:30")==1){
                printf("The bus left");
                continue;
                }
        }
        if(bus_no == 3&& strcmp(travelDate,todayDate)==0){
                if(strcmp(nowTime,"11:00")==1){
                printf("The bus left");
                continue;
                }
        }
        if(bus_no == 4&& strcmp(travelDate,todayDate)==0){
                if(strcmp(nowTime,"11:30")==1){
                printf("The bus left");
                continue;
                }
        }
        if(bus_no == 5&& strcmp(travelDate,todayDate)==0){
                if(strcmp(nowTime,"12:00")==1){
                printf("The bus left");
                continue;
                }
        }
        if(bus_no == 6&& strcmp(travelDate,todayDate)==0){
                if(strcmp(nowTime,"12:30")==1){
                printf("The bus left");
                continue;
                }
        }
        if(bus_no == 7&& strcmp(travelDate,todayDate)==0){
                if(strcmp(nowTime,"13:00")==1){
                printf("The bus left");
                continue;
                }
        }
        if(bus_no == 8 && strcmp(travelDate,todayDate)==0){
                if(strcmp(nowTime,"13:30")==1){
                printf("The bus left");
                continue;
                }
        }
        if(bus_no == 9 && strcmp(travelDate,todayDate)==0){
                if(strcmp(nowTime,"14:00")==1){
                printf("The bus left");
                continue;
                }
        }
       
        
        }
        printf("\n");
        
        if(bus_no<=0 || bus_no>9){
            printf("Invalid Choice");
        }else{
            count= readreservations(reserve,bus_no,travelDate);
             printf("\n%d seats Remaining\n", MAX_RESERVATION - count);
            fclose(inputfile);
        }


            switch(menu) {
            case 1: {
                int newRes;
                printf("\nEnter Number of reservations: ");
                scanf("%d", &newRes);

                if(newRes<1||newRes>40){
                    printf("Invalid");
                    continue;
                }

                if(newRes>(MAX_RESERVATION-count)){
                    printf("Invalid input");
                }
                clearInputBuffer();

                takeReservations(reserve,count,newRes,bus_no,travelDate);
                count+=newRes;
                break;
            }
            case 2: {
                char name[100];
                printf("\nEnter Passenger name: ");
                fgets(name, sizeof(name),stdin);
                searchbyPassenger(reserve,name,count,bus_no);
                
                break;
            }
            case 3:{
                char contact[100];
                printf("\nEnter Contact Number: ");
                fgets(contact, sizeof(contact), stdin);
                searchbyContact(reserve,contact,count,bus_no);
                break;
            }
            case 4:{
                cancelReservation(bus_no,travelDate);
                break;
            
            }
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    }while(menu!=5);
    return 0;
    
}
