# include <iostream>
# include <stdio.h>
# include <string>
# include <vector>
# include <stdlib.h>

using namespace std;

int gLine = 1, gColumn = 0;

enum Type{
  END_OF_FILE,ID,STRLIT,LBR,RBR,DOT,OPERATOR,NONE
};

struct Token {
  Type type ;
  string str;
};

Token gUnDealToken;
bool gPeeking = false;
vector<Token>gToPrintToken;

void Initialize( Token & token );
char Get_the_next_char();
char Get_the_next_non_white_space_char();
Token Get_all_ID( char firstCharacter );
Token Get_all_operator( char firstCharacter );
Token Get_all_STRLIT( char firstCharacter );
Token GetToken();
void Primary_tail( bool & correct );

void PeekToken() {
  gPeeking = true;
  gUnDealToken = GetToken();
  gPeeking = false;
} // PeekToken()

void ErrorHandler( string str, int errorType ) {
  char ch = '\0';
  if ( errorType == 0 ) {
    cout << "> Line " << gLine << " : Error\n" ;
    // do nothing
  } // if
  else if ( errorType == 1 ) {
    //cout << "> Line " << gLine << " : unrecognized token with first char : '" + str +  "'\n";
    cout << "invalid input";
  } // else if
  else if ( errorType == 2 ) {
    cout << "> Line " << gLine << " : unexpected token : '" + str +  "'\n";
  } // else if
  else { 
    cout << "> Line " << gLine << " : undefined identifier : '" + str +  "'\n";
  } // else
  
  gLine = 0;
  while ( ch != '\n' ) {
    ch = Get_the_next_char();
  } // while
  
  Initialize( gUnDealToken );
  throw errorType;
} // ErrorHandler()

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
    
    else if ( ch == '\"' ) {
      token = Get_all_STRLIT( ch );
    } // else if
    
    else if ( ( ch >= 'A' && ch <= 'Z' ) || ( ch >= 'a' && ch <= 'z' ) || ch == '_' ) {
      token = Get_all_ID( ch );
    } // else if
    else {
      // the ERROR: Unrecognized token will occur in Get_all_operator() function.
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

Token Get_all_STRLIT( char firstCharacter ) {
  Token token;
  char ch = '\0';
  string tokenStr = "";
  Initialize( token );
  
  tokenStr += firstCharacter;
  ch = cin.peek();
  while ( ch != '"' ) {
    ch = Get_the_next_char();
    tokenStr += ch;
    ch = cin.peek();
  } // while
  
  ch = cin.get();
  tokenStr += ch;
  token.type = STRLIT;
  token.str = tokenStr;
  return token;
  
} // Token Get_all_STRLIT()

Token Get_all_ID( char firstCharacter ) {
  Token token;
  char ch = '\0';
  string tokenStr = "";
  Initialize( token );
  
  tokenStr += firstCharacter;
  ch = cin.peek();
  while ( ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' ) || ( ch >= '0' && ch <= '9' ) 
        || ch == '_' ) {
    ch = Get_the_next_char();
    tokenStr += ch;
    ch = cin.peek();
  } // while
  
  token.type = ID;
  token.str = tokenStr;
  return token;
  
} // Get_all_ID()

Token Get_all_operator( char firstCharacter ) {
  Token token;
  char ch = '\0';
  string tokenStr = "";
  Initialize( token );
  token.type = OPERATOR;
  
  tokenStr += firstCharacter;
  
  if ( tokenStr == "(" ) {
    token.type = LBR;
    token.str = tokenStr;
    return token;
  } // if
  else if ( tokenStr == ")" ) {
    token.type = RBR;
    token.str = tokenStr;
    return token;
  } // else if
  else if ( tokenStr == "." ) {
    token.type = DOT;
    token.str = tokenStr;
    return token;
  } // else if
  else {
  	ErrorHandler( tokenStr, 1 );
  }
} // Get_all_operator()

char Get_the_next_char() {
  // to read a character 
  // and keep track of the line number and gcolumn number of this character
  // return this character
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
  // to read a non-white-space character 
  // and skip comment
  // return this character
  char ch = '\0', comment = '\0';
  ch = Get_the_next_char();
  while ( IsWhiteSpace( ch ) ) {
    ch = Get_the_next_char();
  } // while

  while ( ch == '/' ) {
    comment = cin.peek();
    // if comment is '/', then read until '\n'.
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
    else { // comment is not '/'(it's means it's only a '/' character 這只是一個除號)
      return ch;
    } // else
    
    // if the next not white space(ch) is '/', then will see if it is comment or not(while loop again).
  } // while
    
  return ch;
} // Get_the_next_non_white_space_char()

void Initialize( Token & token ) {
  token.type = NONE;
  token.str = "";
  //token.value_type = NONE;
  //token.value = 0.0;
} // Initialize()

void Stmt( bool & correct ) {
  bool ptCorrect = false;
  Token token;  
  Initialize( token );
  
  PeekToken();
  if ( gUnDealToken.type == ID ) {
    token = GetToken(); 
    gToPrintToken.push_back(token);
    //cout << "Stmt\t" << token.type << "\t" << token.str << "\n"; 
    Primary_tail( ptCorrect );
    if ( ptCorrect == true ) {
      correct = true;
      return;
    } // if
    correct = false;
    return;
  } // if
  else if ( gUnDealToken.type == STRLIT ) {
    token = GetToken(); 
    gToPrintToken.push_back(token);
    //cout << "Stmt\t" << token.type << "\t" << token.str << "\n"; 
    correct = true;
    return;
  } // else if
  
  correct = true;
  return;
} // Stmt()

void Primary_tail( bool & correct ) {
  bool ptCorrect = false;
  bool stmtCorrect = false;
  Token token;  
  Initialize( token );
  PeekToken();
  if ( gUnDealToken.type == DOT ) {
    token = GetToken(); 
    gToPrintToken.push_back(token);
    //cout << "Pt\t" << token.type << "\t" << token.str << "\n"; 
    PeekToken();
    if ( gUnDealToken.type == ID ) {
      token = GetToken(); 
      gToPrintToken.push_back(token);
      //cout << "Pt\t" << token.type << "\t" << token.str << "\n";
      Primary_tail( ptCorrect );
      if ( ptCorrect == true ) {
        correct = true;
        return;
      } // if
      correct = false;
      return;
    } // if 
    correct = false;
    return;
  } // if
  else if ( gUnDealToken.type == LBR ) {
    token = GetToken(); 
    gToPrintToken.push_back(token);
    //cout << "Pt\t" << token.type << "\t" << token.str << "\n"; 
    Stmt(stmtCorrect);
    if ( stmtCorrect == true ) {
      PeekToken();
      if ( gUnDealToken.type == RBR ) {
        token = GetToken(); 
        gToPrintToken.push_back(token);
        //cout << "Pt\t" << token.type << "\t" << token.str << "\n";
        Primary_tail( ptCorrect );
        if ( ptCorrect == true ) {
          correct = true;
          return;
        }
        correct = false;
        return;
      }
      correct = false;
      return;
    }
    correct = false;
    return;
  }
  correct = true;
  return;
} // Primary_tail()

void Stmts( bool & correct ) {
  bool ptCorrect = false;
  bool stmtsCorrect = false;
  Token token;  
  Initialize( token );
  
  PeekToken();
  if ( gUnDealToken.type == ID ) {
    token = GetToken(); 
    gToPrintToken.push_back(token);
    //cout << "Stmts\t" << token.type << "\t" << token.str << "\n"; 
    Primary_tail( ptCorrect );
    if ( ptCorrect == true ) {
      Stmts( stmtsCorrect );
      if ( stmtsCorrect == true) {
      	correct = true;
    	return;
	  } // if	  
	  correct = false;
      return;
    } // if
    correct = false;
    return;
  } // if
  else if ( gUnDealToken.type == STRLIT ) {
    token = GetToken(); 
    gToPrintToken.push_back(token);
    //cout << "Stmts\t" << token.type << "\t" << token.str << "\n";
    Stmts( stmtsCorrect );
    if ( stmtsCorrect == true ) {
	  correct = true;
      return;
	}
    correct = false;
    return;
  } // else if
  /*
  else if ( gUnDealToken.type == END_OF_FILE ) {
    GetToken();
    correct = true;
    return;
  } // else if
  */
  else {
    correct = true;
    return;
  } // else 
} // Stmts()

void Program( bool & correct ) {
  bool stmtsCorrect = false;
  Stmts( stmtsCorrect );
  if ( stmtsCorrect = true ) {
    correct = true;
    return;
  } // if
  correct = false;
  return;
} // Program()

void Print_enum( int num ) {
  if ( num == ID ) cout << "ID";
  else if ( num == STRLIT ) cout << "STRLIT";
  else if ( num == LBR ) cout << "LBR";
  else if ( num == RBR ) cout << "RBR";
  else if ( num == DOT ) cout << "DOT";
} // Print_enum()

int main() {
  Token token;
  bool programContinue = true;
  char enter;
  bool correct = false;
  
  Initialize( gUnDealToken );
  Initialize( token );

  while ( gUnDealToken.type != END_OF_FILE ) {
    try {  
      Program( correct );
      if ( correct == true ) {
        for ( int i=0; i<gToPrintToken.size(); i++ ) {
        	Print_enum(gToPrintToken[i].type);
        	cout << " " << gToPrintToken[i].str << "\n";
		} // for
		gToPrintToken.clear();
	
      } // if
      
    } // try 
    
    catch( int err ) {
    	
    } // catch()
    
  } // while
  
}


