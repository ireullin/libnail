
rm -rf ./dev
clear
g++ -o dev dev.cpp -lpthread -lrt -lmysqlclient -DNAIL_TRACE_ENABLE
./dev

