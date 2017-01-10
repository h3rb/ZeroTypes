#pragma once

#include "LinkedList.h"

// "Direct" or "older" way of using the LinkedList class (ZeroTypes circa 2012)

class ChildItem : public ListItem {
public:
 Zstring name;
 void WhoAmI() {
  OUTPUT("%s",this->identity().c_str());
 }
 void Set( const char *name ) { this->name=name; }
 string toString() { return name; }
 void fromString( const char *s ) { name=s; }
};

class ChildCollection : public LinkedList {
public:
 void Add() {
  Append(new ChildItem);
 }
 void WhoAmI() {
  OUTPUT(this->identity().c_str());
 }
 void Print() {
  FOREACH(ChildItem,c) OUTPUT("%s\n",c->name.c_str());
 }
 CLEARLISTRESET(ChildItem)  // expects ChildItem in this list...
};

// ZeroTypes circa 2016
// "New" or "faster to implement" or "easy to read" way of implementing a single and its collection.

ONE(SingleItem,{})
MANY(SingleItem,SingleItemHandle,SingleItemHandles,"SingleItem",SingleItems,{})
DONE(SingleItem);


// Implements a child of SingleItem called SingleItemChildItem
// Also implements a text-based file format
// (toString and fromString are implemented using macros)

C_ONE(SingleItemChildItem,SingleItem,{
  z=5;
})
 Zint z;
 Zstring protected_text;
 KEYWORDS({
  KEYWORD("name",{name=w;})    // a default property implemented by macro SINGLE
  TXTWORD("protected_text",protected_text);
  NUMWORD("z",z)
 })
 WORDKEYS({
  WORDKEY("name",name)
  TXTKEY("protected_text",protected_text)
  NUMBKEY("z",z)
 })
  void EachMethod() {
   OUTPUT("This is a method for each in the list!\n");
  }
  void Render() {
  }
  void Between() { /* each frame... */  }
MANY(SingleItemChildItem,SingleItemChildItemHandle,SingleItemChildItemHandles,"SingleItemChildItem",SingleItemChildItems,{
 p=5;
})
 Zint p;
 SingleItemChildItems( int pvalue ) : LinkedList() { p=pvalue; } // custom constructor
 KEYSWORDSGroups("SingleItemChildItem",SingleItemChildItem)
 CALLEACH(SingleItemChildItem,EachMethod)  // Implements EachMethod() that calls EachMethod on each item in list...
 CALLEACH(SingleItemChildItem,Render)
 CALLEACH(SingleItemChildItem,Between)
 void PrintNames() {
  FOREACH(SingleItemChildItem,sici) {
   OUTPUT("%s%c",sici->name.c_str(),sici->next?',':'\n');
  }
 }
 SORTING(SingleItemChildItem,SortNames,{},{ result= (int)A->name.value.compare(B->name.value); },{})
DONE(SingleItemChildItem);

// Real-time type identifier optimization for polymorphic lists

#define RTID_MyTypeName 12345  // must be unique and not 0
RONE(MyTypeName,RTID_MyTypeName,{})
 Zint value;
 MyTypeName( int number ) : ListItem() {
  value=number;
 }
MANY(MyTypeName,MyTypeNameHandle,MyTypeNameHandles,"MyTypeName",MyTypeNames,{})
 void Fast() {
  int i=0;
  FOREACH(ListItem,L) {
   if ( L->rtid == RTID_MyTypeName ) 
    OUTPUT("element #%d is of the expected type\n",(int)i);
   i++;
  }
 }
 void Slow() {
  int i=0;
  FOREACH(ListItem,L) {
   if ( L->is("MyTypeName") ) OUTPUT("element #%d is of the expected type\n",(int)i);
   else OUTPUT("Unexpected type found: %s\n", L->identity().c_str() );
   i++;
  }
 }
 string toString() {
  string output=string("");  // could have used Zstring output; instead...
  FOREACH(ListItem,L) output+=L->identity()+string("...");
  return output;
 }
DONE(MyTypeName);

#include "ZIndexed.h"

struct ZintGrid : public ZIndexed<Zint> {
 void Make() {
  Size(1000); // creates 1000 Zints (integers set to 0), length=1000, w=1000, h=1
 }
};

struct MyStruct {
 Zint x,y,value;
};

struct OurStruct : public ZIndexed<MyStruct> {
public:
 OurStruct() : ZIndexed<MyStruct>() {
  Size((size_t)10,(size_t)10);
  Renumber();
  Print();
 }
 void Renumber() {
  for ( int i=0; i<(int)w; i++ ) {
   for ( int j=0; j<(int)h; j++ ) {
    (*this)(i,j).x=i;
    (*this)(i,j).y=j;
    // or...
    MyStruct *m=&((*this)(i,j));
    m->value=i*j;
   }
  }
 }
 void Print() {
  OUTPUT("Printing the contents of OurStruct...\n");
  for ( int j=0; j<(int)h; j++ ) {
   for ( int i=0; i<(int)w; i++ ) {
    OUTPUT("[%c]",((*this)(i,j).value%2==0?'X':'0'));
   }
   OUTPUT("\n");
  }
  OUTPUT("done!\n");
 }
};

// You can also do this:



// See this function for the test case of these classes...
void Examples();