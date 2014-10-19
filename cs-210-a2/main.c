//
//  main.c
//  For Part1 - Part4
//
//  Created by Hao Chen on 19/09/14.
//  Copyright (c) 2014 Hao Chen. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX
#include <stdlib.h>  // for strtol



int * hexToBinary( char c ); //return an integer array
int hexToDecimal(const char *);

int binaryToDecimal( int, int *, int );
char * decimalToHex( int );

int * decimalToBinary( int );

int addBinaryAndInt( const int * , int , int);

int power(int,int);

void addFunction( char * );
void andFunction( char * );
void jmpFunction( char * );
void brFunction( char * );

static int PCintAddress;
static int pcCounter = 0;


int debug = 0;
void createOBJ( const char * );
void instructions( const char * );
void setPCAddress( const char * );




int main(int argc, const char * argv[]) {
    // insert code here...
    if (argc == 1) {
        printf("Error, need at least one arugs!\n[complete file name] or\n[complete file name] [an integer]\n");

    } else if (argc < 4){
        if (debug == 1){
            printf("arg is: %s \n", argv[1]);
            createOBJ(argv[1]);
        }
        if (argc > 2) {

            setPCAddress( argv[2] ); //read hex value;
            
        }
        instructions( argv[1] );
        
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
    
    PCintAddress = hexToDecimal(argu);
    //PCintAddress = binaryToDecimal(16,pcStarter,1);
    
    if (debug == 1) {
        printf("address in Deciaml is %i\n", PCintAddress);
        
        printf("address in Hex is 0x%x\n", PCintAddress);
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
void instructions( const char *argu)
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
                    /*
                     int i;
                     printf("\[%d]address is [",pcCounter);
                     for (i = 0; i < 15; i++) {
                     //partOfaddress[i] = *(pcStarter(7 + i));
                     printf("%d",pcStarter[i]);
                     }
                     printf("]\n");
                     */
                    printf("pcCount is %d in while is 0x%x!\n", pcCounter, pcCounter + PCintAddress);
                }
                switch (hexCode[0]) {
                    case '0':
                        if (debug == 1) {
                            printf("hexCode is %s and 2nd argu is %d!\n", hexCode, pcCounter);
                            printf("brStarter is %d!!\n", pcCounter);
                        }
                        brFunction(hexCode);
                        break;
                    case '1':
                        if (debug == 1)
                            printf("hexCode is %s !\n", hexCode);
                        addFunction(hexCode);
                        break;
                    case '2':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case '3':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case '4':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case '5':
                        if (debug == 1)
                            printf("hexCode is %s !\n", hexCode);
                        andFunction(hexCode);
                        break;
                    case '6':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case '7':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case '8':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case '9':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case 'A':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case 'a':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case 'B':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case 'b':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case 'C':
                        if (debug == 1)
                            printf("hexCode is %s !\n", hexCode);
                        jmpFunction(hexCode);
                        break;
                    case 'c':
                        if (debug == 1)
                            printf("hexCode is %s !\n", hexCode);
                        jmpFunction(hexCode);
                        break;
                    case 'D':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case 'd':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case 'E':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case 'e':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case 'F':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
                        break;
                    case 'f':
                        printf("hexCode[0] is %c !\n", hexCode[0]);
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
void addFunction( char *addressOfchars)
{
    int *c;
    int binNums[3];
    int r1,r2,r3,imm5 = 0;

    c = hexToBinary(*(addressOfchars + 1));
    binNums[0] = *(c);
    binNums[1] = *(c + 1);
    binNums[2] = *(c + 2);
    r1 = binaryToDecimal(3, binNums, 1);
    
    binNums[0] = *(c + 3);
    c = hexToBinary(*(addressOfchars + 2));
    binNums[1] = *(c);
    binNums[2] = *(c + 1);
    r2 = binaryToDecimal(3, binNums, 1);
    if (*(c + 2) == 0) {
        c = hexToBinary(*(addressOfchars + 3));
        binNums[0] = *(c + 1);
        binNums[1] = *(c + 2);
        binNums[2] = *(c + 3);
        r3 = binaryToDecimal(3, binNums, 1);
        
        printf("%s r%d, r%d, r%d\n", "add", r1 , r2, r3);
    } else {
        int binImm5Num[5];
        binImm5Num[0] = *(c + 3);
        c = hexToBinary(*(addressOfchars + 3));
        binImm5Num[1] = *(c);
        binImm5Num[2] = *(c + 1);
        binImm5Num[3] = *(c + 2);
        binImm5Num[4] = *(c + 3);
        imm5 = binaryToDecimal(5, binImm5Num,0);
        printf("%s r%d, r%d, #%d\n", "add", r1 , r2, imm5);
    }
}
// end ADD

// AND Section

void andFunction( char *addressOfchars)
{
    
    int *c;
    int binNums[3];
    int r1,r2,r3,imm5 = 0;
    
    c = hexToBinary(*(addressOfchars + 1));
    binNums[0] = *(c);
    binNums[1] = *(c + 1);
    binNums[2] = *(c + 2);
    r1 = binaryToDecimal(3, binNums, 1);
    
    binNums[0] = *(c + 3);
    c = hexToBinary(*(addressOfchars + 2));
    binNums[1] = *(c);
    binNums[2] = *(c + 1);
    r2 = binaryToDecimal(3, binNums, 1);
    if (*(c + 2) == 0) {
        c = hexToBinary(*(addressOfchars + 3));
        binNums[0] = *(c + 1);
        binNums[1] = *(c + 2);
        binNums[2] = *(c + 3);
        r3 = binaryToDecimal(3, binNums, 1);
        
        printf("%s r%d, r%d, r%d\n", "and", r1 , r2, r3);
    } else {
        int binImm5Num[5];
        binImm5Num[0] = *(c + 3);
        c = hexToBinary(*(addressOfchars + 3));
        binImm5Num[1] = *(c);
        binImm5Num[2] = *(c + 1);
        binImm5Num[3] = *(c + 2);
        binImm5Num[4] = *(c + 3);
        imm5 = binaryToDecimal(5, binImm5Num,0);
        printf("%s r%d, r%d, #%d\n", "and", r1 , r2, imm5);
    }
}
// end AND

// JMP Section

void jmpFunction( char *addressOfchars)
{
    int *c;
    int binNums[3], binNums2[6];;
    int r1, r2, r3;
    
    //check 000
    c = hexToBinary(*(addressOfchars + 1));
    binNums[0] = *(c);
    binNums[1] = *(c + 1);
    binNums[2] = *(c + 2);
    r1 = binaryToDecimal(3, binNums, 1);
    
    //get register
    binNums[0] = *(c + 3);
    c = hexToBinary(*(addressOfchars + 2));
    binNums[1] = *(c);
    binNums[2] = *(c + 1);
    r2 = binaryToDecimal(3, binNums, 1);

    //check 000000
    binNums2[0] = *(c + 2);
    binNums2[1] = *(c + 3);
    c = hexToBinary(*(addressOfchars + 3));
    binNums2[2] = *(c);
    binNums2[3] = *(c + 1);
    binNums2[4] = *(c + 2);
    binNums2[5] = *(c + 3);
    r3 = binaryToDecimal(6, binNums2, 1);
    
    if (debug == 1){
        printf("jmp messages! r1=%d r2=%d r3=%d\n", r1, r2, r3 );
    }
    if ((r1 + r3) == 0) {
        if (r2 == 7) {
            printf("%s", "ret");
        } else {
            printf("jmp r%d\n" , r2);
        }
    } else {
        printf("Error, jmp error!\n");
    }
}
// end JMP


// BR Section

void brFunction( char *addressOfchars )
{
    if (debug == 1){
        printf("in BRFunction 2nd argu is :%d!\n", pcCounter);
    }
    int *c;
    int binNums[9];
    //int r1, r2, r3;
    
    //check n == 0, z == 0, p == 0
    printf("br");
    c = hexToBinary(*(addressOfchars + 1));
    if (*(c) == 1)
        printf("n");
    if (*(c + 1) == 1)
        printf("z");
    if (*(c + 2) == 1)
        printf("p");
    
    if (debug == 1)
        printf(" 0x%X", PCintAddress);

        //get 9bits PCoffset9
        binNums[0] = *(c + 3);
        c = hexToBinary(*(addressOfchars + 2));
        binNums[1] = *(c);
        binNums[2] = *(c + 1);
        binNums[3] = *(c + 2);
        binNums[4] = *(c + 3);
        c = hexToBinary(*(addressOfchars + 3));
        binNums[5] = *(c);
        binNums[6] = *(c + 1);
        binNums[7] = *(c + 2);
        binNums[8] = *(c + 3);
    
    
    
    int currentPCPoint = addBinaryAndInt(binNums , pcCounter, 9);
    if(debug == 1)
        printf(" Deciaml is %d\n", currentPCPoint);
    printf(" 0x%X\n", PCintAddress + currentPCPoint);
}
// end BR


/*  add two binary numbers and return a binary number
 *
 *
 *
 *  @param      int *       pointer of int[] (1st binary number)
 *  @param      int         int (2nd integer number)
 *  @param      int         length of the binary number need to add
 *
 *  @return     int         add a binary number and an integer (the result)
 *
 *
 *
 */

int addBinaryAndInt( const int *num1 , int num2 , int bits){
    int * num3 = decimalToBinary(num2);
    if (debug == 1){
        printf("\nInteger to binary [%d]", *(num3+14));
        printf("\nadd two binary numbers: 2nd integer is %d\n[",num2);
    }
    int result[bits];
    
    int i, c = 0;
    static int resultInt;


    if (debug == 1){
        for (i = 0; i < bits; i++) {
            printf("%d", num1[i]);
        }
        printf("]\n[");
    
        for (i = 0; i < bits; i++) {
            printf("%d", *(num3+i+7));
        }
        printf("]\n[");
    }
    
    for (i = (bits - 1); i >= 0; i--) {
        result[i] = (num1[i] ^ *(num3+i+7) ^ c); //a xor b xor c
        c = ((num1[i] & *(num3+i+7)) | (num1[i] &c)) | (*(num3+i+7) & c); //ab+bc+ca
    }
    
    if (debug == 1){
        //printf("\n[");
        for (i = 0; i < bits; i++) {
            printf("%d", result[i]);
        }
        printf("]\n");
    }
    
    resultInt = binaryToDecimal(bits, result, 1 );
    
    
    return resultInt;

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
    } else if(num2 ==0) {
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

/*  decimal numbers to a bit hex number converter
 *  valid deicmal integer is 0 <= integer <= 65536
 *
 *
 *  @param      int
 *
 *  @return     char *      a pointer of char[5], char[5] = '\0'
 *                          the return value is able to convert to string.
 *
 *
 */

char * decimalToHex( int n ) /* Function to convert decimal to hexadecimal. */
{
    printf("decToHex input value is %d!\n", n);
    char hex[5];
    int i = 0, rem;
    while (n != 0)
    {
        rem = n % 16;
        switch (rem)
        {
            case 10:
                hex[i]='A';
                break;
            case 11:
                hex[i]='B';
                break;
            case 12:
                hex[i]='C';
                break;
            case 13:
                hex[i]='D';
                break;
            case 14:
                hex[i]='E';
                break;
            case 15:
                hex[i]='F';
                break;
            default:
                hex[i]=rem+'0';
                break;
        }
        ++i;
        n /= 16;
    }
    hex[i] = '\0';
    printf("HEX value is: %s!\n", hex);
    //strrev(hex);   /* Reverse string */
    static char result[5];
    result[0] = hex[3];
    result[1] = hex[2];
    result[2] = hex[1];
    result[3] = hex[0];
    result[4] = '\0';
    printf("after reverse HEX value is: %s!\n", result);
    
    return result;
}

/*  binary number to decimal number converter with 3 params
 *
 *
 *
 *  @param      int     length of the binary number
 *  @param      int * = a pointer of int[]
 *  @param      int     Unsign binary number or Sign binary number
 *
 *  @return     int
 *
 *
 *
 */

int binaryToDecimal(int length, int *addressOfIntegers, int unsignBin)
{
    if (debug == 1) {
        printf("bin To Dec bin [%dbits] are: [", length);
        int i;
		for (i = 0; i < length; i++) {
            printf("%d", *(addressOfIntegers + i));
        }
        printf("]\n");
    }
    int result = 0;
    if (unsignBin == 1) {
		int i;
        for (i = 0; i < length; i++) {
            result += *(addressOfIntegers + i) * power(2, (length - i - 1));
            if (debug == 1)
                printf("Test value is: %d\n", result);
        }
        if (debug == 1)
            printf("[U]bin To Dec decimal is: %d\n\n", result);
    } else {
		int i;
        for (i = 1; i < length; i++) {
            if ((length - i - 1) >= 0) {
                result += power(2, (length - i - 1)) * *(addressOfIntegers + i);
                //result = length - i - 1;
                //result = *(addressOfIntegers + i);
                if (debug == 1)
                    printf("bin To Dec decimal is: %d\n", result);
            }
        }
        result = result - *(addressOfIntegers) * power(2, (length - 1));
        if (debug == 1)
            printf("[S]bin To Dec decimal is: %d\n\n", result);
    }
    
    return result;
    
}

/*  a decimal number to  binary number converter
 *
 *
 *
 *  @param      int
 *
 *  @return     int[]  =   a pointer of int[16] 16bits
 *
 *
 *
 */

int * decimalToBinary(int n)
{
    if(debug == 1)
        printf("\ndecimalToBinary'%d':\n[",n);
    int c, rem, count = 0;
    static int pointer[16];
    int temp[16];
    
    for (c = 0; c < 16; c++) {
        pointer[c] = 0;
        temp[c] = 0;
    }
    
    while (n >= 0) {
        if(n == 0){
            temp[count] = 0;
            count++;
            temp[count] = 0;
            break;
        } else if (n == 1){
            temp[count] = 1;
            break;
        } else if (n == 2) {
            temp[count] = 0;
            count++;
            temp[count] = 1;
            break;
        } else {
            rem = n % 2;
            temp[count] = rem;
            n /= 2;
            count++;
        }
    }
    for (c = 0; c < 16; c++) {
        pointer[c] = temp[15 - c];
        if (debug == 1)
            printf("%d",pointer[c]);
    }
    if (debug == 1)
        printf("]");
    return  pointer;
}

/*  a bit hex to 4 bit binary number converter
 *
 *
 *
 *  @param      char
 *
 *  @return     int[4]  =   a pointer of int[]
 *
 *
 *
 */

int * hexToBinary(char c)
{
    if (debug == 1) {
        printf("hex To bin -- char is: %c\n", c);
    }
    static int binComb[4];
    switch (c) {
        case '0':
            binComb[0] = 0;
            binComb[1] = 0;
            binComb[2] = 0;
            binComb[3] = 0;
            break;
        case '1':
            binComb[0] = 0;
            binComb[1] = 0;
            binComb[2] = 0;
            binComb[3] = 1;
            break;
        case '2':
            binComb[0] = 0;
            binComb[1] = 0;
            binComb[2] = 1;
            binComb[3] = 0;
            break;
        case '3':
            binComb[0] = 0;
            binComb[1] = 0;
            binComb[2] = 1;
            binComb[3] = 1;
            break;
        case '4':
            binComb[0] = 0;
            binComb[1] = 1;
            binComb[2] = 0;
            binComb[3] = 0;
            break;
        case '5':
            binComb[0] = 0;
            binComb[1] = 1;
            binComb[2] = 0;
            binComb[3] = 1;
            break;
        case '6':
            binComb[0] = 0;
            binComb[1] = 1;
            binComb[2] = 1;
            binComb[3] = 0;
            break;
        case '7':
            binComb[0] = 0;
            binComb[1] = 1;
            binComb[2] = 1;
            binComb[3] = 1;
            break;
        case '8':
            binComb[0] = 1;
            binComb[1] = 0;
            binComb[2] = 0;
            binComb[3] = 0;
            break;
        case '9':
            binComb[0] = 1;
            binComb[1] = 0;
            binComb[2] = 0;
            binComb[3] = 1;
            break;
        case 'A':
            binComb[0] = 1;
            binComb[1] = 0;
            binComb[2] = 1;
            binComb[3] = 0;
            break;
        case 'a':
            binComb[0] = 1;
            binComb[1] = 0;
            binComb[2] = 1;
            binComb[3] = 0;
            break;
        case 'B':
            binComb[0] = 1;
            binComb[1] = 0;
            binComb[2] = 1;
            binComb[3] = 1;
            break;
        case 'b':
            binComb[0] = 1;
            binComb[1] = 0;
            binComb[2] = 1;
            binComb[3] = 1;
            break;
        case 'C':
            binComb[0] = 1;
            binComb[1] = 1;
            binComb[2] = 0;
            binComb[3] = 0;
            break;
        case 'c':
            binComb[0] = 1;
            binComb[1] = 1;
            binComb[2] = 0;
            binComb[3] = 0;
            break;
        case 'D':
            binComb[0] = 1;
            binComb[1] = 1;
            binComb[2] = 0;
            binComb[3] = 1;
            break;
        case 'd':
            binComb[0] = 1;
            binComb[1] = 1;
            binComb[2] = 0;
            binComb[3] = 1;
            break;
        case 'E':
            binComb[0] = 1;
            binComb[1] = 1;
            binComb[2] = 1;
            binComb[3] = 0;
            break;
        case 'e':
            binComb[0] = 1;
            binComb[1] = 1;
            binComb[2] = 1;
            binComb[3] = 0;
            break;
        case 'F':
            binComb[0] = 1;
            binComb[1] = 1;
            binComb[2] = 1;
            binComb[3] = 1;
            break;
        case 'f':
            binComb[0] = 1;
            binComb[1] = 1;
            binComb[2] = 1;
            binComb[3] = 1;
            break;
            
        default:
            printf("Error, the input value in hexToBin is %c!\n", c);
            break;
    }
    if (debug == 1)
        printf("hex To bin int[] is: [%d %d %d %d]\n", binComb[0],binComb[1],binComb[2],binComb[3]);
    
    return binComb;
}

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
    int i, length, sum=0;
    for(length=0; hex[length]!='\0'; ++length);
    for(i=0; hex[i]!='\0'; ++i, --length)
    {
        if(hex[i]>='0' && hex[i]<='9')
            sum+=(hex[i]-'0')*power(16,length-1);
        if(hex[i]>='A' && hex[i]<='F')
            sum+=(hex[i]-55)*power(16,length-1);
        if(hex[i]>='a' && hex[i]<='f')
            sum+=(hex[i]-87)*power(16,length-1);
    }
    return sum;
}