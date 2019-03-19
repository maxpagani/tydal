# tydal
TYpe Definition Awesome Language

(C) 2016 Massimiliano Pagani - maxpag@gmail.com

## What is Tydal
Tydal is a type specification language. The design goal is to have a simple and intuitive syntax that can be easily employed to specify mainly JSON types, but that can be also used to specify other structured data such as storage or message formats.
There are many other type specification languages but they lack the clarity and intuitiveness or they are too specialized for a specific application (e.g. web services).

## What does this project provide
This project provides a document that defines Tydal and a translator that can be used to compile Tydal texts into C++, C, Scala or Java type source code for use in your own application. Your application run time will not need any extra library nor the source code will have any dependency on tydal.

## Compile and Installing
Build is based on cmake. First you need to compile tydal. Execute a shell in the root project directory and then:
```
> cd Builds
> cmake -G "Unix Makefiles" ../Sources
> make
```

In order to install (not yet supported), type the following command
```
> make install
```
