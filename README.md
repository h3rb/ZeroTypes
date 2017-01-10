ZeroTypes Library for Visual C++
---------------

Part of the Lost Astronaut Studios Game Creation Framework in use by http://lostastronaut.com

__ZeroTypes Library__ is a personal helper library written for Visual C++ which performs rudimentary and important initialization of C-types (POD or plain-old data types) for Win32 and x64 systems.  It has been in development since 2007.  I wrote it to make my life easier.  It has, and now for the first time in 2017 it can make /your/ life easier /too/ -- AS SEEN ON http://HANDMADE.NETWORK

I've been adding things to this library since 2006, but some of the functions harken back to 1993 when I first started writing C code.  All in one place.  Very helpful for newcomers who want to start a big project in C++, or for old-timers who want to have a nicer day of C++ coding.

ZeroTypes saves you the trouble of initializing types in the class constructor, provides useful insight into what you would need to, say, compare strings by using operator overloads, and implements two distinct pointer handlers (Zero-Pointer and Zero-Disposable-Pointer).

ZeroTypes was rigorously tested and combed through using cppCheck (http://cppcheck.sourceforge.net/) - one of the most useful tools on the planet for C++ developers.

No need for BOOST BLOAT!  DIY and DRY

BSD LICENSE!!!  Credit due, but otherwise, free and clear for commercial use.

Also included:

 - Super deep random numbers library
 - Random data generated from Atmospheric Data (Random.org)
 - Extensive String manipulation functions
 - Kewl Beans BinaryFile class
 - Powerful optimized LinkedList class with MACROS for easy daily use
 - Super-simple JSON reader/writer
 - Awesome error code reading functions specifically for WinAPI

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
 /* automatically destroys temp on destroy of A */
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

Why use this over Boost?

Well, it's lighter weight, specialized to only a handful of basic important types and their interoperability, and while powerful, Boost is bloat, and we are not bloat (sort-of).  Hey, you can use this WITH BOOST if you want.  No one is stopping you.

ZeroTypes implements the following classes:

* Zint
* Zbyte
* Zuint
* Zdouble
* Zfloat
* Zbool
* Zstring

ZeroTypes also comes with an optimized LinkedList base class and ListItem base class, and on top of these, there are helpers for sets of strings, which are folded into Zstring.

* ListItem (implements RTTI)
* LinkedList
* String : ListItem
* Strings : LinkedList

Additionally, a lightweight template for handling one-or-two-dimensional arrays built to be fast, portable and powerful:
* ZIndexed

Project TODO

Some of the code works on Linux. With a few changes, it will work on x64.  I'll get to this, or maybe you can by submitting a pull request on the github

__To Do:__

* Implement 64-bit version
* Make more Linux-friendly

You also get a slough of string helper functions, super useful macros collected since 1992, and a deep sense of resentment for casting.  All implemented for Microsoft Visual Studio's kinda wonky interpretation of C++.  Maybe one day I'll write documentation for all of this, but for now, my best advice is to read the code!
