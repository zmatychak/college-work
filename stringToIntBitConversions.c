/*
    ZEN MATYCHAK
    PART ONE DONE- CONVERTING DATA TYPES
    Number converter
    UP TO 8 HEX CHARS TOTAL

    Menu
    Convert between integer, binary, octal and hexadecimal

    This program should accept numeric values in hexadecimal,
    decimal, octal and binary formats as:

        Hex 0x0 to 0xFFFFFFFF
        Dec 0 to 4294967295
        Oct o0 to o37777777777
        Bin b0 to b11111111111111111111111111111111

    After a value is input the code in main will interpret the
    data types above an process the conversion to an unsigned
    int.  The unsigned int will be used to convert the input to
    strings containing hexadecimal, octal and binary strings.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//int input_to_decimal(char *input);
unsigned int bin_to_uint(char *input);
unsigned int oct_to_uint(char *input);
unsigned int hex_to_uint(char *input);
unsigned int dec_to_uint(char *input);
void uint_to_hex(unsigned int n, char *output);
void uint_to_oct(unsigned int n, char *output);
void uint_to_bin(unsigned int n, char *output);


int error = 0;


int main(){
    char input[50];
    unsigned int n = 0;
    char output[50];

    // Write code here to test your functions
    // Uncomment code below when done

    printf("Enter a binary, octal, decimal or hexadecimal number\n");
    printf("convert > ");
    gets(input);
    //scanf("%s", &input);
    // Detect input data type
    // Hexadecimal
    if(input[0] == '0' && input[1] == 'x'){
        puts("Hex Value Registered");
        n = hex_to_uint(input);
    }
    // Decimal
    else if(input[0] >= '0' && input[0] <= '9'){
        n = dec_to_uint(input);
    }
    // Octal
    else if(input[0] == 'o'){
        n = oct_to_uint(input);
    }
    // Binary
    else if(input[0] == 'b'){
        n = bin_to_uint(input);
    }
    // Unknown
    else{
        printf("ERROR: Unknown data type: %s\n", input);
    }

    // Print results
    printf("The decimal value of %s is %u\n", input, n);
    uint_to_hex(n, output);
    printf("The hexadecimal value of %s is %s\n", input, output);
    uint_to_oct(n, output);
    printf("The octal value of %s is %s\n", input, output);
    uint_to_bin(n, output);
    printf("The binary value of %s is %s\n", input, output);

    return 0;
}

// Convert a hexadecimal char array to uint
unsigned int hex_to_uint(char *input){  //works
    // Declare result and set to zero
    unsigned int res = 0;
    // Declare and set multiplier to 1
    int multiplier=1;
    // Declare iterator
    int stringLen=strlen(input);
    int i=stringLen-1;            //START AFTER 0X
    char loopInput[stringLen];
    strcpy(loopInput,input);
    puts(loopInput);
    // Loop through value part of input string

        // If between 0 and 9 add 0 to 9 to res with multiplier 48-57

        // If between A and F add 10 to 15 to res with multiplier 65-70

        // Error - exit

        // Advance multiplier to next position value
        while(loopInput[i]!='\0'&&(loopInput[i]!='x')) {
            if (loopInput[i] >= 48 && (loopInput[i] <= 57))
                res = res + (loopInput[i] - '0') * multiplier;
            else if (loopInput[i] >= 65 && (loopInput[i] <= 70))
            res = res + ((loopInput[i] - 65) + 10) * multiplier; //17 IS THE DIFFERENCE FROM A to 1 on ASCII TABLE
            else {puts("INVALID NUMBER HEX"); exit(1);}

            multiplier*=16;
            i=i-1;
        }
    return res;
}


/*
    Copy hex_to_uint() and modify for decimal input.
*/
// Convert a unsigned integer char array to uint
unsigned int dec_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    // Declare and set multiplier to 1
    int multiplier=1;
    // Declare iterator
    int stringLen=strlen(input);
    int i=stringLen-1;            //START AT 0

    while(input[i]!='\0')
    {
        if(input[i]>=48&&input[i]<=57)
            res=res+(input[i]-'0')*multiplier;
        else {puts("INVALID NUMBER DEC"); exit(2);}

        multiplier*=10;
        i=i-1;
    }

    return res;
}


/*
    Copy dec_to_uint() and modify for octal input.
*/
// Convert a octal char array to uint
unsigned int oct_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    // Declare and set multiplier to 1
    int multiplier=1;
    // Declare iterator
    int stringLen=strlen(input);
    int i=stringLen-1;            //START AT 0

    while(input[i]!='\0'&&input[i]!='o')
    {
        if(input[i]>=48&&input[i]<=56)      //up to and including '8'
            res=res+(input[i]-'0')*multiplier;
        else {puts("INVALID NUMBER OCT"); exit(3);}

        multiplier*=8;
        i=i-1;
    }

    return res;
}


/*
    Copy oct_to_uint() and modify for binary input.
*/
// Convert a binary char array to unsigned int
unsigned int bin_to_uint(char *input){
    // Declare result and set to zero
    unsigned int res = 0;
    // Declare and set multiplier to 1
    int multiplier=1;
    // Declare iterator
    int stringLen=strlen(input);
    int i=stringLen-1;            //START AT 0

    while(&input[i]!=NULL&&input[i]!='o')
    {
        if(input[i]>=48&&input[i]<=49)      //up to and including '0'-'1'
            res=res+(input[i]-'0')*multiplier;
        else {puts("INVALID NUMBER OCT"); exit(3);}

        multiplier*=2;
        i=i-1;
    }

    return res;
}


/*
    This function converts from unsigned int to a hex
    char array.  Try this on paper before coding.
*/
// Convert a unsigned integer char array to hexadecimal
void uint_to_hex(unsigned int n, char *output){
    // Declare a uint for remainder
    unsigned int rem=0;
    // Declare an int for division
    int div;
    // Declare a char array buffer
    char buffer[50];
    // Use a loop to generate a hex string - string will be reverse
    int i=0;
    while(n!=0)
    {
        rem=n%16;
        n=n/16;
        if(rem>9&&rem<16)
        {
            buffer[i]=rem+55;
        }
        else
            buffer[i]=rem+48;
        i+=1;
    }
    buffer[i]='\0';
    strcpy(output,"0x");
    strrev(buffer);
    strcat(output,buffer);
    // Get last hex char

    // Put null at end of buffer

    // Copy 0x to output string

    // Copy chars from buffer in reverse order to output string

    return;
}


/*
    Copy uint_to_hex() and modify for octal
*/
// Convert a unsigned integer char array to octal
void uint_to_oct(unsigned int n, char *output){
    // Declare a uint for remainder
    unsigned int rem=0;
    // Declare an int for division
    int div;
    // Declare a char array buffer
    char buffer[50];
    // Use a loop to generate a hex string - string will be reverse
    int i=0;
    while(n!=0)
    {
        rem=n%8;
        n=n/8;
        if(rem<9)
        {
            buffer[i]=rem+48;
        }
        else
            exit(3);
        i+=1;
    }
    buffer[i]='\0';
    strcpy(output,"o");
    strrev(buffer);
    strcat(output,buffer);
    return;
}


/*
    Copy uint_to_oct() and modify for binary
*/
// Convert a unsigned integer char array to binary
void uint_to_bin(unsigned int n, char *output){
    // Declare a uint for remainder
    unsigned int rem=0;
    // Declare an int for division
    int div;
    // Declare a char array buffer
    char buffer[50];
    // Use a loop to generate a hex string - string will be reverse
    int i=0;
    while(n!=0)
    {
        rem=n%2;
        n=n/2;
        if(rem<2)
        {
            buffer[i]=rem+48;
        }
        else
            exit(4);
        i+=1;
    }
    buffer[i]='\0';
    strcpy(output,"b");
    strrev(buffer);
    strcat(output,buffer);
    return;
}

