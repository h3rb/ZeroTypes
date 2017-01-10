/*

 ZeroTypes Library
 Open source license: BSD 4-clause

 Author: H. Elwood Gilliland III
 Copyright (c) 2007-2017

*/
#pragma once
#pragma warning (disable:4100)

#include <string>
using namespace std;
#include "string_functions.h"
#include "macros.h"
#include "ZeroTypes.h"

class BinaryFile;
class KeyedDataStore;

#define CLONE(single,code) single *Duplicate() { single *a=new single; {code} return a; }
#define DUPE(membername) {a->membername=membername;}
#define DUPELIST(membername,membername_single) { EACH(membername->first,membername_single,b) a->membername->Append(b->Duplicate()); }
#define DUPESLIST(membername,membername_single) { EACH(membername.first,membername_single,b) a->membername.Append(b->Duplicate()); }

class ListItem {
public:
 Zint leashes,rtid;
 ListItem *next;
 ListItem *prev;
 ListItem(void) { next=prev=null; }
 virtual ~ListItem() {} // Source: Meyers Effective C++, removed due to vile reprocussions, then re-added due to complaints.
 virtual void Virtual(void) {}
 virtual string identity() { ///RTTI///
  string classname=typeid(*this).name();
  string discard;
  const char *q=string_argument(classname.c_str(),&discard); // discards the words "class or struct"
  return string(q);
 }
 virtual bool is( const char *classnamed ) {
  string id=identity();
  return ( !str_cmp(id.c_str(),classnamed) );
 }
 // Note: there is a bug in MSVC2010EE here that makes the following 'virtual' cause the linker to bust.
 /* virtual */ void fromString( const char *st ) {
  string c=identity();
  OUTPUT("ListItem: fromString() called on base class (RTTI class was: %s).\n",c.c_str());
 }
 virtual string toString() {
  return identity()+string(" default virtual toString");
 }
 virtual void BinaryRead( BinaryFile *open ) {} // read data from an already open binary file (ifstream method)
 virtual void BinaryWrite( BinaryFile *open ) {} // write the data to an already open binary file (ifstream method)
 virtual void KeyedRead( KeyedDataStore *open ) {}
 virtual void KeyedWrite( KeyedDataStore *open ) {}
 bool isAfter( ListItem *I ) {
  ListItem *c=I;
  while ( c ) {
   c=c->next;
   if ( c==this ) return true;
  }
  return false;
 }
 bool isBefore( ListItem *I ) {
  ListItem *c=I;
  while ( c ) {
   c=c->prev;
   if ( c==this ) return true;
  }
  return false;
 }
};


// See HANDLE and related macro options in LinkedList.h
template <class T> class Handle : public ListItem {
public:
 T *p;
 Handle():ListItem(){
  p=null;
 }
// This cannot be done:
// Handle( T *p ) : ListItem() {
//  this->p=p;
// }
 void fromString(char *st) {
  if (p) delete p;
  p=new single;
  p->fromString(st);
 }
 virtual string toString() { 
  if (p) return p->toString();
  else return string("");
 }
};

template <class T>
class NamedHandle : public Handle<T> {
public:
 Zstring name;
 NamedHandle() {}
 NamedHandle( string name ) { this->name=name; }
 NamedHandle( const char *n ) { name=string(n); }
};

void recycle( ListItem *p );