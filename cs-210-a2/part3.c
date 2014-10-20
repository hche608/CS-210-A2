//
//  main.c
//  For Part1 - Part4
//
//  Created by Hao Chen on 19/09/14.
//  Copyright (c) 2014 Hao Chen. All rights reserved.
//

#include<stdio.h>
#include<stdbool.h>
#include<string.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int reader[6];
    int num;
    int count=0;
    int opcode = 0;
    int temp1, temp2,r1,r2,r3 = 0;
    fp = fopen(argv[1],"r");
    char c[6];
    char input;
    int a1,b1,c1,d1 = 0;
    input=fgetc(fp);
    memset(c, 0, 6);
    memset(reader, 0, 6);
    while(input!= EOF)
    {
        c[count] = input;
        //printf("%d\n",count);
        //printf("%d\n",input);
        if (input>=48 && input <= 57){
            reader[count] = input - 48;
        }
        if (input >=97 && input <= 102){
            reader[count] = input - 87;
        }
        count ++;
        if (count == 4){
            a1 = reader[0];
            b1 = reader[1];
            c1 = reader[2];
            d1 = reader[3];
            //printf("%d\n",a1);
            num = ((a1*16+b1)*16+c1)*16+d1;
            //printf("%x\n",num);
            
            
            opcode=num >>12;
            if(opcode==0x0001)
            {
                temp1=num >> 9;
                r1 = temp1 % 8;
                temp2=num >> 6;
                r2 = temp2 % 8;
                opcode=num >>5;
                if (opcode%2==0) {
                    r3=num % 8;
                    printf("add r%d, r%d r%d\n",r1,r2,r3);
                } else {
                    temp1 = (num >>4)%2;
                    r3=(num % 16) - (temp1*16);
                    printf("add r%d, r%d #%d\n",r1,r2,r3);
                    
                }
                
            }
            if(opcode==0x0005)
            {
                temp1=num >> 9;
                r1 = temp1 % 8;
                temp2=num >> 6;
                r2 = temp2 % 8;
                opcode=num >>5;
                if (opcode%2==0) {
                    r3=num % 8;
                    printf("and r%d, r%d r%d\n",r1,r2,r3);
                } else {
                    temp1 = (num >>4)%2;
                    r3=(num % 16) - (temp1*16);
                    printf("and r%d, r%d #%d\n",r1,r2,r3);
                    
                }
            }
        }
        if (count >= 5){
            count = 0;
        }
        input=fgetc(fp);
    }
    fclose(fp);
    return 0;
}

