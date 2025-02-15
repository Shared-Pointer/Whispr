FROM fedora:latest

RUN dnf install --assumeyes \
    nano \
    curl \
    vim \
    gcc \
    htop \
    cmake \
    && dnf clean all

WORKDIR /Whispr

EXPOSE 8080

CMD ["/bin/bash"]
