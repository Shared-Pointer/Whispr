FROM fedora:latest

RUN dnf install --assumeyes \
    nano \
    curl \
    vim \
    g++ \
    htop \
    make \
    cmake \
    && dnf clean all

WORKDIR /Whispr

COPY . .

#RUN mkdir build/ \
#&& cd build/ \
#&& CMAKE_CXX_COMPILER="usr/bin/g++" \
#&& cmake .. \
#&& make

EXPOSE 8080

CMD ["/bin/bash"]
