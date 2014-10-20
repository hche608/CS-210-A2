//
//  main.c
//  For Part1 - Part4
//
//  Created by Hao Chen on 19/09/14.
//  Copyright (c) 2014 Hao Chen. All rights reserved.
//

#include <stdio.h>

int hexToDecimal(const char *);
int power(int,int);

void addFunction( int );
void andFunction( int );
void jmpFunction( int );
void brFunction( int );

static int PC_int_Address;
static int pcCounter = 0;

int debug = 0;
//void createOBJ( const char * );
void instruction_detector( const char * );
void setPCAddress( const char * );

int main(int argc, const char * argv[]) {
    if (argc == 1) {
        printf("Error, need at least one arugs!\n[complete file name] or\n[complete file name] [an integer]\n");
    } else if (argc < 4){
        if (debug == 1){
            printf("arg is: %s \n", argv[1]);
            //createOBJ(argv[1]);
        }
        if (argc > 2) {
            setPCAddress( argv[2] ); //read hex value;
        }
        instruction_detector( argv[1] );
        printf("Done!\n");
    } else {
        printf("Error! Too many arugs, only take at most two arugs!\n[argu1] or\n[argu1] [argu2]\n");
    }
    return 0;
}


// set PC address
void setPCAddress( const char *argu ){
    if (debug == 1)
        printf("loading address is [0x%s]\n", argu);
    
    PC_int_Address = hexToDecimal(argu);
    
    if (debug == 1) {
        printf("address in Deciaml is %i\n", PC_int_Address);
        printf("address in Hex is 0x%x\n", PC_int_Address);
    }

}
/*
//create a file name as argv[1]
void createOBJ( const char *argu)
{
    
    FILE * fp;
    
    fp = fopen (argu, "w+");
    
    fprintf(fp, "%s\n", "1283");
    fprintf(fp, "%s\n", "5105");
    fprintf(fp, "%s\n", "0ffd");
    fprintf(fp, "%s\n", "0802");
    fprintf(fp, "%s\n", "1df7");
    fprintf(fp, "%s\n", "506f");
    fprintf(fp, "%s\n", "c080");
    fclose(fp);
    //end create a file
}
*/

//identify instructions
void instruction_detector( const char *argu)
{
    
    char hexCode[4];
    
    FILE *file;
    file = fopen(argu, "r");
    
    if(file == NULL) //if file does not exist, create it
    {
        printf("Error, File does not exist!\n");
    } else {
        while
            (fscanf(file, "%s", hexCode)!= EOF){
                pcCounter +=1;
                if (debug == 1){
                    printf("pcCount is %d in while is 0x%x!\n", pcCounter, pcCounter + PC_int_Address);
                }
                int num = hexToDecimal(hexCode);
                int opcode = num >> 12;
                switch (opcode) {
                    case 0x0000:
                        if (debug == 1) {
                            printf("instruction is %s and 2nd argu is %d!\n", hexCode, pcCounter);
                            printf("brStarter is %d!!\n", pcCounter);
                        }
                        brFunction(num);
                        break;
                    case 0x0001:
                        if (debug == 1)
                            printf("instruction is %s !\n", hexCode);
                        addFunction(num);
                        break;
                    case 0x0005:
                        if (debug == 1)
                            printf("instruction is %s !\n", hexCode);
                        andFunction(num);
                        break;
                    case 0x000C:
                        if (debug == 1)
                            printf("instruction is %s !\n", hexCode);
                        jmpFunction(num);
                        break;
                        
                    default:
                        pcCounter -=1;
                        printf("Error, The input value is %s, it is not valid!\n", hexCode);
                        break;
                }
            }
        
        fclose(file);
    }
}


// ADD section
void addFunction( int num )
{
    int opcode,r1,r2,r3 = 0;
    
    opcode = num >> 9;
    r1 = opcode % 8;
    opcode = num >> 6;
    r2 = opcode % 8;
    if ((num >> 5) % 2 == 0) {
        r3 = num % 8;
        printf("add r%d, r%d r%d\n",r1,r2,r3);
    } else {
        r3 = (num % 16) - (((num >> 4) % 2) * 16);
        printf("add r%d, r%d #%d\n",r1,r2,r3);
    }
}
// end ADD

// AND Section

void andFunction( int num )
{
    int opcode,r1,r2,r3 = 0;
    
    opcode = num >> 9;
    r1 = opcode % 8;
    opcode = num >> 6;
    r2 = opcode % 8;
    if ((num >> 5) % 2 == 0) {
        r3 = num % 8;
        printf("and r%d, r%d r%d\n",r1,r2,r3);
    } else {
        r3 = (num % 16) - (((num >> 4) % 2) * 16);
        printf("and r%d, r%d #%d\n",r1,r2,r3);
    }
}
// end AND

// JMP Section
void jmpFunction( int num )
{
    int opcode = (num >> 6) % 8;
    if (opcode == 7) {
        printf("%s", "ret");
    } else {
        printf("jmp r%d\n" , opcode);
    }
}
// end JMP


// BR Section
void brFunction( int num )
{
    int currentPCPoint = 0;
    
    printf("br");
    if ((num >> 11) % 2 == 1) {
        printf("n");
    }
    
    if ((num >> 10) % 2 == 1) {
        printf("z");
    }
    
    if ((num >> 9) % 2 == 1) {
        printf("p");
    }
    currentPCPoint = ((num + pcCounter) % 512);

    printf(" 0x%X\n", PC_int_Address + currentPCPoint );
}
// end BR


/*  a hex number to decimal number converter
 *
 *
 *
 *  @param      char * pointer of char[]
 *
 *  @return     int
 *
 *
 *
 */

int hexToDecimal(const char * hex)   /* Function to convert hexadecimal to decimal. */
{
    int i, length, sum = 0;
    for(length = 0; hex[length] != '\0'; ++length);
    for(i = 0; hex[i] != '\0'; ++i, --length)
    {
        if(hex[i] >= '0' && hex[i] <= '9')
            sum += (hex[i] - '0') * power(16,length-1);
        if(hex[i] >= 'A' && hex[i] <= 'F')
            sum += (hex[i] - 55) * power(16,length-1);
        if(hex[i] >= 'a' && hex[i] <= 'f')
            sum += (hex[i] - 87) * power(16,length-1);
    }
    return sum;
}

/*  decimal numbers to a bit hex number converter
 *  valid deicmal integer is 0 <= integer <= 65536
 *
 *
 *  @param      int     base number
 *  @param      int     power factor (valid value >= 0)
 *
 *  @return     int     result = x^y
 *
 *
 *
 */

int power(int num1, int num2){
    int result;
    if (num2 < 0){
        printf("Error, the power factor is %d. It is invalid!\n", num2);
    } else if(num2 == 0) {
        result = 1;
    } else {
        int i;
        result = 1;
        for (i = 0; i < num2; i++) {
            result *= num1;
        }
    }
    return result;
}