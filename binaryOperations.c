/*
    ZENON MATYCHAK
    LAB 5
    PART 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Prototypes
int _add(int a, int b);
int add(int a, int b);
int sub(int a, int b);
int neg(int a);
int mul(int a, int b);
int division(int a, int b);
int mod(int a, int b);
int power(int a, int b);
int convert(char *input);
void menuu();

int error = 0;
// Main
int main(int argc, char *argv[]){

    int res = 0;        // Cumulative result - running total
    int n = 0;          // For number conversion from input string
    char input[50];     // Input string
    input[0] = '\0';    // Put null in operator char so loop works

    // Write code here to test your functions
    // Uncomment code below when done

    int a=4;
    int b=-5;
    printf("Add %d + %d = %d\n",a,b,add(a,b));
    printf("Sub %d - %d = %d\n",a,b,sub(a,b));
    printf("Neg %d = %d\n",a,neg(a));
    printf("Multiply %d * %d = %d\n",a,b,mul(a,b));
    printf("Divide %d / %d = %d\n",20,-5,division(20,-5));
    printf("MOD %d %% %d = %d\n",5,20,mod(5,6));
    printf("%d ^ %d = %d\n",a,b,power(a,b));
    //
    printf("Convert = %d",convert("  1023"));
    // Loop until quit is selected

    while(input[0] != 'q' && input[0] != 'Q'){
        // Show menu choices
        menuu();
        // Print prompt with running total
        printf("\nres = %d > ", res);
        // Get input string
        gets(input);
        // Clear screen
        system("cls");

        // Switch on operator char input[0]
        switch (input[0]){
            case '+':
                res = add(res, convert(input));
                break;
            case '-':
                res = sub(res, convert(input));
                break;
            case '*':
                res = mul(res, convert(input));
                break;
            case '/':
                res = division(res, convert(input));
                break;
            case '%':
                res = mod(res, convert(input));
                break;
            case '~':
                res = neg(res);
                break;
            case '^':
                res = power(res, convert(input));
                break;
            case 'c':
            case 'C':
                res = 0;
                break;
            case 'q':
            case 'Q':
                printf("Good-bye!\n");
                break;
            default:
                printf("Enter a valid operator and operand\n");

        }

    }


    return 0;
}


// Show menu choices
void menuu(){
    printf("\nSafe Integer Calculator\n");
    printf("+ x to add\n");
    printf("- x to subtract\n");
    printf("* x to multiply\n");
    printf("/ x to divide\n");
    printf("%% x to modulus\n");
    printf("~ x to negate\n");
    printf("^ x to raise by power x\n");
    printf("c x to clear result\n");
    printf("q x to quit\n");
    return;
}


/*
    This function should only use bitwise operators and
    relational operators
*/
// Add operation using only bitwise operators
int _add(int a, int b){
    // Loop until b is zero
    int carry;
    // Find carry 1 bits - a AND b assign to carry

    // Find non carry 1 bits - a XOR b assign to a

    // Multiply carry by 2 by shift and assign to b
    while(b!=0)
    {
        carry=a&b;
        a=a^b;
        b=carry<<1;
    }

    return a;
}


/*
    Safe add() should call _add() and check for both
    overflow and underflow errors.
*/
// Safe add operation
int add(int a, int b){
    // Declare int for result
    int res = 0;
    // Call to _add() a and b and assign to result
    res=_add(a,b);
    // Check for overflow - look at page 90 in book
    if(a>0&&b>0&&res<0)
        res=1;              //OVERFLOW
    else if(a<0&&b<0&&res>0)
            res=-1;         //UNDERFLOW
    return res;                 //GOOD TO GO
}


/*
    Negate a by using a bitwise operator and safe add().
    Look on page 95 in book.
    Replace the zero with an expression that solves this.
*/
// Define negation with ~ and safe add
int neg(int a){
    // Return negation of a and add 1
    return (add(~a,1));
    //return (add(-a,1));
}


/*
    Remember that subtraction is the same as addition
    if you negate one of the operands.
    Replace the zero with an expression that solves this.
*/
// Define safe subtract by safe add - negate b
int sub(int a, int b){
    return (add(a,neg(b)));  // Replace 0 with code
    //return (add(a,-b));
}


/*
    Safe mul() uses an iterative call to safe add()
    to calculate a product. Remember that
        5 x 4 = 5 + 5 + 5 + 5 = 20
*/
// Define safe multiply by calling safe add b times
int mul(int a, int b){

    int smaller;
    int bigger;
    if(abs(a)<abs(b))
        {smaller=a; bigger=b;}
    else
        {smaller=b; bigger=a;}

    int res = 0;
    int i;
    int sign=1;

    //smaller=abs(smaller);
    sign=~sign;
    //bigger=abs(bigger);
    sign=~sign;
    for(i=0;i<abs(smaller);i++)
    {
        res=add(res,bigger);
    }
    // Declare sign of product - initially assume positive

    // For efficiency - smaller number should be multiplier

    // Absolute value of a and flip sign
    // Accumulate result

    // Set sign to output

    return res;
}


/*
    Safe div() repeatedly subtracts b from a, counting the
    number of subtractions until a < b, which it returns.
*/
// Define safe divide by calling safe subtract b times
int division(int a, int b)
{
    // Declare int to count how many times can b be subtracted from a
    int cnt = 1;
    // Declare sign
    int sign=1;
    // Absolute value of a and flip sign
    a=(abs(a));
    sign=~sign;
    // Absolute value of b and flip sign
    b=(abs(b));
    sign=~sign;
    // loop to calculate how many times can b be subtracted from a
    while(a>=b)
    {
        a=sub(a,b);
        cnt+=1;
    }
    // Set sign to output

    return cnt;
}


/*
    Safe mod() repeatedly subtracts b from a until a < b, returning a.
*/
// Define safe modulus by calling safe subtract
int mod(int a, int b){
    // Absolute value of a
    a=abs(a);
    // Absolute value of b
    b=abs(b);
   // if(b>a)
   //     return a;

    while(a>=b&&a>0)
    {
        a=sub(a,b);
    }
    // Find remainder by repeated subtraction a - b

    return a;
}


/*
    Safe pow() calculates as the math pow function but
    only uses the safe operations.
        res = n^exp
    Loop until exp is zero
        res = res * n
        exp = exp - 1
    Remember the special case for n^0

*/
// Define safe pow by calling safe multiply exp times
int power(int n, int exp){
    // Declare int for result of n^exp
    int res = 1;
    if(exp==0)
        return 1;
    while(exp>0)
    {
        res=mul(res,n);
        exp=sub(exp,1);
    }
    // Loop and multiply to calculate n^exp

    return res;
}


/*
    This function extracts the integer value from the input string.
        If input = "+ -123", res = -123.
        If input = "* 987654", res = 987654.
    The best way to solve complicated problems is to work them out
    on paper first.
*/
// Extract the integer from the input string and convert to int
int convert(char *input){
    // Declare int for result extracted from input
    int res = 0;
    // Declare int for sign of result
    int sign=1;
    // Declare two iterators
    int i=0;
    int j=0;
    // Declare a buffer for numeric chars
    char buffer[50];
    // Set error to zero - no error found yet
    error=0;
    // Check for space in element 1

    // Check for negative integer at element 2
    if(input[2]=='-')
    {
        sign=-1;
        puts("Negative number!");
    }


    // Loop to copy all numeric chars to buffer 48 TO 57 ON ASCII CHART
    while(input[i]!='\0')
    {
        if(input[i]>=48&&input[i]<=57)
        {
            buffer[j]=input[i];
            j+=1;
        }
        i+=1;
    }
    // i is iterator for input string and should start at first numeric char
    // j is iterator for buffer where numeric chars are copied
    // This must test for chars between 0 and 9

    // i gets position of last numeric char in buffer

    // j is now used for pow function - start at zero
    j=0;
    int len=strlen(buffer);
    int p=0;
    int tenCount=1;
    for(p=len-2;p>=0;p--)
    {
        if(buffer[p]>=48&&buffer[p]<=57)
        {
            res = res + ((buffer[p] - '0') * tenCount);
            tenCount=tenCount * 10;
        }
    }

    // Construct integer from buffer using pow j increases and i decreases
    //^..what??
    //res=power(j,i);
    // Set sign for output
    if(input[2]=='-')
        return mul(res,-1);
    else
    res= mul(res,sign);
    return res;

}