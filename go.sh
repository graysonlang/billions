clang++ -std=c++11 billions.cpp -o ~/Desktop/billions && ~/Desktop/billions "$@"
# && time ~/Desktop/test | tee ~/Desktop/out.txt

# 1 billion values output to file =  161.63s user 10.03s system 99% cpu 2:52.51 total
# 9 GB file
