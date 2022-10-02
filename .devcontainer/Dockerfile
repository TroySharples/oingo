FROM debian:bullseye

RUN apt update -y && apt upgrade -y \
    && apt install -y build-essential cmake git gdb imagemagick \
    && rm -rf /var/lib/apt/lists/*
