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

ZeroTypes was rigorously tested and combed through using cppCheck (http://cppcheck.sourceforge.net/) - one of the most useful tools on the planet for C++ developers.

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

```
class A {
 A() { x=0; }  // If you didn't do this, you would have problems
 int x;
};
```

After ZeroTypes:

```
class A {
 Zint x;
};
```

Much easier to write and read (humanly), yet it accomplishes the same thing.

Pointers before ZeroTypes:

```
class A {
 int *b;
 int *temp;
 A() { b=nullptr; temp=new int; }
 ~A() { delete temp; }
};
```

Pointers after ZeroTypes:

```
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

```
class A {
 Zp<int> b;
 Zdis<int> temp;
};
```

Strings before ZeroTypes:
```
class A {
 std::string alpha,beta;
 A() { alpha=string(""); beta=string("beta"); }
 bool Compares() { return ( alpha.compare(beta) == 0 ); }
};
```

Strings after ZeroTypes:

```
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

In class descriptions almost always, as "properties" -- usually never as a parameter.  You can also use them as globals.

When should I cast these to their target data type?

When you are passing a Z-POD to a function that has multiple prototypes, for example std::abs() which takes a double, int or float, it is best to overcome interoperability overload features of the Z-POD by casting to enforce strict typing, or use their .value property to get at the wrapped POD.

Example:

```
class Foo {
 Zint x;
 void absolute_value_Ex1() {
  return std::abs((double)x);
 }
 void absolute_value_Ex2() {
  return std::abs(x.value);
 }
 void absolute_value_Ex3_compiler_error_in_ambiguity() {
  return std::abs(x); 
  /* How would the compiler know which "x" you want due 
  to the interoperability features of Zint's cast overloading? */
 }
};
```

In some situations, 

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

Additionally, a lightweight template for handling one-or-two-dimensional arrays built to be fast, portable and powerful:
* ZIndexed

__To Do:__

Some of the code works on Linux. With a few changes, it will work on x64.  I'll get to this, or maybe you can by submitting a pull request on the github

* Make more Linux-friendly
* Make more Mac-friendly

You also get a slough of string helper functions, super useful macros collected since 1992, and a deep sense of resentment for casting.  All implemented for Microsoft Visual Studio's kinda wonky interpretation of C++.  Maybe one day I'll write documentation for all of this, but for now, my best advice is to read the code!
