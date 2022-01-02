#! /bin/bash

rm -f libScanner.so
g++ -std=c++11 -fPIC -shared AndPattern.cpp CharPattern.cpp CodeGenerate.cpp Config.cpp Content.cpp Lexical.cpp OrPattern.cpp Pattern.cpp StringPattern.cpp Rule.cpp -o libScanner.so

rm -f Scanner
g++ -std=c++11 Scanner.cpp -L. -lScanner -o Scanner -Wl,-rpath .

./Scanner c_front.s

rm -f libc_front.so
g++ -std=c++11 -fPIC -shared CodeGenerate.cpp -L. -lScanner -o libc_front.so -Wl,-rpath .
