/*********************************************************************************************
 *  __    __________________   ________________________________   __________  ________       *
 * /\ \  /\  __ \  ___\__  _\ /\  __ \  ___\__  _\  == \  __ \ "-.\ \  __ \ \/\ \__  _\ (tm) *
 * \ \ \_\_\ \/\ \___  \/\ \/ \ \  __ \___  \/\ \/\  __<\ \/\ \ \-.  \  __ \ \_\ \/\ \/      *
 *  \ \_____\_____\_____\ \_\  \ \_\ \_\_____\ \_\ \_\ \_\_____\_\\"\_\_\ \_\_____\ \_\      *
 *   \/_____/_____/_____/\/_/   \/_/\/_/_____/\/_/\/_/\/_/_____/_/ \/_/_/\/_/_____/\/_/      *
 *    --------------------------------------------------------------------------------       *
 *     Lost Astronaut Game Development Framework (c) 2007-2017 H. Elwood Gilliland III       *
 *********************************************************************************************
 * BSD LICENSE - See accompanying "License.txt" for details.                                 *
 *********************************************************************************************/
#pragma once

#include "BinaryFile.h"

class BinaryFileTest {
public:
 BinaryFileTest() {
  FileWrite();
  FileRead();
 }
 void FileRead() {
  BinaryFile read1("data/out/test1.bin",false);
  float f1,f2;
  read1.read(&f1);
  read1.read(&f2);
  OUTPUT("F1=%f F2=%f ", f1,f2);
  BinaryFile read2("data/out/test2.bin",false);
  unsigned int i,j;
  read2.read(&i);
  read2.read(&j);
  OUTPUT("i=%d j=%d ", i,j);
  BinaryFile read3("data/out/test3.bin",false);
  uint32 a,b;
  read3.read(&a);
  read3.read(&b);
  OUTPUT("a=%d b=%d\n",(unsigned int) a, (unsigned int) b);
 }
 void FileWrite() {
  BinaryFile file1("data/out/test1.bin",true);
  file1.scrawl(1.0f);
  float f=2.0f;
  file1.scrawl(f);
  BinaryFile file2("data/out/test2.bin",true);
  file2.scrawl((unsigned int) 1);
  unsigned int i=2;
  file2.scrawl(i);
  BinaryFile file3("data/out/test3.bin",true);
  unsigned int j=2;
  file3.scrawl( (uint32) 1 );
  file3.scrawl( (uint32) j );
 }
};
