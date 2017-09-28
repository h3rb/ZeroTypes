ZeroTypes Library for Visual C++
---------------
BSD LICENSE
Credit due, but otherwise, free and clear for commercial use.
See License.txt for details.

![alt tag](https://raw.githubusercontent.com/h3rb/ZeroTypes/master/zero.png)

Part of the Lost Astronaut Studios Game Creation Framework in use by http://lostastronaut.com

__ZeroTypes Library__ is a personal helper library written for Visual C++ which performs rudimentary and important initialization of C-types (POD or plain-old data types) for Win32 and x64 systems.  It has been in development under the name ZeroTypes since 2007.  I wrote it to make my life easier.  It has, and now for the first time in 2017 it can make *your* life easier *too* -- AS SEEN ON https://zero.handmade.network/

I've been adding things to the informal predecessor of this library since 2006, but some of the functions harken back to 1992 when I first started writing C code.  All in one place.  Very helpful for newcomers who want to start a big project in C++, or for old-timers who want to have a nicer day of C++ coding.

ZeroTypes saves you the trouble of initializing types in the class constructor, provides useful insight into what you would need to, say, compare strings by using operator overloads, and implements two distinct pointer handlers (Zero-Pointer and Zero-Disposable-Pointer).

ZeroTypes was rigorously tested and combed through using cppCheck (http://cppcheck.sourceforge.net/) - one of the most useful tools on the planet for C++ developers who make applications (not firmware).

C++ is a generalized language that works on the lowest and highest levels.  For this reason, it has some specific annoyances that occur at the application and library level that are not as prevalent at the embedded or lowest level.  ZeroTypes solves problems for application developers by being an embeddable snippet providing utility saving time and grief.

Also included:

 - Super deep random numbers library
 - Random data generated from Atmospheric Data (Random.org), pseudorandoms and uniform() randoms
 - Extensive String manipulation functions
 - Kewl Beans BinaryFile class
 - Powerful optimized LinkedList class with MACROS for easy daily use
 - Super-simple JSON reader/writer
 - Awesome error code reading functions specifically for WinAPI
 - Nifty geometry helpers like distance and angle helpers for simple game AI
 - Utility functions galore

Some contributions marked with other licenses or links to the tutorial it came from.  Generally all were compatible with MIT or BSD, or were public domain.   

Contributors: Makoto Matsumoto and Takuji Nishimura, Sean O'Neil, Ken Perlin, NVIDIA, Daniel White, Alan Paeth, René Nyffenegger, dhPoware, Emil Persson (Humus)

Examples
========

Before ZeroTypes:

```c++
class A {
 A() { x=0; }  // If you didn't do this, you would have problems
 int x;
};
```

After ZeroTypes:

```c++
class A {
 Zint x;
};
```

Much easier to write and read (humanly), yet it accomplishes the same thing.

Pointers before ZeroTypes:

```c++
class A {
 int *b;
 int *temp;
 A() { b=nullptr; temp=new int; }
 ~A() { delete temp; }
};
```

Pointers after ZeroTypes:

```c++
class A {
 Zpointer<int> b;
 Zdisposable<int> temp;
 A() {
  temp.Instantiate();
 }
 /* automatically destroys temp on destroy of A's instance but not b */
};
```

You can also write using ZeroTypes shorthand:

```c++
class A {
 Zp<int> b;
 Zdis<int> temp;
};
```

Strings before ZeroTypes:
```c++
class A {
 std::string alpha,beta;
 A() { alpha=string(""); beta=string("beta"); }
 bool Compares() { return ( alpha.compare(beta) == 0 ); }
};
```

Strings after ZeroTypes:

```c++
class A {
 Zstring alpha,beta;
 A() {}
 bool Compares() { return alpha == beta; }
};
```

No need for BOOST BLOAT!  DIY and DRY - Why use this over Boost or STL?

Well, it's lighter weight, specialized to only a handful of basic important types and their interoperability, and while powerful, Boost is bloat, and we are not bloat (sort-of).  Hey, you can use this WITH BOOST if you want.  No one is stopping you.

ZeroTypes implements the following Z-POD classes:

* Zint
* Zbyte
* Zuint
* Zdouble
* Zfloat
* Zbool
* Zstring

When should I use these?

In class descriptions almost always, as "properties" -- 

```c++
class MyClass {
public:
 Zint foo;
 Zdouble bar;
 Zbool baz;
};
```

Usually not as a parameter unless the case is a pointer or reference to something you are going to modify, but since they are POD-types, usually they are already wrapped in a class and won't be used directly as a parameter.  Or, they are POD-types are you will be return a non-pod type.

```c++
// Don't do this unless you really want to:
void functionname( Zint foo );

// It's better to do this, because Z-pods were designed to be POD-helpers, rather than replacements:
void functionname2( int foo );
Zint myint;
functioname2(myint);

//I can imagine you may need to do this:
void functionname3( Zint *out );
// You could also do this instead:
void functionname4( Zint &out );
// Or just this:
void functionname5( int *out );
functioname5(&myint.value);
```

Never as a return value, because there is no need to do so.  However, you may use them in a class or other structure that is a return value just fine.

You can also use them as globals, though it is often not necessary to do so.

You can use them as a local variable, but generally it can be avoided and should be when no value to using a Z-pod, though ultimately, it can be -- for the other ZeroTypes, though Zpointer locals sometimes make sense:

```c++
class MyItem : public ListItem { Zint desired; };
class MyList : public LinkedList { .. };
MyList myList;
void oop( int desired ) {
  Zp<Somewhere> ptr;
  EACH(myList.first,MyItem,p) if ( p->value == desired ) ptr=p;
  if ( ptr ) {
   // do something
  }
  Zint x;  // x is 0
  Zint y=5;  // you could just use an int... but no big deal if you do this, however it can be avoided.
}
```

You generally want to use them in situations where data will be eventually converted to or from a string input.  I originally wrote them for use in OpenGL graphics applications, games and gaming servers (on Linux).  Using them protects against compiler inconsistencies across multiple platforms. Z-pods is designed to assure you have initialized values, and optimizers will eliminate any "double initialization" woes you may feel you'll face, in the case you wish to provide a default anyway.  

Using Z-pods, you can type less, write more uniform implementations avoiding uninitialized class variables, and you can even get out of having to create a constructor, for instance in the case where you wish to "pass down" a virtual constructor to a child class. (See the section below "Why would I want to avoid a constructor in C++?")

Due to the built-in string/data translation, easily store and retrieve state from a string in memory or file - operations that are common in applications that require reading and writing files and states.  It also makes std::string operability function more like Java string concatenations, and helps you avoid relying on << chaining (useful only in C++ and C#, not in Java, Javascript or PHP), and of course avoiding the whole printf() thing to format a string (unless you like this).  

If you want to easily port your code with minimal syntax changes to Processing.org IDE or Javascript by simply removing the "Z" it will generally be similar to Java (Find/Replace to translate).  Also, I have sometimes converted PHP code quite easily back to C++ and visa versa using ZeroTypes snippets to help form my code, without losing performance and increasing application stability on the C++ side, however this is only truly realized in value when you are using the LinkedList, Strings and Zstring classes, which have functionality that mimics common language features of both.

When should I cast these to their target data type?

When you are passing a Z-POD to a function that has multiple prototypes, for example std::abs() which takes a double, int or float, it is best to overcome interoperability overload features of the Z-POD by casting to enforce strict typing, or use their .value property to get at the wrapped POD.  A side effect of this necessary step is that you are certain, in situations where you are using ints and doubles together, for instance, that you are casting properly and getting the desired output data.  

Consider:
```c++
// It's not always safe to assume one compiler to another,
// in a cross-platform or multi-platform context, will
// treat this:
 int x=50.5;
 double e=5.5*x;
// the way you think it should... did you mean 50.0 X 5.5 or 5 * 50 or 51 * 5.5 or ...
 int x=2;
 double f=1.0/x; // might be 0.5
 double g=1/x; // might be 0.0
```

This happens a lot when doing graphics applications as well as science applications.  So, the cast is useful not only to be explicit to the compiler, but also when you read it later you can double check your math against an "annotated" equation rather than a guessing game scenario.  It's also necessary when using printf() and other variable argument functions to be explicitly a POD type, so always cast your Zint and Zdouble to the desired format specifier (like %L or %f, which are sadly also platform specific).

There is also the matter of ambiguity, which is generally why I tend to avoid Zints and Zdoubles as function or method function parameters.  If I do end up using one as a last resort, I make sure to use a reference (unless a pointer is necessary), but rarely as a "copy" op, though it's not clear if that makes much of a difference.  When there is no ambiguity, the compiler will correctly find the right overload.

Example of type ambiguity as an artifact of using ZeroType POD-non-POD classes:

```c++
class Foo {
 Zint x;
 void absolute_value_Ex1() {
  return std::abs((double)x);
 }
 void absolute_value_Ex2() {
  return std::abs(x.value);
 }
 double absolute_value_Ex3_compiler_error_in_ambiguity() {
  return std::abs(x); 
  /* How would the compiler know which "x" you want due 
  to the interoperability features of Zint's cast overloading?
  If you're lucky, it will pick double, but you can't be too sure...
  The fix for this is in example Ex1. */
 }
 void my_abs(int i) { return std::abs(i); }
 int absolute_value_Ex4_works_fine_no_ambiguity() { return my_abs(x); }
 void my_abs(char c, int i) { cout << c; return std::abs(i); }
 int absolute_value_Ex5_works_fine_no_ambiguity() { return my_abs('y',x); }
};
```

Zpointer's .pointer caveat

Generally it's a good idea to use a Zpointer's .pointer if you absolutely need the pointer.  There are some edge cases where Zpointer's pointer to the wrapper class instance is accidentally substituted (at least in Visual Studio).  You'll know immediately if your code around there doesn't work. However, within itself, Zpointer works fine without the .pointer specificity.  The same can be said for Zdisposable.  One example of this is the ! operator is sometimes misconstrued.  My speculation is that when you have a Zpointer pointer pointer.  See below., where "m" and "preview" and "n" and "preview" are all Zpointers.

```c++
m->preview = n->preview;  // This always works if both preview properties are Zp<SameClass>
if ( !m ) { /* always works */ }
if ( !m->preview ) {
 /* I think this works most of the time in Visual Studio, 
    but sometimes it defaults to true because it's checking 
    if m's "Zpointer" has a value rather than its pointer's Zpointer. 
    There is no good reason for this, it's an error in Microsoft's
    compiler/debugger as it is inconsistent.  Reports to them
    have gone without response or action. */
}
if ( !m->preview.pointer ) { /* this definitely works! */ }
if ( m->preview.pointer != nullptr ) { /* this definitely works! */ }
```

ZeroTypes also comes with an optimized LinkedList base class and ListItem base class, and on top of these, there are helpers for sets of strings, which are folded into Zstring.

* ListItem (implements RTTI)
* LinkedList
* String : ListItem
* Strings : LinkedList

Include "Randoms.h" which implements a variety of different approaches, some original, some borrowed:

* RandomSet : ListItem
* RandomSets : LinkedList
* Random : LinkedList
* Randoms : LinkedList

Additionally, a lightweight template for handling one-or-two-dimensional arrays built to be fast, portable and extendable:

* ZIndexed

Zindexed allows you to, through a template, reuse basic C arrays in place of std::vector and std:set -- when you need to have indexed data looked up easily.  Unlike vector or set, you can use ZIndexed to hold 2-dimensional arrays, and treat them as both linear and 2-dimensional without having to rewrite or reinvent the ```x+y*w``` conversion (and the even more esoteric backward-conversion from a linear value to a 2-d coordinate).  You can then use double-templating and triple-templating (et cetera) to extend the dimensionality beyond.  It also encourages the use of a for-loop iterator, which can be easily translated into other languages.

In ZIndexed, Search, Delete and Insert operations are not handled in the template for you -- this is intentional as often these operations have additional requirements and reprocussions.  Normally, you have to write these specialized functions anyway when using an std::vector and std::set (or std::list, std::deque).  This could be done as a virtual, perhaps the class will evolve slightly more later, but for now it's designed intentionally to be done in the following way:

```c++
class Node { public: Zint value; Zstring name; operator =(Node &in){ value=in.value; name=in.name; } };
class Nodes : public ZIndexed<Node> {
 void Insert( int before, Node &input ) {
  // .Increase() to grow by one
  Increase();
  // Iterate backward from the end, copying i-1 to i
  for ( int i=(int)length-1; i>before; i++ ) {
   (*this)[i]=(*this)[i-1];
  }
  // Insert node
  (*this)[before]=input;
  // Perform any unique calculations, etc (equivalent of OnInsert virtual)
 }
 bool Delete( int cell ) {
  if ( !( cell >= 0 && cell < (int) length ) ) return false; // out of bounds
  // Copy values then call .Size(length-1)
  for ( int i=cell; i < (int)length; i++ ) {
   (*this)[i] = (*this)[i+1];
  }
  Size(length-1,true);  // true tells ZIndexed to "keep" the values rather than reinit the whole array.
  return true; // deletion successful
 }
};
```

Why would I want to avoid a constructor in C++?

In C++ you sometimes need the features of other languages, but don't have them at your disposal.  

In C++:
* Constructors cannot be virtual.
* Default constructors (constructors declared in the parent and not the child in the simplest form with no parameters) are special.
* Constructors can call virtual functions, however the virtual functions are not called on the inherited function, as is the case in other languages like C# and eC.

Consider:

```c++
class A {
public: A() { Init(); }
virtual void Init() { cout << 'A'; }
}; 
class B : A {
public: virtual void Init() { cout << 'B'; }
}; 
class C : B {
public: virtual void Init() { cout << 'C'; } }; 
int main() { C c; }
```

The output of the above is "A" You might think "Well what if I had a couple of constructors, B():A(){} and C():B() {}" .. it would still print "A".  

So the value of such a constructor is very limited.  It only really provides initialization for the class itself.
Almost always this kind of "default constructor" cannot be used in tandem with a virtual function to provide the expected result (or desired result).  In dynamic languages, like C# or eC, you can use a virtual function in a constructor without much issue.

Since it has little utility, it can be avoided altogether, keeping the code cleaner, and avoiding the habit of falling into this trap, and all of the other traps like: https://stackoverflow.com/questions/3156597/override-or-remove-an-inherited-constructor

__To Do:__

Some of the code works on Linux. With a few changes, it will work on x64.  I'll get to this, or maybe you can by submitting a pull request on the github

* Make more Linux-friendly
* Make more Mac-friendly

You also get a slough of string helper functions, super useful macros collected since 1992, and a deep sense of resentment for casting.  All implemented for Microsoft Visual Studio's kinda wonky interpretation of C++.  Maybe one day I'll write documentation for all of this, but for now, my best advice is to read the code!
