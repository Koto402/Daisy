FROM ubuntu:24.04

# Setup environment variables
ENV DEV=/docker/dev

# Setup dev directory
WORKDIR ${DEV}

RUN apt-get update && \
    apt-get clean && \
    apt-get install -y \
		usbutils \
		dfu-util \
		openocd \
        build-essential \
        wget \
        dos2unix \
        python3 && \
        ln -s /usr/bin/python3 /usr/bin/python

RUN wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/10-2020q4/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2 | tar -xj

# Setup GCC path
ENV GCC_PATH=${DEV}/gcc-arm-none-eabi-10-2020-q4-major/bin
ENV PATH=$GCC_PATH:$PATH