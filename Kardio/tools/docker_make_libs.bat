docker run -it --rm -v $(CURDIR)/Kardio:/app daisy:latest /bin/bash -c "cd /app && dos2unix -n tools/build_libs.sh tools/build_libs_docker.sh && sh tools/build_libs_docker.sh"