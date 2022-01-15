%{
	#include <stdio.h>
	int yylex(void);
	void yyerror(const char *);
	int stack[200];
	int count = 0;
	int i = 0;
	
%}


%union{
    int ival;
}

%token <ival> INTEGER
%token INC
%token DEC
%token LOAD
%token ADD
%token SUB
%token MUL
%token MOD
%type <ival> expr

%%
command : lines {
		//printf("111");
                	if (count != 1) {
						printf("Invalid format\n");
                    	exit(0);
                    }
                    else {
						printf("%d",stack[count-1]);
			    	}
                }
		
lines   : lines line    {;}
        | line          {;}
        ;
line    : expr '\n'     {;}
        | expr          {;}
        | '\n'          {;}
        ;
expr    : LOAD INTEGER 	{ 
			     				stack[count] = $2;
							//printf("123");
		     					count++; 
						}
		| ADD           {
                            if (count < 2) {
                                printf("Invalid format\n");
                                exit(0);
                            }
                            else {
				count--;
                                int a = stack[count];
                                count--;
                                int b = stack[count];
                                
                                stack[count] = a+b;
                                count++;
                            }
                        }
		| SUB           {
				//printf("122");
                            if (count < 2) {
                                printf("Invalid format\n");
                                exit(0);
                            }
                            else {
				count--;
                                int a = stack[count];
                                count--;
                                int b = stack[count];
                                
                                stack[count] = a-b;
                                count++;
                            }
                        }
		| MUL           {
		                    if (count < 2) {
		                        printf("Invalid format\n");
		                        exit(0);
		                    }
		                    else {
					count--;
		                        int a = stack[count];
		                        count--;
		                        int b = stack[count];
		                        
		                        stack[count] = a*b;
		                        count++;
		                    }
                        }	
 		| MOD           {
							if (count < 2) {
								printf("Invalid format\n");
		                   				exit(0);
							}
							else {
								count--;
								int a = stack[count];
					                        count--;
					                        int b = stack[count];
					                        
					                        stack[count] = a%b;
		                        			count++;
							}
 		           		}  
		| INC           {
                            if (count < 1) {
                                printf("Invalid format\n");
		                   		exit(0);
                            }
                            else {
                                stack[count-1] = stack[count-1]+1;
                            }
                        }
        | DEC           {
                            if (count < 1) {
                                printf("Invalid format\n");
                                exit(0);
                            }
                            else {
                                stack[count-1] = stack[count-1]-1;
                            }
                        }
        ;           
%%

void yyerror(const char *message) {
    printf("Invalid input\n");
}

int main(void) {
	for( i=0; i<=200; i++ ) {
		stack[i] = 0;
	}
    yyparse();
    return 0;
}					
					
					
					
					
