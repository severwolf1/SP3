FROM ubuntu
COPY main.cpp .
RUN apt-get update && \
apt-get -y install gdb gcc g++ mono-mcs build-essential gcc-multilib g++-multilib libc6-dev-i386 && \
rm -rf /var/lib/apt/lists/*
RUN gcc -fno-pie -no-pie main.cpp -o lab3 -g -lstdc++
CMD ./lab3