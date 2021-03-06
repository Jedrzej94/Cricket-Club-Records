/**---------------------------------------------------------------------------**\
				========================================
				Cricket Club Records - data manipulation
				========================================

Description:
	This is a very simple script that I have written from scratch back in 2013 for my school purposes.
	It is a little system for user to manage his data stored in files.

Purpose:
	Only for learning purposes, if you wish to edit this code, then go ahead and do so. Please, leave credits.

Legal:
	The Initial Developer of the Original Code is Jędrzej Chmielewski.
	Portions created by the Initial Developer are Copyright (C) 2013
	the Initial Developer. All Rights Reserved.

Version:
	1.0

\**---------------------------------------------------------------------------**/

// Includes.
#include    <stdio.h>
#include    <stdbool.h>
#include    <windows.h> 

// Macro definitions.
#define     clrscr(); system("CLS");

// Headers of all the functions written.
void DisplayUserMenu();
void PromptUserForFilePaths();
int AddNewMember(char team_initial);
int PrintMemberDetails(char team_initial);
int DeleteMember(char team_initial);
int RestoreMember(char team_initial);
int AmendMemberDetails(char team_initial);

// Global variables.
FILE * team_file;

char batt_path[128],
     fiel_path[128],
     file_path[128];

// Member struct.
struct Members
{
     int Number;
     char Name[32];
     long int TelNo;
     bool Created;
};

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//---------------------------- main -----------------------------
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
int main(void)
{
    // Call function to enter file paths.
    PromptUserForFilePaths();

    // Display user menu.
    DisplayUserMenu();
    return 0;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//--------------------- CODE FUNCTIONS --------------------------
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void DisplayUserMenu(void)
{
    char option;

    do
    {
        clrscr();
        printf("\t\t\tCRICKET CLUB RECORDS - DATA ENTRY\n\n");
        printf("1 - Add new member\n");
        printf("2 - Print member details\n");
        printf("3 - Delete member\n");
        printf("4 - Restore member\n");
        printf("5 - Amend member details\n\n");
        printf("\"X\" - Close the program");
        
        option = toupper(getch());
    
        switch(option)
        {
            case '1':
            {
                 printf("\n\nAdding new member procedure. . .\nPlease enter team initial (B/F): ");
                 AddNewMember(toupper(getch()));
                 break;     
            }
            
            case '2':
            {
                 printf("\n\nPrinting member details. . .\nPlease enter team initial (B/F): ");
                 PrintMemberDetails(toupper(getch()));
                 break;     
            }
            
            case '3':
            {
                 printf("\n\nDeleting member procedure. . .\nPlease enter team initial (B/F): ");
                 DeleteMember(toupper(getch()));
                 break;       
            }
            
            case '4':
            {
                 printf("\n\nRestoring member procedure. . .\nPlease enter team initial (B/F): ");
                 RestoreMember(toupper(getch()));
                 break; 
            }
            
            case '5':
            {
                 printf("\n\nAmending member details. . .\nPlease enter team initial (B/F): ");
                 AmendMemberDetails(toupper(getch()));
                 break;     
            }
        }
    }
    while(option != 'X');
}

// ---------------------------
// -> Add a new member function.
int AddNewMember(char team_initial)
{
     clrscr();
     
     switch(team_initial)
     {
          case 'B':team_file = fopen(batt_path, "r+b");  break;
          case 'F':team_file = fopen(fiel_path, "r+b");  break;
          default :printf("ERROR: Wrong team initial!"); return 1; break;
     }
     
     int PlayerNo;
     char InputName[32];
     long int InputTelNo;
     
     printf("Please enter member number (it's also used as UID): ");
     fflush(stdin); scanf("%d", &PlayerNo);
     
     struct Members singlemember;
     
     fseek(team_file, (PlayerNo - 1) * sizeof(struct Members), SEEK_SET);
     fread(&singlemember, sizeof(struct Members), true, team_file);
     
     if(singlemember.Created)
     {
          printf("ERROR: That member already exists! ");
          system("PAUSE");
          return 1;
     }
     
     else 
     {
          singlemember.Created = true;
          singlemember.Number = PlayerNo;
     }
          
     printf("Please enter member name: ");
     fflush(stdin); scanf("%s", InputName);
     strcpy(singlemember.Name, InputName);
     
     printf("Please enter member telephone number: ");
     fflush(stdin); scanf("%ld", &InputTelNo);
     singlemember.TelNo = InputTelNo;
     
     fseek(team_file, (PlayerNo - 1) * sizeof(struct Members), SEEK_SET);
     fwrite(&singlemember, sizeof(struct Members), true, team_file);
     fclose(team_file);
     
     printf("Member has been added successfully! Press any key to continue. . .");
     getch();
     return 0;
}

// ---------------------------
// -> Print details about member from selected team.
int PrintMemberDetails(char team_initial)
{
     switch(team_initial)
     {
          case 'B':team_file = fopen(batt_path, "rb");   break;
          case 'F':team_file = fopen(fiel_path, "rb");   break;
          default :printf("ERROR: Wrong team initial!"); return 1; break;
     }
     
     int PlayerNo;
     struct Members singlemember;
     
     printf("Please enter member number: ");
     fflush(stdin); scanf("%d", &PlayerNo);
     
     fseek(team_file, (PlayerNo - 1) * sizeof(struct Members), SEEK_SET);
     fread(&singlemember, sizeof(struct Members), true, team_file);
     
     if(singlemember.Created && singlemember.Number == PlayerNo)
     {
          printf("\n\n[DETAILS]\nName: %s\nNumber: %d\nTelNo: %ld\n\n", singlemember.Name, singlemember.Number, singlemember.TelNo);
     }
     
     else
     {  
          printf("ERROR: That member doesn't exist!\n\n");
     }
     
     fclose(team_file);
     
     system("PAUSE");
     return 0;
}

// ---------------------------
// -> Delete member from selected team.
int DeleteMember(char team_initial)
{
     switch(team_initial)
     {
          case 'B':team_file = fopen(batt_path, "r+b");  break;
          case 'F':team_file = fopen(fiel_path, "r+b");  break;
          default :printf("ERROR: Wrong team initial!"); return 1; break;
     }
     
     int PlayerNo;
     char answer;
     struct Members singlemember;
     
     printf("Please enter member number: ");
     fflush(stdin); scanf("%d", &PlayerNo);
     
     fseek(team_file, (PlayerNo - 1) * sizeof(struct Members), SEEK_SET);
     fread(&singlemember, sizeof(struct Members), true, team_file);
     
     if(singlemember.Created && singlemember.Number == PlayerNo)     
         printf("Are you sure, that you want to delete %s member (Y/N)?\n\n", singlemember.Name);
     else
         printf("ERROR: That member is already deleted or doesn't exist!");
         
     answer = toupper(getch());
     if(answer == 'Y')
     {
          singlemember.Created = false;
          
          fseek(team_file, (PlayerNo - 1) * sizeof(struct Members), SEEK_SET);
          fwrite(&singlemember, sizeof(struct Members), true, team_file);
          fclose(team_file);
          
          printf("Member has been deleted successfully!\nPress any key to continue. . .");
          getch();
     }
     
     else if(answer == 'N')
     {
          system("PAUSE");
     }
     return 0;
}

// ---------------------------
// -> Restoring a member back in the team (only when has been removed from the team beforehand).
int RestoreMember(char team_initial)
{
     switch(team_initial)
     {
          case 'B':team_file = fopen(batt_path, "r+b");  break;
          case 'F':team_file = fopen(fiel_path, "r+b");  break;
          default :printf("ERROR: Wrong team initial!"); return 1; break;
     }
     
     int PlayerNo;
     char answer;
     struct Members singlemember;
     
     printf("Please enter member number: ");
     fflush(stdin); scanf("%d", &PlayerNo);
     
     fseek(team_file, (PlayerNo - 1) * sizeof(struct Members), SEEK_SET);
     fread(&singlemember, sizeof(struct Members), true, team_file);
     
     if(!singlemember.Created && singlemember.Number == PlayerNo)     
         printf("Are you sure, that you want to restore %s member (Y/N)?\n\n", singlemember.Name);
     else
         printf("ERROR: That member is already restored or doesn't exist!");
         
     answer = toupper(getch());
     if(answer == 'Y')
     {
          singlemember.Created = true;
          
          fseek(team_file, (PlayerNo - 1) * sizeof(struct Members), SEEK_SET);
          fwrite(&singlemember, sizeof(struct Members), true, team_file);
          fclose(team_file);
          
          printf("Member has been restored successfully!\nPress any key to continue. . .");
          getch();
     }
     
     else if(answer == 'N')
     {
          system("PAUSE");
     }
     return 0;
}

// ---------------------------
// -> Changing details of a member.
int AmendMemberDetails(char team_initial)
{
    clrscr();
    switch(team_initial)
    {
         case 'B':team_file = fopen(batt_path, "r+b");  break;
         case 'F':team_file = fopen(fiel_path, "r+b");  break;
         default :printf("ERROR: Wrong team initial!"); return 1; break;
    }
    
    int PlayerNo;
    char answer;
    struct Members singlemember;
      
    printf("Please enter member number: ");
    fflush(stdin); scanf("%d", &PlayerNo);
    
    fseek(team_file, (PlayerNo - 1) * sizeof(struct Members), SEEK_SET);
    fread(&singlemember, sizeof(struct Members), true, team_file);
    
    if(singlemember.Created && singlemember.Number == PlayerNo)
    {   
         printf("\n\n[DETAILS]\nName: %s\nNumber: %d\nTelNo: %ld", singlemember.Name, singlemember.Number, singlemember.TelNo);
         printf("\n\nWhat details do you want to edit?");
         printf("\n1 - Name");
         printf("\n2 - Number");
         printf("\n3 - Mobile number");
         printf("\n\"X\" - go back");
         printf("\n\nPlease type the number: ");
    }
    
    else
    {
         printf("ERROR: That member doesn't exist!");
         getch();
         return 1;
    }

    char NewInputPlayerName[32];
    int NewInputNumber;
    long int NewInputTelNo;
    
    do
    { 
        answer = toupper(getche());
        switch(answer)
        {
             // Edit player name.
             case '1':
             {
                  printf("\n\nPlease enter new player name: ");
                  fflush(stdin); scanf("%s", NewInputPlayerName);
                  
                  strcpy(singlemember.Name, NewInputPlayerName);
                  
                  printf("\nName has been successfully changed to: \"%s\"! Press any key to continue. . .", NewInputPlayerName);
             }
             break;
             
             
             // Edit player number.
             case '2':
             {
                  printf("\n\nPlease enter new player number: ");
                  fflush(stdin); scanf("%d", &NewInputNumber);
                  
                  singlemember.Number = NewInputNumber;
                  
                  printf("\nNumber has been successfully changed to: %d! Press any key to continue. . .", NewInputNumber);
             }
             break;
             
             // Edit player mobile phone number.
             case '3':
             {
                  printf("\n\nPlease enter new player mobile phone number: ");
                  fflush(stdin); scanf("%ld", &NewInputTelNo);
                  
                  singlemember.TelNo = NewInputTelNo;
                  
                  printf("\nMobile number has been successfully changed to: %ld! Press any key to continue. . .", NewInputTelNo);              
             }
             break;
             
             default:
             {
                  printf("ERROR: Wrong option!");
                  return 1;
             }
             break;             
        }
        fseek(team_file, (PlayerNo - 1) * sizeof(struct Members), SEEK_SET);
        fwrite(&singlemember, sizeof(struct Members), 1, team_file);
        fclose(team_file);
    }
    while(answer != 'X');
    return 0;
}

// ---------------------------
// -> NECESSARY to ask user to ask for file paths of the teams. Could be done more user-friendly way, not mentioned to be edited by me anymore.
void PromptUserForFilePaths(void)
{    
    // Local variables.    
    int count = 0;    
    char answer;

    while(count != 2)    
    {        
        clrscr();        
        switch(count)        
        {            
            // Prompt for BATTING team file path.            
            case 0:            
            {
                /*int i;      
                for(i = 0; i != 16; i++)
                {
                      printf("[Format: Disk:\\Folder\\FileName] Please enter BATTING team file location below: \n");
                      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i); 
                }*/
                      
                printf("[Format: Disk:\\Folder\\FileName]\nPlease enter BATTING team file location below: ");                
                fflush(stdin); scanf("%s", file_path);
                strcat(file_path, ".ini");
                strcpy(batt_path, file_path);
                break;            
            }
                              
            // Prompt for FIELDING team file path.            
            case 1:            
            {                
                printf("[Format: Disk:\\Folder\\FileName]\nPlease enter FIELDING team file location below: ");                
                fflush(stdin); scanf("%s", file_path);
                strcat(file_path, ".ini");                       
                strcpy(fiel_path, file_path);                
                break;            
            }        
        }            

        // Open each file for reading binary.        
        team_file = fopen(file_path, "rb");                      

        // If file does exists in the given location.        
        if(team_file)        
        {            
            count += 1;            
            printf("\nFile is already created there!\nPress any key to continue. . .");            
            getch();        
        }                

        else        
        {                     
            // Prompt user to create file in the given location.            
            printf("\nERROR: That file doesn't exists!\nCreate a new file in that location (Y/N)?");            
            answer = toupper(getch());                        

            // Check, which option user chosen from prompt above.            
            switch(answer)            
            {                
               case 'Y':                
               {                         
                   team_file = fopen(file_path, "wb");
                   printf("\n\nCreating file. . .\nFile created successfully! Press any key to continue. . .");
                   fclose(team_file);
                   count += 1;
                   getch();
                   break;
               }                                 

               case 'N':                
               {                     
                   char team_name[8];                     
                   if(!count)strcpy(team_name, "BATTING");                     
                   else strcpy(team_name, "FIELDING");                                          
                   printf("\n\nPress any key, to type %s team file location again. . .", team_name);                     
                   getch();                    
                   break;                
               }            
            }        
        }
    }
}
