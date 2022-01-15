# include <iostream>
# include <stdio.h>
# include <string>
# include <vector>
# include <stdlib.h>

using namespace std;

int gLine = 1, gColumn = 0;

enum Type{
  END_OF_FILE,NUM,PLUS,MINUS,MUL,DIV,LPR,RPR,OPERATOR,NONE
};

struct Token {
  Type type ;
  string str;
};

Token gUnDealToken;

void Initialize( Token & token );
char Get_the_next_char();
char Get_the_next_non_white_space_char();
Token Get_all_constant( char firstCharacter );
Token Get_all_operator( char firstCharacter );

Token GetToken() {
  char ch = '\0';
  Token token;
  Initialize( token );
  if ( gUnDealToken.type != NONE ) {
    token = gUnDealToken;
    Initialize( gUnDealToken );
  } // if
  else {
    ch = Get_the_next_non_white_space_char();
    if ( ch == EOF ) {
      token.type = END_OF_FILE;
    } // if 
    else if ( ch >= '0' && ch <= '9' ) {
      token = Get_all_constant( ch );
    } // else if
    else {
      token = Get_all_operator( ch );
    } // else
    
  } // else
  /*
  if ( gLogStatement && !gPeeking ) {
    gTempStatements.push_back( token );
  } // if
  */
  return token;
} // GetToken()

Token Get_all_constant( char firstCharacter ) {

  Token token;
  char ch = '\0';
  string tokenStr = "";
  Initialize( token );
  token.type = NUM;
  
  tokenStr += firstCharacter;
  if ( tokenStr == "0" ) {
    token.str = tokenStr;
    token.type = NUM;
    return token;
  } // if
  
  ch = cin.peek();
  while ( ch >= '0' && ch <= '9' ) {
    ch = Get_the_next_char();
    tokenStr += ch;
    ch = cin.peek();
  } // while
  
  token.str = tokenStr;
  return token;
} // Get_all_constant()

Token Get_all_operator( char firstCharacter ) {
  Token token;
  char ch = '\0';
  string tokenStr = "";
  Initialize( token );
  token.type = OPERATOR;
    
  tokenStr += firstCharacter; 
  if ( tokenStr == "(" ) {
    token.type = LPR;
    token.str = tokenStr;
    return token;
  } // if
  else if ( tokenStr == ")" ) {
    token.type = RPR;
    token.str = tokenStr;
    return token;
  } // else if
  else if ( tokenStr == "+" ) {
    token.type = PLUS;
    token.str = tokenStr;
    return token;
  } // else if
  else if ( tokenStr == "-" ) {
    token.type = MINUS;
    token.str = tokenStr;
    return token;
  } // else if
  else if ( tokenStr == "*" ) {
    token.type = MUL;
    token.str = tokenStr;
    return token;
  } // else if
  else if ( tokenStr == "/" ) {
    token.type = DIV;
    token.str = tokenStr;
    return token;
  } // else if
  
} // Get_all_operator()

char Get_the_next_char() {
  char ch = '\0';
  ch = cin.get();
  if ( ch == EOF ) {
    return ch;
  } // if
  else if ( ch == '\n' ) {
    ++gLine;
    gColumn = 0;
    return ch;
  } // else if
  else {
    ++gColumn;
    return ch;
  } // else 

} // Get_the_next_char()

bool IsWhiteSpace( char ch ) {
  if ( ch == ' ' || ch == '\t' || ch == '\n' ) {
    return true;
  } // if
  
  return false;
} // IsWhiteSpace()

char Get_the_next_non_white_space_char() {
  char ch = '\0', comment = '\0';
  ch = Get_the_next_char();
  while ( IsWhiteSpace( ch ) ) {
    ch = Get_the_next_char();
  } // while

  // skip comment
  while ( ch == '/' ) {
    comment = cin.peek();
    if ( comment == '/' ) {
      comment = '\0';
      ch = Get_the_next_char();
      while ( ch != '\n' ) { // read until '\n'.
        ch = Get_the_next_char();
      } // while
      
      while ( IsWhiteSpace( ch ) ) { // read until not white space
        ch = Get_the_next_char();
      } // while
      
    } // if
    else { // comment is not '/'(it's means it's only a '/' character )
      return ch;
    } // else
    
    // if the next not white space(ch) is '/', then will see if it is comment or not(while loop again).
  } // while
    
  return ch;
} // Get_the_next_non_white_space_char()

void Initialize( Token & token ) {
  token.type = NONE;
  token.str = "";
} // Initialize()

void Print_enum( int num ) {
  if ( num == NUM ) cout << "NUM";
  else if ( num == PLUS ) cout << "PLUS";
  else if ( num == MINUS ) cout << "MINUS";
  else if ( num == MUL ) cout << "MUL";
  else if ( num == DIV ) cout << "DIV";
  else if ( num == LPR ) cout << "LPR";
  else if ( num == RPR ) cout << "RPR";
} // Print_enum()

int main() {
  Token token;
  bool programContinue = true;
  char enter;
  
  Initialize( gUnDealToken );
  Initialize( token );

  while ( token.type != END_OF_FILE ) {
    try {
      token = GetToken();
      Print_enum( token.type );
      if ( token.type == NUM ) cout << " " << token.str ;
      cout << "\n";
    } // try 
    catch( int err ) {
      
    } // catch()
    
  } // while

} // main()
