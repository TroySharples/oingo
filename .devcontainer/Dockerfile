FROM debian:latest

# Install packages
RUN apt update -y && apt upgrade -y \
    && apt install -y sudo build-essential cmake git clang gdb imagemagick \
    && rm -rf /var/lib/apt/lists/*

# Add non-root user
ARG USERNAME
RUN groupadd --gid 1000 $USERNAME \
    && useradd --uid 1000 --gid 1000 -s /bin/bash -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME
USER $USERNAME
