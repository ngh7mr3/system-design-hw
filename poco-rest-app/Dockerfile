FROM ubuntu:20.04 as builder
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get upgrade
RUN apt-get install -yq build-essential autoconf libtool git\
                            pkg-config gcc g++ cmake \
                            libssl-dev zlib1g-dev librdkafka-dev libmysqlclient-dev libboost-all-dev

# build Google Test
RUN git clone https://github.com/google/googletest.git
RUN cd googletest && mkdir build && cd build && cmake .. -DBUILD_SHARED_LIBS=ON -DINSTALL_GTEST=ON -DCMAKE_INSTALL_PREFIX:PATH=/usr && make -j8 && make install && ldconfig

# build Poco
RUN cd
RUN git clone -b master https://github.com/pocoproject/poco.git
RUN cd poco && mkdir cmake-build && cd cmake-build && cmake .. && cmake --build . --config Release && cmake --build . --target install

FROM builder as src
COPY . /server
RUN cd /server && mkdir bin && cd bin && cmake .. && cmake --build . --target install

# maybe somehow copy only libraries
WORKDIR /server
RUN ./bin/gtests

EXPOSE 8080

### https://github.com/pocoproject/poco/issues/2543
ENV LD_LIBRARY_PATH=/usr/local/lib
###

CMD ["./bin/server"]
