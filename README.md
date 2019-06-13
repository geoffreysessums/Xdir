# Xdir

Geoffrey Sessums

Systems Programming (Fall 2017)

Language: C

## Description

Xdir is a custom directory command that uses low level C I/O functions to display the contents of the directory by default plus additional file and directory details when passed switches.

## What I Learned

* First thing I learned...
* Next I learned...

### Command Descriptions

### Xdir Output

## Installation

From the command-line:  

Clone the repository:  
$ ```git clone https://github.com/geoffreysessums/Xdir.git```

Change to the Xdir directory.  
Compile xdir.c:  
$ ```make xdir.c```

## Usage

Run command:

xdir *directory*

xdir *directory* *switches*

Example without switches:

$ `xdir Data`

    Data :  
    Program2
    Program5  
    Program4
    Program3
    file4
    file5
    file6

Example with -l switch:
$ ```xdir Data -l```
  Data :
      Program2 D 0 blks 192 bytes
      Program5 D 0 blks 192 bytes
      Program4 D 0 blks 224 bytes
      Program3 D 0 blks 192 bytes
      file4 F 8 blks 87 bytes
      file5 F 8 blks 167 bytes
      file6 F 8 blks 121 bytes

Example with -a switch:
$ ```xdir Data -a```
  Data :
      .
      ..
      Program2
      Program5
      Program4
      Program3
      file4
      file5
      .mydot
      file6

Example with both -l and -a switches:
$ ```xdir Data -l -a```
  Data :
      . D 0 blks 320 bytes
      .. D 0 blks 384 bytes
      Program2 D 0 blks 192 bytes
      Program5 D 0 blks 192 bytes
      Program4 D 0 blks 224 bytes
      Program3 D 0 blks 192 bytes
      file4 F 8 blks 87 bytes
      file5 F 8 blks 167 bytes
      .mydot F 8 blks 25 bytes
      file6 F 8 blks 121 bytes

## Credits

Author: Geoffrey Sessums

## License

MIT License

Copyright (c) 2017 Geoffrey Sessums

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
