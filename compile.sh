
rm -rf ./example
g++ -o example example_filesystem.cpp -lpthread -lrt -DNAIL_TRACE_ENABLE
