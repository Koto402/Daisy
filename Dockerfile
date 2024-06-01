FROM ubuntu:22.04

# Setup environment variables
ENV DEV /dev

# Setup dev directory
WORKDIR ${DEV}

RUN apt-get update && \
    apt-get clean && \
    apt-get install -y \
        build-essential \
        dfu-util \
        openocd \
        wget \
        python3 && \
        alias python=python3