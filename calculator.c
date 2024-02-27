/*********************REQUIRED HEADER FILES AND GLOBAL VARIABLES*****************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

char num1[50],num2[50];      //getting two numbers
char ch;                                    //getting the operator of the operation
char expression[100];

/**************************PRE-REQUIRED FUNCTIONS*****************************************/
int compare(char *a, char *b) {
    if (a[0] > b[0])
        return 1;
    else {
        int index = 0;
        while (index < strlen(a)) {
            if (a[index] == b[index]) {
                index++;
                continue;
            } else if (a[index] < b[index])
                return 0;
            else if (a[index] > b[index])
                return 1;
        }
    }
}

char* equalizeZeros(char* str, int s, int max)
{
    int N = strlen(str);
    char* ptr = malloc((max + 1) * sizeof(char));
    memset(ptr, '0', max);
    int k = 0;
    for (int i = max - s; i < max; i++)
    {
        ptr[i] = str[k++];
    }
    ptr[max] = '\0';
    return ptr;
}

char* removeZeros(char *a)
{
    int N = strlen(a);
    char *ptr = malloc((N+1)*sizeof(char));
    int k = -1,flag=0;
    for(int i = 0;i<N+1;i++){
        if(a[i]!='0'&&flag==0) {
          ptr[++k] = a[i];
          flag=1;
        }
        else if(flag==1) ptr[++k] = a[i];
    }
    ptr[N] = '\0';
    return ptr;
}

int isValidNumber(char *a)
{
    int N = strlen(a);
    for(int i=0;i<N;i++){
        if(!(isdigit(a[i]))) return 0;
    }
    return 1;
}

char *add(char *a)
{
     int a1, b1;
    int N1 = strlen(a);
    char* temp = malloc((N1 + 1) * sizeof(char));
    char* one = "1";
    if(strlen(one)!=strlen(a)) one = equalizeZeros(one, 1, N1);
    int addArray[N1];
    int carryFlag = 0, sum, res, k = -1;
    for (int i = N1 - 1; i >= 0; i--)
    {
          a1 = a[i] - '0';
          b1 = one[i] - '0';
          sum = carryFlag + a1 + b1;
          res = sum % 10;
          carryFlag = sum / 10;
          addArray[++k] = res;
     }
      int j = 0;
      if (carryFlag != 0) temp[j++] = carryFlag + '0';
      while (k >= 0) temp[j++] = addArray[k--] + '0';
      temp[j] = '\0';
      return temp;
}

char *sub(char *a,char *b)
{
    int a1, b1;
    int N1 = strlen(a);
    char subArray[N1];
    char* temp = malloc((N1 + 1) * sizeof(char));
    char borrowFlag = 0, difference, k = -1, flag = 0;
    for (int i = N1 - 1; i >= 0; i--) {
              a1 = a[i] - '0';
              b1 = b[i] - '0';
              if (a1 == b1) {
                    if (borrowFlag != 0) a1 += 9;
                   difference = a1 - b1;
            }
           else if (a1 < b1) {
                  if (borrowFlag == 0) {
                        a1 += 10;
                        borrowFlag = 1;
                }
            else if (borrowFlag != 0)  a1 = a1 + 9;
            difference = a1 - b1;
          }
           else if (a1 > b1) {
                if (borrowFlag != 0) {
                a1 -= 1;
                borrowFlag = 0;
           }
           difference = a1 - b1;
         }
         subArray[++k] = difference + '0';
   }
    int j = 0;
    for (int i = k; i >= 0; i--) temp[j++] = subArray[i];
    temp[j] = '\0';
    return temp;
}

/**********************START OF OPERATIONS***************************/
void addition(char *a,char *b,char *op1,char *op2)
{
    int a1,b1;
    int N1 = strlen(a);
    int addArray[N1];
    int carryFlag = 0,sum,res,k=-1;
    for(int i=N1-1;i>=0;i--){
        a1=a[i]-'0';
        b1=b[i]-'0';
        sum = carryFlag + a1 + b1;
        res = sum%10;
        carryFlag = sum/10;
        addArray[++k] = res;
    }
    printf("%s + %s = ",op1,op2);
    if(carryFlag != 0) printf("%d",carryFlag);
    while(k>=0){
      printf("%d",addArray[k]);
      k--;
    }
    printf("\n");
}

void subtraction(char *a,char *b,char *op1,char *op2,char ch)    //always do (a-b)
{
    int a1,b1;
    int N1 = strlen(a);
    int subArray[N1];
    int borrowFlag = 0,difference,k=-1,flag=0;
    for(int i=N1-1;i>=0;i--){
        a1=a[i]-'0';
        b1=b[i]-'0';
        if(a1==b1) {
          if(borrowFlag!=0) a1+=9;
          difference = a1-b1;
        }
        else if(a1<b1){
            if(borrowFlag==0){
                a1+=10;
                borrowFlag = 1;
            }
            else if(borrowFlag!=0) a1 = a1+9;
            difference = a1 - b1;
        }
        else if(a1>b1){
            if(borrowFlag!=0){
                a1-=1;
                borrowFlag=0;
            }
            difference=a1-b1;
        }
    subArray[++k] = difference;
    }
    if(ch=='-') printf("%s - %s = -",op2,op1);
    else printf("%s - %s = ",op1,op2);
    while(k>=0){
      if(subArray[k]!= 0 && flag==0 ) {
          printf("%d",subArray[k]);
          flag=1;
        }
      else if(flag==1) printf("%d",subArray[k]);
      k--;
    }
    printf("\n");
}

void multiplication(char *a,char *b)
{
    int a1,b1,k = 0,m,n;
    int N1 = strlen(a);
    int N2 = strlen(b);
    int arr1[100],arr2[100];
    int mulArray[100];
    for(int i=0;i<(N1+N2);i++) mulArray[i] = 0;
    for (int i = 0; i < N1; i++)  arr1[i] = a[N1 - i - 1] - '0';
    for (int i = 0; i < N2; i++)  arr2[i] = b[N2 - i - 1] - '0';
    for (int i = 0; i < N1; i++)
        for (int j = 0; j < N2; j++)
              mulArray[i + j] += arr1[i] * arr2[j];
   for (int i = 0; i <N1+N2 ; i++) {
        mulArray[i + 1] += mulArray[i] / 10;
        mulArray[i] %= 10;
        if (mulArray[i] != 0)   k = i;
    }
    printf("%s * %s = ",a,b);
    for (int i = k; i >= 0; i--)
    printf("%d",mulArray[i]);
    printf("\n");
}

void division(char *a, char *b,char *op1,char *op2)                //a is always greater than b
{
    int N = strlen(a);
    char* quotient = malloc((N + 1) * sizeof(char));
    quotient = "0";
    while (compare(a, b) != 0) {
           a = sub(a, b);
           quotient = add(quotient);
           if (strlen(a) > strlen(b))
                b = equalizeZeros(b, strlen(b), strlen(a));
          else if (strlen(a) < strlen(b))
               a = equalizeZeros(a, strlen(a), strlen(b));
   }
   a = removeZeros(a);
   printf("%s / %s = %s\nRemainder = %s\n", op1, op2, quotient, a);
}

/****************************MAIN FUNCTION***************************/
int main()
{
    char *str1,*str2,*temp1,*temp2;
    int s1,s2,max;
    char flag = 0;
    while(1){
        printf("Calc>");
        fflush(stdin);
        scanf("%[^\n]",expression);
        if(strcmp(expression,"Exit")==0) break;
        sscanf(expression,"%[^(+-/*)] %c %s",num1,&ch,num2);
        if(!(isValidNumber(num1)&&isValidNumber(num2))){
            printf("Check your inputs!!\n");
            continue;
        }
        str1 = removeZeros(num1);
        temp1 = str1;
        str2 = removeZeros(num2);
        temp2 = str2;
        s1=strlen(str1);
        s2=strlen(str2);
        max = (s1>s2)?s1:s2;
        if((s1-s2)==0) goto next;
        else if(max==s1) str2 = equalizeZeros(str2,s2,s1);
        else if(max==s2) str1 = equalizeZeros(str1,s1,s2);
 next:  if(ch=='+'){
            int i=0;
            while(i<strlen(temp1)) if(temp1[i++]!=0) flag = 1;
            if(flag==0) { printf("0 + %s = %s\n",temp2,temp2); continue; }
            i = 0; flag = 0;
            while(i<strlen(temp2)) if(temp1[i++]!=0) flag = 1;
            if(flag==0) { printf("%s + 0 = %s\n",temp1,temp1); continue; }
             addition(str1,str2,temp1,temp2);
        }
        else if(ch=='-'){
            if(strcmp(temp1,temp2)==0) printf("%s - %s = 0\n",temp1,temp2);
            else if(strlen(temp1)>strlen(temp2)) subtraction(str1,str2,temp1,temp2,'+');
            else if(strlen(temp1)==strlen(temp2)){
                if(temp1[0]>temp2[0]) subtraction(str1,str2,temp1,temp2,'+');
                else if(temp1[0]<temp2[0]) subtraction(str2,str1,temp2,temp1,'-');
            }
            else subtraction(str2,str1,temp2,temp1,'-');
        }
        else if(ch=='*') {
            int i=0;
            while(i<strlen(temp1)) if(temp1[i++]!=0) flag = 1;
            if(flag==0) { printf("0 * %s = 0\n",temp2); continue; }
            i = 0; flag = 0;
            while(i<strlen(temp2))  if(temp2[i++]!=0) flag = 1;
            if(flag==0) { printf("%s * 0 = 0\n",temp1); continue; }
            multiplication(temp1,temp2);
        }
        else if(ch=='/') {
            int i=0;
            while(i<strlen(temp1)) if(temp1[i++]!=0) flag = 1;
            if(flag==0) { printf("0 / %s = 0\nRemainder = 0\n",temp2); continue; }
            i = 0; flag = 0;
            while(i<strlen(temp2))  if(temp2[i++]!=0) flag = 1;
            if(flag==0) { printf("MATH ERROR\n"); continue; }
            if(strcmp(temp2,"1") == 0) {printf("%s / 1 = %s\nRemainder = 0\n",temp1,temp1); }
            else if(strcmp(str1,str2)==0) printf("%s / %s = 1\nRemainder = 0\n",temp1,temp2);
            else if(strlen(temp1)==strlen(temp2)){
                 if(temp1[0]>temp2[0]) division(str1,str2,temp1,temp2);
                 else{
                 int index = 0;
                 while(index<strlen(temp1)){
                    if(temp1[index]==temp2[index]){
                        index++;
                        continue;
                    }
                   else if(temp1[index]<temp2[index]) {
                      printf("%s / %s = 0\nRemainder = %s\n",temp1,temp2,temp1);
                      break;
                   }
                   else if(temp1[index]>temp2[index]) {
                     division(str1,str2,temp1,temp2);
                      break;
                   }
                 }
            }
        }
            else if(strlen(temp1)<strlen(temp2)) printf("%s / %s = 0\nRemainder = %s\n",temp1,temp2,temp1);
            else division(str1,str2,temp1,temp2);
        }
    }
}
