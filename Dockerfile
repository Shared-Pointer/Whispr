FROM ubunut

RUN dnf update &&
    dnf install --assumeyes \
    nano \
    curl \
    vim \
    gcc \
    htop \
    make \
    cmake \
    && dnf clean all

WORKDIR /Whispr

COPY . .

RUN mkdir build/ && cd build/ && cmake .. && make && cd ..

EXPOSE 8080

CMD ["/bin/bash"]
