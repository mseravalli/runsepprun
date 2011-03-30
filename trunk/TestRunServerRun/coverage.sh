 #!/bin/bash



#rm debug/*.gc*
rm gcov/*

#make clean
make -f Makefile.Debug


mkdir -p gcov
./RunTestRun

cloc-1.50 ../RunSeppRun/ . > gcov/test_result.txt

gcov -o debug/ main.cpp  | grep "File '../RunSepp" -A 1 >> gcov/test_result.txt
#gcov -o release/ main.cpp  | grep "File '../RunSepp" -A 1 > gcov/Testresult.txt
mv *.gcov gcov
