FROM amd64/debian

WORKDIR /app
COPY . .
RUN apt-get update
#RUN apt-get install make cmake gcc g++ -y
#RUN cd ./third-party/libzmq && mkdir build && cd build && cmake .. && make -j5 && make install
#RUN cd ./third-party/libconfig && mkdir build && cd build && cmake .. && make -j5 && make install
#RUN mkdir build && cd build && cmake .. && make
RUN mkdir build
RUN cp ./deploy/lib*.* /usr/lib
RUN apt-get install libbsd0

CMD ["./deploy/linlog","/app/config.cfg"]