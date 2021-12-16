/* A simple B interpreter */

#include <stdio.h>  /* include declarations for i/o routines */
#include <ctype.h>  /* ... and for character test routines */
#include <stdlib.h> /*and for some standard routines, such as exit*/


#define NONE   -1

#define NUM    256
#define STR	   257
#define ID     258
#define BOOL   259
#define CHAR   260
#define DONE   261

char keywords[10][] = {"array"
,"boolean"
,"char"
,"else"
,"false"
,"for"
,"function"
,"if"
,"integer"
,"print"
,"return"
,"string"
,"true"
,"void"
,"while"}
char  *tokenval = "";
int lexan (){  /*  lexical analyzer  */
  char t , temp[256] , nullstr[256] = {};
  while(1) {
    t = getchar ();
    if (t == ' ' || t == '\t' || t == '\n')
      ;  /*  strip out white space  */
    
    else if (isdigit (t)) {  /*  t is a digit  */
      ungetc(t, stdin);
      int i =0;strcpy(temp,nullstr);
      while ((temp[i++] = getchar()) != '\n' && isdigit(temp[i-1]);
      strcpy(tokenval,temp);
      ungetc(t, stdin);
      return NUM;
    }

    else if (t == EOF)
      return DONE;
    
    else if (isalpha(t)) {
        ungetc(t,stdin);
        int i =0;strcpy(temp,nullstr);
    while ((temp[i++] = getchar()) != '\n' && ( isalpha(temp[i-1]) || isdigit(temp[i-1]) ||temp[i-1] == '_' ));
    temp[i] = '\0'
      strcpy(tokenval,temp);
      ungetc(t, stdin);
      return ID;
    }
    
    else if (t == '/'){
        t = getchar ();
        if ( t == '*'){
        while (1){
    while ((t = getchar()) != '*' );
        t = getchar ();
        if (t == '/') break;
        }
        }else if (t == '/'){
            while ((t = getchar()) != '\n' );
        }else{
            //error
        }
    }

    else if (t == '\''){
        temp[0] = getchar();
        t = getchar();
        if (t == '\''){
            tokenval = temp[0];
            return CHAR;
        }else{
            ungetc(t,stdin);
            ungetc(temp[0],stdin);
            //error
        }
    }
    
    else if (t == '\"'){
        ungetc(t,stdin);
        int i =0;strcpy(temp,nullstr);
    while ((temp[i++] = getchar()) != '\n' && temp[i-1] == '\"' );
    if (temp[i-1] == '\"'){
        strcpy(tokenval,temp);
      return STR;
    }
    else{
        //error
    }
    }


    else if (t == ';')
      return DONE;
    
    else {  /*  any character */
      error("compiler error");
    }
  }
}


int main (){
	
	
	return 0;
}
