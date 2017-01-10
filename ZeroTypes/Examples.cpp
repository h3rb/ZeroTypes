#include "Examples.h"

#include "Strings.h" 

void Examples() {

 ChildItem child;  // it's the child of a ListItem
 child.WhoAmI();
 OUTPUT("\n");
 ChildCollection myChildren;  // It's a collection of children.. (dont cross the streams)
 myChildren.WhoAmI();
 OUTPUT("\n");

 // Adding a custom child to the list.
 ChildItem *c=new ChildItem;
 c->Set("Tiny Tim");
 myChildren.Append(c);

 // More kids!
 c=new ChildItem; c->Set("Annabelle");  myChildren.Append(c);
 c=new ChildItem; c->Set("Simon");      myChildren.Append(c);
 c=new ChildItem; c->Set("Quna");       myChildren.Append(c);
 c=new ChildItem; c->Set("Neha");       myChildren.Append(c);
 c=new ChildItem; c->Set("Garfield");   myChildren.Append(c);
 c=new ChildItem; c->Set("Louis");      myChildren.Append(c);

 OUTPUT(myChildren.toString().c_str());
 OUTPUT("<-- when you don't override\n");
 EACH(myChildren.first,ChildItem,c) OUTPUT("toString() of ChildItem: %s\n", c->toString().c_str() );

 SingleItem item;   // a STATIC item is born...
 SingleItems collection;   // a collection is born...

 collection.Append(new SingleItem);  // a new item is added to a collection

 // Creating, customizing, and adding to a collection.
 SingleItem *newestItem=new SingleItem;
 newestItem->name="My Special Name!!";
 collection.Append(newestItem);

 // The power of macros... whoops we're mixing types into a heterogenous list...
 MyTypeNames myList;
 for ( int i =0; i<10; i++ ) {
  if ( i % 3 == 1 ) myList.Append(new MyTypeName);
  else myList.Append(new ChildItem);
 }

 OUTPUT("Slow RTTI:\n");
 myList.Slow();

 OUTPUT("Faster!\n");
 myList.Fast();

 // babies having babies...
 
 SingleItemChildItems myNewChildren;  // It's a collection of children's children..

 // Adding a custom child's child to the child's child list.
 SingleItemChildItem *c2=new SingleItemChildItem;
 c2->name=("Doll");
 myNewChildren.Append(c2);

 // More kids!
 c2=new SingleItemChildItem; c2->name=("Toy");      myNewChildren.Append(c2);
 c2=new SingleItemChildItem; c2->name=("Binky");    myNewChildren.Append(c2);
 c2=new SingleItemChildItem; c2->name=("Bib");      myNewChildren.Append(c2);

 string out=myNewChildren.toString(); // don't get strung out! har har
 string_as_file(out.c_str(),"data/myfile.txt");
 OUTPUT("Wrote:\n`%s`\n",out.c_str());

 // Handles -- what they are for
 SingleItemChildItemHandles handles;
 handles.Add(c2);  // remember this from above?
 handles.Add((SingleItemChildItem *)myNewChildren.first); // gotta cast..

 // Ok now we have handles, lets go through and print their names
 OUTPUT("Handles...\n");
 EACH(handles.first,SingleItemChildItemHandle,sicih)
  OUTPUT("Handle of: %s is holding element %d of original list\n",sicih->p->name.c_str(), myNewChildren.IndexOf(sicih->p) );
 OUTPUT("  ...complete.\n");

// How to handle times when you want to remove items from a list...
 EACHN(myNewChildren.first,SingleItemChildItem,L,{
  // Removing items from the list and printing the remainder of the list..
  myNewChildren.Remove(L);
  delete L; // don't refer to L after this...
  OUTPUT("List is: %s\n",myNewChildren.toString().c_str());
 })
  // Note that breakpoints don't work inside EACHN or FOREACHN :( SNIFF.. MSFT FWIW&AFAIK FU

  // ZIndexed demo... note when this function exits it runs a rigorous test on ZIndexed template
  ZintGrid grid;
  OurStruct griddy;

  Strings fiels;

  fiels.folder("data/");
  OUTPUT("Filenames found in data/ path:\n");
  EACH(fiels.first,String,s) OUTPUT("%s\n",s->s.c_str());

  // Read back in data written out
  myNewChildren.Clear();  // empties our current list
  myNewChildren.fromString(file_as_string("data/myfile.txt").c_str());  // could have come from the fiels list, but i know what it is already..
  OUTPUT("Read from file: ");
  EACH(myNewChildren.first,SingleItemChildItem,sici) {
   OUTPUT("%s%c",sici->name.c_str(),sici->next?',':'\n');
  }

  // Reversal
  myNewChildren.ReverseOrder();
  OUTPUT("Reversed: "); myNewChildren.PrintNames();  // Is this PrintNames linted Green for you?  What gives MSFT

  // Randomizer using Randoms.h
  myNewChildren.RandomizeOrder();  // Is this RandomizeOrder linted Green for you?  What gives MSFT
  OUTPUT("Randomized: "); myNewChildren.PrintNames();

  // Sorting
  myNewChildren.SortNames(); 
  OUTPUT("Sorted: "); myNewChildren.PrintNames();

  Strings parts;
  parts.SplitPush("these|are|the|parts|not|the|wholes",'|');
  OUTPUT("Parts of the string split by pipe | symbol:\n");
  EACH(fiels.first,String,s) OUTPUT("%s\n",s->s.c_str());

  // The following code shows you the rabbit hole you'll fall down if you twice-delete a list item corrupting all lists accidentally.
#if defined(NEVER)
  myNewChildren.Append(c); // will "append" c which is not of this list, causing an error in LinkedList::Clear()
#endif

}