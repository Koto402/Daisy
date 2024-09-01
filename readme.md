# Daisy Kardio

This repo contains code for experimenting with various DSP algorithms on the Daisy seed MCU.

## Installation

Docker is used for building the project and the provided Dockerfile will handle installation of dependencies.

For debugging Openocd is required.

Clone the git repo and create a docker image with the included makefile:

```sh
make docker_create_image
```

Note when calling the below scripts there may be an issue using bash. Use cmd instead if this call fails.
Build the example projects:
```sh
make build_examples
```

Build the kardio project:
```sh
make build_kardio
```