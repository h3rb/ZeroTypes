
/***********************************************************************************************
 * Herbian Art and Animation Engine ("HAAE")                                                   *
 ***********************************************************************************************
 * This software is copyrighted software.  Use of this code is given only with permission to   *
 * parties who have been granted such permission by its author, Herbert Elwood Gilliland III   *
 ***********************************************************************************************
 * Copyright (c) 2010 Herbert Elwood Gilliland III ; All rights reserved.                      *
 ***********************************************************************************************/
#include "Strings.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

// String

const char *String::c_str() {
 return this->s.c_str();
}

// Strings
#include "BinaryFile.h"

void Strings::ls_( const char *targetPath, bool listFiles, bool prependPath, bool filterOSFiles ) {
 Strings *folder=ls(targetPath,listFiles,prependPath,filterOSFiles);
 if ( folder ) {
  Concat(folder);
  delete folder;
 }
}

void Strings::Load( const char *filename )
{
 Clear();
 BinaryFile *bf=new BinaryFile(filename,false);
 char ch='\0';
 Zstring line;
 while ( !bf->is_eof() ) {
  if ( !bf->read(&ch) ) break;
  if ( ch == '\r' ) continue;
  if ( ch == '\n' ) {
   String *t=null;
   NEW(t,String(line.c_str()));
   Append(t);
   line.Clear();
   continue;
  }
  line+=ch;
 }
 delete bf;
 if ( line.length > 0 ) {
  String *t=null;
  NEW(t,String(line.c_str()));
 }
}

void Strings::Save( const char *filename )
{
 Clear();
 FILE *f;
 fopen_s(&f,filename, "w");
 if(f)
 {
  fclose(f);
  std::fstream filestr;
  filestr.open(filename, std::fstream::in | std::fstream::out );
  FOREACH(String,s) filestr<<s->s.c_str()<<endl;
  filestr.close();
 }  
 else OUTPUT("File not writeable: %s\n", filename);
}

bool Strings::inList( string s ) {
 FOREACH(String,sL) if ( s == sL->s ) return true;
 return false;
}

String *Strings::matchPrefix( const char *s ) {
 FOREACH(String,sL) if ( sL->s.length() > 0 && strlen(s) > 0 && !str_prefix(sL->c_str(),s) ) return sL;
 return null;
}

void Strings::matchesPrefix( const char *s, Strings *out ) {
 FOREACH(String,sL) {
  if ( sL->s.length() > 0 && strlen(s) > 0 && !str_prefix(sL->c_str(),s) ) {
   out->Push(sL->s.c_str());
  }
 }
}

String *Strings::match( const char *s ) {
 FOREACH(String,sL) if ( !str_cmp(sL->c_str(),s) ) return sL;
 return null;
}

String *Strings::find( string s ) {
 FOREACH(String,sL) if ( s == sL->s ) return sL; 
 return null;
}

String *Strings::find( const char *s ) {
 string f=string(s);
 FOREACH(String,sL) if ( f == sL->s ) return sL; 
 return null;
}

String *Strings::findCaseless( const char *s ) {
 string f=string(s);
 FOREACH(String,sL) if ( !str_cmp(s, sL->s.c_str() ) ) return sL; 
 return null;
}

String *Strings::findCaseless( string s ) {
 string f=string(s);
 FOREACH(String,sL) if ( !str_cmp((char *) s.c_str(), (char *) sL->s.c_str() ) ) return sL; 
 return null;
}

 String *Strings::findSubstring( const char *s ) {
  FOREACH(String,sL) if ( !str_prefix(sL->s.c_str(),s) ) return sL; 
  return null;
 }

 String *Strings::findNextSubstring( String *start, const char *s ) {
  String *sL=start;
  while ( sL && string_infix(s,sL->s) ) sL=(String *) sL->next;
  return sL;
 }

 string Strings::concatToNextSubstring( String *start, const char *end ) {
  String *e = this->findNextSubstring(start,end);
  string x=string("");
  String *sL=start;
  while ( sL && sL != e ) { x+=sL->s+string("\n"); sL=(String *) sL->next; }
  return x;
 }

// Returns -1 if not in list
int Strings::IndexOf( String *s ) {
 int i=0;
 FOREACH(String,sL) {
  if ( s == sL ) return i;
  else i++;
 }
 return -1;
}

// Returns duplicated concatenations of Strings
string Strings::Concatenate( char seperator ) {
 string e = string("");
 FOREACH(String,sL) {
  e=e+sL->s;
  e.append( 1, seperator );
 }
 return e;
}

// Returns duplicated concatenations of Strings
string Strings::Concatenate( having Seamless ) {
 string e = string("");
 FOREACH(String,sL) {
  e=e+sL->s;
 }
 return e;
}

void Strings::appendFromString( const char *s, char c ) {
 static char temp[STRING_SIZE];
 const char *p= s;
 int i=0;
 while ( *p != '\0' ) {
  if ( *p==c ) {
   temp[i]='\0';
   String *t; NEW(t,String(temp));
   if (!t) {
    OUTPUT("appendFromString: error on allocation, Could not allocate new string.\n");
    return;
   }
   Append(t);
   i=0;
  } else
  temp[i++] =*p;
  p++;
 }
}

void Strings::appendFromString( string s, char c ) {
 appendFromString( (char *) s.c_str(), c );
}

void Strings::show() 
{ 
 FOREACH(String,s) OUTPUT( "%s\n", s->s.c_str() ); 
}

void Strings::show( const char *sep, const char *end ) 
{ 
 FOREACH(String,s) OUTPUT( "%s%s", s->s.c_str(), (s->next ? sep : "") );
 OUTPUT("%s",end);
}

// Splits using string_argument
void Strings::SplitPush( const char *s ) {
 const char *p=s;
 while ( *p != '\0' ) {
  string t;
  p=string_argument(p,&t);
  if ( t.length() > 0 ) Push(t);
 }
}


// Splits by char_in(), like char_isof, default is newline/space
void Strings::SplitPush( const char *s, const char *delimiterList ) {
 const char *p=s;
 Zstring t;
 while ( *p != '\0' ) {
  if ( char_in(*p,delimiterList) ) if ( t.length > 0 ) { Add(t.c_str()); t=""; }
  else t+=(*p);
  p++;
 }
}

void Strings::SplitPush( string s, char seperator ) {
 string t;
 static char buf[2];
 buf[0]=seperator;
 buf[1]='\0';
 const char *p=s.c_str();
 while ( *(p=gather_to(p,buf,&t)) != '\0' ) Push(t);
 if ( t.length() > 0 ) Push(t);
}



void Strings::SplitPush( const char *s, char seperator ) {
 string t;
 static char buf[2];
 buf[0]=seperator;
 buf[1]='\0';
 const char *p=s;
 while ( *(p=gather_to(p,buf,&t)) != '\0' ) Push(t);
 if ( t.length() > 0 ) Push(t);
}


// Splits using string_argument
void Strings::ScriptPush( const char *s ) { SplitPush(s); }

void Strings::Push( string s ) {
 String *t; NEW(t,String(s));
 if (!t) {
  OUTPUT("Push: error on allocation, Could not allocate new string.\n");
  return;
 }
 Append(t);
}

void Strings::Push( const char *s ) {
 String *t; NEW(t,String(s));
 if (!t) {
  OUTPUT("Push: error on allocation, Could not allocate new string.\n");
  return;
 }
 Append(t);
}

String *Strings::PushAndGet( const char *s ) {
 String *x; NEW(x,String(string(s)));
 if (!x) {
  OUTPUT("PushAndGet: error on allocation, Could not allocate new string.\n");
  return null;
 }
 Append(x);
 return x;
}

void Strings::DuplicateAndPush( const char *s ) { // No longer different
 String *t; NEW(t,String(s));
 if (!t) {
  OUTPUT("DuplicateAndPush: error on allocation, Could not allocate new string.\n");
  return;
 }
 Append( t );
}

#include <Windows.h> // for ls()
#include <tchar.h> // for ls()

// List directory contents
// http://msdn.microsoft.com/en-us/library/aa365200%28VS.85%29.aspx
// When listFiles parameter is false, find only subfolder names.
Strings *ls( const char *targetPath, bool listFiles, bool prependPath, bool filterOSFiles ) {
 WIN32_FIND_DATA ffd;
 TCHAR szDir[MAX_PATH];
 size_t length_of_arg;
 HANDLE hFind=INVALID_HANDLE_VALUE;
 DWORD dwError=0;
 string endsWithSlash=trailing_backslash(slash_to_backslash(targetPath).c_str());

 // Check that the input path plus 3 is not longer than MAX_PATH.
 // Three characters are for the "\*" plus NULL appended below.
 length_of_arg = strlen(targetPath);
 if (length_of_arg > (MAX_PATH - 3)) {
  OUTPUT("Strings.h ls() reports directory path is too long.\n");
  return null;
 }

 // Prepare string for use with FindFile functions.  First, copy the
 // string to a buffer, then append '\*' to the directory name.
 char path[MAX_PATH+1];
 FORMAT(path,MAX_PATH+1,"%s*",endsWithSlash.c_str());
 for ( int i=0; i<MAX_PATH; i++ ) szDir[i]=(TCHAR) path[i];

 // Find the first file in the directory.
 hFind = FindFirstFile(szDir, &ffd);

 if (INVALID_HANDLE_VALUE == hFind) {
  OUTPUT("String.h ls() reported error: Error was %d\n", (int) dwError );
  return null;
 }

 Strings *list; NEW(list,Strings);
   
 // List all the files in the directory with some info about them.
 do {
  bool isFolder=true && (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
  char buf[260];
  FORMAT(buf,260,"%s",ffd.cFileName);
  if ( filterOSFiles ) {
   if ( !str_cmp(buf,".") ) continue;
   if ( !str_cmp(buf,"..") ) continue;
   if ( !str_cmp(buf,"Thumbs.db") ) continue;
  }
  if (!listFiles && isFolder) {
   if ( prependPath ) {
    char buf2[260+1024];
    FORMAT(buf2,260+1024,"%s%s",endsWithSlash.c_str(),buf);
    String *n; NEW(n,String(buf2));
    list->Append(n);
   } else {
    String *n; NEW(n,String(buf));
    if (!n) {
     OUTPUT("ls: error on allocation, Could not allocate new string.\n");
     return null;
    }
    list->Append(n);
   }
  } else if ( !isFolder ) {
   if ( prependPath  ) {
    char buf2[260+1024];
    FORMAT(buf2,260+1024,"%s%s",endsWithSlash.c_str(),buf);
    String *n; NEW(n,String(buf2));
    if (!n) {
     OUTPUT("ls: error on allocation, Could not allocate new string.\n");
     return null;
    }
    list->Append(n);
   } else {
    String *n; NEW(n,String(buf));
    if (!n) {
     OUTPUT("ls: error on allocation, Could not allocate new string.\n");
     return null;
    }
    list->Append(n);
   }
  }
 }
 while (FindNextFile(hFind, &ffd) != 0); 
 dwError = GetLastError();
 if (dwError != ERROR_NO_MORE_FILES) OUTPUT("Strings.h ls() reported an unexpected error (code %d).\n", (int) dwError );
 FindClose(hFind);
 return list;
}

Strings *ls( const char *targetPath, bool listFiles, bool prependPath, Strings *filters ) {
 WIN32_FIND_DATA ffd;
 size_t length_of_arg;
 HANDLE hFind=INVALID_HANDLE_VALUE;
 DWORD dwError=0;
 
 string endsWithSlash=trailing_backslash(slash_to_backslash(targetPath).c_str());

 // Check that the input path plus 3 is not longer than MAX_PATH.
 // Three characters are for the "*" plus NULL appended below.
 length_of_arg = strlen(targetPath);
 if (length_of_arg > (MAX_PATH - 3)) {
  OUTPUT("Strings.h ls() reports directory path is too long.\n");
  return null;
 }

 // Prepare string for use with FindFile functions.  First, copy the
 // string to a buffer, then append '*' to the directory name.
 char path[MAX_PATH+1];
 FORMAT(path,MAX_PATH+1,"%s*",endsWithSlash.c_str());
 TCHAR szDir[MAX_PATH];
 for ( int i=0; i<MAX_PATH; i++ ) szDir[i]=(TCHAR) path[i];

 // Find the first file in the directory.
 hFind = FindFirstFile(szDir, &ffd);

 if (INVALID_HANDLE_VALUE == hFind) {
  OUTPUT("String.h ls() reported error: Error was %d\n", (int) dwError );
  return null;
 }

 Strings *list; NEW(list,Strings);
 if (!list) {
  OUTPUT("ls: could not allocate list.\n");
  return null;
 }
   
 // List all the files in the directory with some info about them.
 do {
  bool isFolder=true && (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
  char buf[260];
  FORMAT(buf,260,"%s",ffd.cFileName);
  if ( filters ) {
   bool found=false;
   EACH(filters->first,String,filter) if ( !str_infix(buf,filter->c_str()) ) found=true;
   if ( found ) continue;
  }
  if (!listFiles && isFolder) {
   if ( prependPath ) {
    static char buf2[260+1024];
    FORMAT(buf2,260+1024,"%s%s",endsWithSlash.c_str(),buf);
    String *n; NEW(n,String(buf2));
    if (!list) {
     OUTPUT("ls: could not allocate list.\n");
     return null;
    }
    list->Append(n);
   } else {
    String *n; NEW(n,String(buf));
    if (!n) {
     OUTPUT("ls: could not allocate string.\n");
     return null;
    }
    list->Append(n);
   }
  } else if ( !isFolder ) {
   if ( prependPath  ) {
    static char buf2[260+1024];
    FORMAT(buf2,260+1024,"%s/%s",targetPath,buf);
    String *n; NEW(n,String(buf2));
    if (!n) {
     OUTPUT("ls: could not allocate string.\n");
     return null;
    }
    list->Append(n);
   } else {
    String *n; NEW(n,String(buf));
    if (!n) {
     OUTPUT("ls: could not allocate string.\n");
     return null;
    }
    list->Append(n);
   }
  }
 }
 while (FindNextFile(hFind, &ffd) != 0); 
 dwError = GetLastError();
 if (dwError != ERROR_NO_MORE_FILES) OUTPUT("Strings.h ls() reported an unexpected error (code %d).\n", (int) dwError );
 FindClose(hFind);
 return list;
}
