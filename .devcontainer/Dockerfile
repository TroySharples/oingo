FROM debian:bullseye

RUN apt update -y && apt upgrade -y \
    && apt install -y build-essential cmake git curl \
    && rm -rf /var/lib/apt/lists/*
