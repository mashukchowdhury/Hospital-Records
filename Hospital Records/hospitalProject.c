#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct hospital //structure and attributes for the Hospital
{
    char hospitalName [100]; //Hospital Name
    char triageRanking [100]; //Triage Ranking is string as we want to include the severity
    char patientName [100]; //Name of Patient
    char admitNurse [100]; //Name of Admitting Nurse
    char insuranceInfo [100]; //Insurance Info
    char doctorSeen [100]; //Name of Doctor
    char diagnosisPatient [100]; //Diagnosis of Patient
    float costOfTreatment; //cost of Procedure

    struct hospital *next; //pointer to the next block of memory 
};


//function prototypes
struct hospital *GenerateLinkedList(); //initial linked list
void fillHospitalData(struct hospital *middle); 
void browseEntries(struct hospital *middle);
struct hospital *addNewItem(struct hospital *start);
struct hospital *addFirstItem();
struct hospital *deleteEntry(struct hospital *start);
struct hospital *modifyEntry(struct hospital *start);
struct hospital *deleteEndNode(struct hospital *start);
struct hospital *search(struct hospital *start);
void monthlyRevenue(struct hospital *start);    //Monthly Earnings from all procedure
struct hospital *deleteFirstNode(struct hospital *start);
void saveFile(struct hospital *start);
void freeMem(struct hospital *start);  //for clearing heap memory
struct hospital *ReadListIn(struct hospital *start);
struct hospital *ReadNextFromFile(struct hospital *start, FILE *pFile);
struct hospital *sort(struct hospital *start);

int main(){
    int begin;
    int ch;
    int press;
    //you will need a pointer to start of the list. IT SHALL NEVER MOVE*
    //*Unless you re-oder the elements.
    //However ENTRY (FIRST) NODE MUST ALWAYS BE PRESERVED

    struct hospital *start;
    start = 0;
    //we will define a second pointer so we can move through the list and find the
    //last entry in the list (for adding new nodes)

    struct hospital *move;
    puts("--------------------------------------------------------------------------------------------");
    puts("Welcome to the Central Hospital Record Keeping Hub. Please follow the on-screen instructions to navigate the Hub.");
    puts("Please Press 1 to Start || Press 2 to load Saved Data");
    scanf("%d", &begin);
    while ((ch = getchar()) != '\n' && ch != EOF);
    if (begin == 1){  //loads new data
        while (begin == 1){
        
            if (begin == 1){
                puts("Main Menu: ");
                puts("1 --> Add Entries    | 2--> Browse Entries | 3 --> Modify Entries|");
                puts("4 --> Delete Entries | 5--> Save Entry     | 6 --> Sort Entries"); 
                puts("7 --> Search Patient | 8--> Calculate Monthly Earnings"); 
                puts("9 --> Exit the Hub");
                scanf("%d", &press);
                while ((ch = getchar()) != '\n' && ch != EOF) ;
                    
                if (press == 1)
                {
    
                    if (start == 0) { 
                        start = addFirstItem(); 
                    } else { 
                        addNewItem(start); 
                    }

                }else if (press == 2)
                {
                    browseEntries(start);
                }else if (press == 3)
                {                        
                    modifyEntry(start);
                }else if (press == 4)
                {
                    start=deleteEntry(start);
                }else if (press == 5)
                {
                    saveFile(start);
                }else if (press == 6)
                {
                    //start = sort(start->triageRanking);
                puts("Service is not available right now!"); //my apologies as I started the project late and was not able to figure this out
                }else if (press == 7)
                {
                    search(start);
                }else if (press == 8)
                {
                    monthlyRevenue(start);
                }else if (press == 9)
                {
                    puts("Thank you for using our Hub.");
                    break;
                }
                else
                {
                    puts("Oops! Invalid input. Please reade the instructions.");
                    exit(1);
                }
            }
        }
    }else if (begin == 2){     //loads previous data 
        puts("Loading Previously Stored Data");
        start = ReadListIn(start);

        while (begin == 2){
        
            if (begin == 2){

                puts("Main Menu: ");
                puts("1 --> Add Entries    | 2--> Browse Entries | 3 --> Modify Entries|");
                puts("4 --> Delete Entries | 5--> Save Entry     | 6 --> Sort Entries"); 
                puts("7 --> Search Patient | 8--> Calculate Monthly Earnings"); 
                puts("9 --> Exit the Hub");
                
                scanf("%d", &press);
                while ((ch = getchar()) != '\n' && ch != EOF) ;
                    
                if (press == 1)
                {
    
                    if (start == 0) { 
                        start = addFirstItem(); 
                    } else { 
                        addNewItem(start); 
                    }

                }else if (press == 2)
                {
                    browseEntries(start);
                }else if (press == 3)
                {                        
                    modifyEntry(start);
                }else if (press == 4)
                {
                    start=deleteEntry(start);
                }else if (press == 5)
                {
                    saveFile(start);
                }else if (press == 6)
                {
                           //start = sort(start->triageRanking);
                puts("Our Apologies! Service is not available right now."); //my apologies as I started the project late and was not able to figure this out
                }else if (press == 7)
                {
                    search(start);
                }else if (press == 8)
                {
                    monthlyRevenue(start);
                }else if (press == 9)
                {
                    puts("Thank you for using our Hub.");
                    break;
                }else{
                    puts("Oops! Invalid input. Please reade the instructions.");
                    exit(1);
                }
            }
        }
    }else{
        
        puts("Oops! Invalid input. Please reade the instructions.");
        exit(2);
    } 
       
    return 0;
}


struct hospital *GenerateLinkedList(){
    //pointer info *start = first node
    //pointer info *middle = Pointer moving at all times
    //pointer info *end = end node
    struct hospital *start , *middle, *end; //INITIALIZING ALL POINTERS

    int counter = 0;
    char keepGoing = 'y';
    int ch;

    while (keepGoing == 'y'){
        
        if (counter == 0){

            middle = (struct hospital*)malloc(sizeof(struct hospital)); //allocating the size based on 
                                                                        //hospital structure size
        if (middle == NULL) {
                puts("OOPS! MEMORY ALLOCATION ERROR!");
                exit(1);
            }

            start = middle;
            counter++;
            fillHospitalData(middle);
            middle->next = 0;
            end = middle;
        }
        else
        {
            //setting up next node
            middle = (struct hospital*)malloc(sizeof(struct hospital));
            if (middle == NULL) {
                puts("OOPS! MEMORY ALLOCATION ERROR!");
                exit(1);
            }
            counter++;
            fillHospitalData(middle);
            middle->next = 0;
            end->next = middle; // link it to a memory before end = middle;
            end = middle;
        }

        puts("Enter new Record? y/n\n"); //prompt user if they want to enter more data
        scanf("%c", &keepGoing);
        while ((ch = getchar()) != '\n' && ch != EOF); //buffer flush
    }

    return start; //returning start pointer to initial state
}

void fillHospitalData(struct hospital *middle){  //function with data entry instructions
    int ch;

    puts("Enter Hospital Name: ");  //prompt the name of the Hospital
    //fgets(middle->hospitalName,50,stdin);
    scanf("%[^\n]", middle->hospitalName);
    while ((ch = getchar()) != '\n' && ch != EOF);

    puts("Enter Triage Ranking: "); //prompt the Triage Ranking
    puts("Please Choose From: \"Level 1: Resuscitation\"");
    puts("                    \"Level 2: Emergent \"");
    puts("                    \"Level 3: Urgent \"");
    puts("                    \"Level 4: Less Urgent \"");
    puts("                    \"Level 5: Not Urgent \"");
    scanf("%[^\n]", middle->triageRanking); 
    while ((ch = getchar()) != '\n' && ch != EOF);

    puts("Enter Patient's Full Name: "); //prompt Patient's Name
    scanf("%[^\n]", middle->patientName);
    while ((ch = getchar()) != '\n' && ch != EOF);

    puts("Enter Admitting Nurse's Full Name: "); //prompt Admitting Nurse's Name
    scanf("%[^\n]", middle->admitNurse);
    while ((ch = getchar()) != '\n' && ch != EOF);
                                                    //Enter Insurance Information
    puts("Enter Patient's Insurance information (Company&Policy_Number together):  ");
    scanf("%[^\n]", middle->insuranceInfo);
    while ((ch = getchar()) != '\n' && ch != EOF);

    puts("Enter Name of Patient's Doctor: "); //Name of Doctor Attending Patient
    scanf("%[^\n]", middle->doctorSeen);
    while ((ch = getchar()) != '\n' && ch != EOF);

    puts("What is the patient diagnosed with? "); //Result of Diagnosis
    scanf("%[^\n]", middle->diagnosisPatient);
    while ((ch = getchar()) != '\n' && ch != EOF);

    puts("Cost of Procedure:$ ");    //Total cost of Treatment
    scanf("%f", &middle->costOfTreatment);
    while ((ch = getchar()) != '\n' && ch != EOF);
}

struct hospital *addFirstItem(){      //storing item entries
    struct hospital *start, *middle, *end;
    int ch;
    middle = (struct hospital*)malloc(sizeof(struct hospital));
    if (middle == NULL) {
        puts("OOPS! MEMORY ALLOCATION ERROR!");
        exit(1);
    }

    start = middle;
    fillHospitalData(middle); //filling in the data with data at pointer
    middle->next = 0;
    end = middle;

    return start;
}

struct hospital *addNewItem(struct hospital *start){
    struct hospital  *middle, *end;
    middle = start;
    int ch;

    while (middle->next != 0){
        middle = middle->next; 
    } 
    end = middle;
    //set up next node. link to end node
    middle = (struct hospital*)malloc(sizeof(struct hospital));
    if (middle == NULL) {
        puts("OOPS! MEMORY ALLOCATION ERROR!");
        exit(1);
    }

    fillHospitalData(middle);
    middle->next = 0;
    end->next = middle;

    return middle;
}


void browseEntries(struct hospital *middle){ //function to browse entries
    struct hospital *move;
    int counter = 0;
    int check;

    //move through the list and display
    move = middle;
    while (move->next != 0){
        counter++;
        printf("\nEntry NO: %d\n", counter);
        printf("Hospital Name: %s \n",move->hospitalName);
        printf("Triage Ranking: %s \n",move->triageRanking);
        printf("Patient's Name: %s \n",move->patientName);
        printf("Admitting Nurse: %s \n",move->admitNurse);
        printf("Insurance Information: %s \n",move->insuranceInfo);
        printf("Attending Doctor : %s \n",move->doctorSeen);
        printf("Diagnosis: %s \n",move->diagnosisPatient);
        printf("Cost of Procedure:$ %.2f \n",move->costOfTreatment);
        puts("--------------------------------------------------");

        if (move->next != 0)
        {
            int ch;
            puts("1 --> Continue | 2 --> Stop");
            scanf("%d", &check);
            while ((ch = getchar()) != '\n' && ch != EOF);
            if (check == 1)
            {
                move = move->next;
            }else if (check == 2)
            {
                break;
            }
          
        }
        
    }

    if (check != 2) {  //Displaying results as user continued
        counter++;
        printf("\nEntry NO: %d\n", counter);
        printf("Hospital Name: %s \n",move->hospitalName);
        printf("Triage Ranking: %s \n",move->triageRanking);
        printf("Patient's Name: %s \n",move->patientName);
        printf("Admitting Nurse: %s \n",move->admitNurse);
        printf("Insurance Information: %s \n",move->insuranceInfo);
        printf("Attending Doctor : %s \n",move->doctorSeen);
        printf("Diagnosis: %s \n",move->diagnosisPatient);
        printf("Cost of Procedure:$ %.2f \n",move->costOfTreatment);
        puts("End of list\n");
    }

}

//Modifying
struct hospital *modifyEntry(struct hospital *start){
    struct hospital  *middle, *end;
    middle = start;

    int ch, counter, entry;

    puts("Enter the number of entries you want to modify\n");
    scanf("%d", &entry);

    while ((ch = getchar()) != '\n' && ch != EOF);
    counter = 0;
    
    while (middle->next != 0){
       
        
        counter++;
        if (entry == counter)
        {
            break;
        }
         middle = middle->next;
    
    }
  
    fillHospitalData(middle);            
}
//Delete Entry
struct hospital *deleteEntry(struct hospital *start){
    struct hospital  *middle, *end ,*previous;
    middle = start;
    int ch, count, entry;
    puts("Enter the number of entries you want to DELETE\n");
    scanf("%d", &entry);
    while ((ch = getchar()) != '\n' && ch != EOF);
    
    count = 0;
    //deleting First Entry
    if (entry == 1){
                    
        start = deleteFirstNode(start);        

    }else{

        while (middle->next != 0){
   
            count++;
            
            if (entry == count)
            {
            
                break;
            }
            previous = middle;
            middle = middle->next;
    
        }
        if (middle->next != 0){
            previous->next = middle->next;
            free(middle);
            puts("\nThe selected Entry has been deleted\n");
            middle = previous->next;
        }else
        {            
            deleteEndNode(start);                        
        }   
    }   
    return start;          
}

//Deleting first node
struct hospital *deleteFirstNode(struct hospital *start){
    struct hospital  *middle, *end, *move ,*previous;
    middle = start;

    if (start != NULL && start != 0) 
    {
        middle = start->next;
    }
    free(start);
    start = middle;
    return middle;

}

//Deleting end Node
struct hospital *deleteEndNode(struct hospital *start){
    struct hospital  *middle, *end ,*previous;
    middle = start;

    if(middle == 0){
        puts("Record cannot be deleted.");
    }else{
        previous = 0;
        end = middle;
        while(end->next != 0){
            previous = end;
            end = end->next;
        }
        if (previous == 0){
            middle = 0;
        }else
        {
            previous->next = 0;
            free(end);
        }
        
    }
}
//Search Function with patient's name to find records
struct hospital *search(struct hospital *start){
    struct hospital  *middle, *end, *move ,*previous;
    middle = start;
    int ch;
    char entry[30];
    puts("Enter Patient Name:");
    scanf("%[^\n]",entry);  //taking in full 
    while ((ch = getchar()) != '\n' && ch != EOF);
    while (middle != 0)
    {
        if(strcmp(middle->patientName, entry) == 0){  //compares string with entered data
        //if strings compared match each other pointer points to patient's details
            move=middle;
            
        puts("\nMATCH FOUND\n");
        
        printf("Hospital Name: %s \n",move->hospitalName);
        printf("Triage Ranking: %s \n",move->triageRanking);
        printf("Patient's Name: %s \n",move->patientName);
        printf("Admitting Nurse: %s \n",move->admitNurse);
        printf("Insurance Information: %s \n",move->insuranceInfo);
        printf("Attending Doctor : %s \n",move->doctorSeen);
        printf("Diagnosis: %s \n",move->diagnosisPatient);
        printf("Cost of Procedure:$ %.2f \n",move->costOfTreatment);
        puts("End of list\n");

            break;
        }
        middle = middle->next;
    }
    
}
//Calculating hospital Monthly Earns
void monthlyRevenue(struct hospital *start){
    struct hospital  *middle, *end, *move ,*previous;
    middle = start;
    double total = 0.00;

    while (middle->next != 0){
   
        total += (middle->costOfTreatment); //summation of all medical bills
    
        middle = middle->next;
    
    }

    total += (middle->costOfTreatment);

    printf("\nHospital Revenue:$ %.2f\n", total);

}

// Write Data or save data to file
void saveFile(struct hospital *start) {
	FILE *pFile; //pointer to open file
	pFile =  fopen("hospitalRecords.txt", "wb"); //hospitalRecords serves as file to edit
    //wb to write to file in binary mode
    
	
	if(pFile != 0) {
        struct hospital  *middle, *holdNext, *move ,*holdPrevious;
        middle = start;		
		holdNext = 0;
		holdPrevious = 0;
		
		while(middle != 0) {
			holdNext = middle->next;
						
			middle->next = NULL;
						
			fseek(pFile, 0, SEEK_END);
			fwrite(middle, sizeof(struct hospital), 1, pFile);
			
			printf("Patient %s records have been saved successfully.\n",middle->patientName);
			
			middle->next = holdNext;
			
			
			holdNext = NULL;
			holdPrevious = NULL;
			
			middle = middle->next;
		}
		fclose(pFile); //close function to exit from file
		pFile = NULL;
	} else {
		printf("Error Opening File\n");
	}
	
}

//Cleanup function
void freeMem(struct hospital *start) {
    struct hospital  *middle, *freeMe, *holdMe;	
	freeMe = start;
	holdMe = NULL;	
	while(freeMe != NULL) {
		holdMe = freeMe->next;
		printf("%s is now free\n", freeMe->hospitalName);
		free(freeMe);
		freeMe = holdMe;
	}	
}

//Read  next From File
struct hospital *ReadNextFromFile(struct hospital *start, FILE *pFile) {
	size_t returnValue;
	if(start == NULL) {
		start = malloc(sizeof(struct hospital));
		returnValue = fread(start, sizeof(struct hospital), 1, pFile);
		start->next = NULL;
	} else {
		struct hospital *indexhospital = start;
		struct hospital *newhospital = malloc(sizeof(struct hospital));
		while(indexhospital->next != NULL) {
			indexhospital = indexhospital->next;
		}
		returnValue = fread(newhospital, sizeof(struct hospital), 1, pFile);
		indexhospital->next = newhospital;
		newhospital->next = NULL;
		
	}
	return start;
}
// Main Reading from file
struct hospital *ReadListIn(struct hospital *start) {
	
	FILE *pFile;
	pFile = fopen("hospitalRecords.txt", "rb"); //Read in Binary
	if(pFile != NULL) {
	
		freeMem(start);
		start = NULL;
		
		fseek(pFile, 0, SEEK_END);
		long fileSize = ftell(pFile);
		rewind(pFile);
		
		int numEntries = (int)(fileSize / (sizeof(struct hospital)));
		printf("Total Entries on File:%d\n",numEntries);
		
		int loop = 0;
		for(loop = 0; loop < numEntries; ++loop) {
			fseek(pFile, (sizeof(struct hospital) * loop), SEEK_SET);
			start = ReadNextFromFile(start, pFile);
		}
	}  else {
		printf("Error! File Cannot Open.");
	}
	
	return start;

}
//Sorting Function

struct hospital *sort(struct hospital *m_array){
 
    
}        

