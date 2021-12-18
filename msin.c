/* A simple B interpreter */

#include <stdio.h>  /* include declarations for i/o routines */
#include <ctype.h>  /* ... and for character test routines */
#include <stdlib.h> /*and for some standard routines, such as exit*/


#define NONE   -1

#define NUM    1
#define STR	   2
#define ID     3
#define BOOL   4
#define CHAR   5
#define DONE   6
#define semi    7
#define Lbrake  8
#define Rbrake  9
#define Lbracket    10
#define Rbraket 11
#define Lparen  12
#define Rparen  13
#define pp  14
#define plus    15
#define mm  16
#define minus   17
#define mult    18
#define mod 19
#define comma   20
#define colon   21
#define leq 22
#define lss 23
#define geq 24
#define gtr 25
#define eq  26 
#define ass 27
#define neq 28
#define not 29
#define tk_and  30
#define eoi 31
#define tk_or   32
#define eoi 33

char keywords[10][15] = {"array","boolean","char","else","false","for","function","if","integer","print","return","string","true","void","while"};
char  *tokenval = "";
int line=1,column=0;
static FILE *source_fp;


int lexan (){  /*  lexical analyzer  */
  char t , temp[256] , nullstr[256] = {};
  while(1) {
    t = fgetc(source_fp);
    if (t == ' ' || t == '\t')
    column ++;
        /*  strip out white space  */
    else if ( t == '\n'){
    	column = 0;
    	line ++;
	}
	
    else if (isdigit (t)) {  /*  t is a digit  */
      ungetc(t, source_fp);
      int i =0;strcpy(temp,nullstr);
      while ((temp[i++] = fgetc(source_fp)) != '\n' && isdigit(temp[i-1]));
      strcpy(tokenval,temp);
      ungetc(t, source_fp);
      return NUM;
    }

    else if (t == EOF)
      return eoi;
    
    else if (isalpha(t)) {
        ungetc(t,source_fp);
        int i =0;strcpy(temp,nullstr);
    while ((temp[i++] = fgetc(source_fp)) != '\n' && ( isalpha(temp[i-1]) || isdigit(temp[i-1]) ||temp[i-1] == '_' ));
    temp[i] = '\0';
      strcpy(tokenval,temp);
	  for (int i=0;i<15;i++){
      	if( strcmp(tokenval, keywords[i]) == 0)
		{
    		return keywords[i];
		}
	  }
      return ID;
    }
    
    else if (t == '/'){
        t = fgetc(source_fp);
        if ( t == '*'){
        while (1){
    while ((t = fgetc(source_fp)) != '*' );
        t = fgetc(source_fp);
        if (t == '/') break;
        }
        }else if (t == '/'){
            while ((t = fgetc(source_fp)) != '\n' );
        }else{
        	ungetc(t,source_fp);
            return div;
        }
    }

    else if (t == '\''){
        temp[0] = fgetc(source_fp);
        t = fgetc(source_fp);
        if (t == '\''){
            tokenval = temp[0];
            return CHAR;
        }else{
            ungetc(t,source_fp);
            ungetc(temp[0],source_fp);
            printf("error in carachter, line:%d, column %d\n",line,column);
        }
    }
    
    else if (t == '\"'){
        ungetc(t,source_fp);
        int i =0;strcpy(temp,nullstr);
    while ((temp[i++] = fgetc(source_fp)) != '\n' && temp[i-1] == '\"' );
    if (temp[i-1] == '\"'){
        strcpy(tokenval,temp);
      return STR;
    }
    else{
        printf("error in string coats, line:%d, column %d\n",line,column);
    }
    }


    else if (t == ';')
      return semi;
    else if (t == '{'){
    	return Lbrake;
	}
	else if (t == '}'){
		return Rbrake;
	}
	else if (t == '['){
    	return Lbracket;
	}
	else if (t == ']'){
    	return Rbraket;
	}
	else if (t == '('){
    	return Lparen;
	}
	else if (t == ')'){
    	return Rparen;
	}
	else if (t == '+'){
		temp[0] = fgetc(source_fp);
    	if (temp[0] == '+'){
    	return pp;
	}else{
		ungetc(temp[0],source_fp);
		return plus;
	}
	}
	else if (t == '-'){
		temp[0] = fgetc(source_fp);
    	if (temp[0] == '-'){
    	return mm;
	}else{
		ungetc(temp[0],source_fp);
		return minus;
	}
	}
	else if (t == '*'){
		return mult;
	}
	else if (t == '%'){
		return mod;
	}
	else if (t == ','){
		return comma;
	}
	else if (t == ':'){
		return colon;
	}
	else if (t == '<'){
		temp[0] = fgetc(source_fp);
    	if (temp[0] == '='){
    	return leq;
	}else{
		ungetc(temp[0],source_fp);
		return lss;
	}
	}
	else if (t == '>'){
		temp[0] = fgetc(source_fp);
    	if (temp[0] == '='){
    	return geq;
	}else{
		ungetc(temp[0],source_fp);
		return gtr;
	}
	}
	else if (t == '='){
		temp[0] = fgetc(source_fp);
    	if (temp[0] == '='){
    	return eq;
	}else{
		ungetc(temp[0],source_fp);
		return ass;
	}
	}
	else if (t == '!'){
		temp[0] = fgetc(source_fp);
    	if (temp[0] == '='){
    	return neq;
	}else{
		ungetc(temp[0],source_fp);
		return not;
	}
	}
	else if (t == '&'){
		temp[0] = fgetc(source_fp);
    	if (temp[0] == '&'){
    	return tk_and;
	}else{
		ungetc(temp[0],source_fp);
		return eoi;
	}
	}
	else if (t == '|'){
		temp[0] = fgetc(source_fp);
    	if (temp[0] == '|'){
    	return tk_or;
	}else{
		ungetc(temp[0],source_fp);
		return eoi;
	}
	}
	
	
    
  }
}


int main (int argc, char *argv[]){
	if (argc <= 1){
        printf("please enter source file path.");
        return 1;
    }

    if ((source_fp = fopen(argv[1], "r")) == NULL){
        printf("Can't open %s\n", argv[1]);
        return 1;
    }
    
    
    printf("Line\tColumn\t\tToken type\t\tValue\n\n");
    int type=0;
    do {
    	type = lexan();
    	switch(type){
		
case 1:
printf("number  %s\n",*tokenval);
break;
    case 2:
printf("string %s\n",*tokenval);
break;
    case 3:
printf("id %s\n",*tokenval);
break;
    case 4:
printf("\n");
break;
    case 5:
printf("char %s\n",*tokenval);
break;
    case 6:
printf("\n");
break;
    case 7:
printf("");
break;
    case 8:
printf("");
break;
    case 9:
printf("");
break;
    case 10:
printf("");
break;
    case 11:
printf("");
break;
    case 12:
printf("");
break;
    case 13:
printf("");
break;
    case 14:
printf("");
break;
    case 15:
printf("");
break;
    case 16:
printf("");
break;
    case 17:
printf("");
break;
    case 18:
printf("");
break;
    case 19:
printf("");
break;
    case 20:
printf("");
break;
    case 21:
printf("");
break;
    case 22:
printf("");
break;
    case 23:
printf("");
break;
    case 24:
printf("");
break;
    case 25:
printf("");
break;
    case 26: 
printf("");
break;
    case 27:
printf("");
break;
    case 28:
printf("");
break;
    case 29:
printf("");
break;
    case 30:
printf("");
break;
    case 31:
printf("");
break;
    case 32:
printf("");
break;
}
	}while (type != 33);
}
