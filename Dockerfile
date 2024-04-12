FROM gcc:latest

RUN  mkdir /usr/src/zzy

COPY ./* /usr/src/zzy

WORKDIR /usr/src/zzy

RUN  gcc test.cpp 

CMD ["./test.out"]
