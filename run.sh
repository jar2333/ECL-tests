clang -c -O3 -o src/fibonacci.o src/fibonacci.c -fPIC
clang -shared -o src/fibonacci.so src/fibonacci.o

ecl -compile "src/scripts/fibonacci.lisp"

cmake --build /home/jar2333/clorx/build --config Debug --target main -j 14 --
mv ./build/main ./main
./main