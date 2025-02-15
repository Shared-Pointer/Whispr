FROM fedora:latest

RUN dnf install -y \
    nano \
    curl \
    vim \
    gcc \
    htop \
    && dnf clean all

WORKDIR /Whispr

EXPOSE 8080

CMD ["/bin/bash"]
