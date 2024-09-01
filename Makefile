build_examples:
	docker run -it --rm -v $(CURDIR)/DaisyExamples:/app daisy:latest \
	/bin/bash -c "cd /app && \
	chmod +x ci/build_libs_docker.sh && \
	dos2unix -n ci/build_libs.sh ci/build_libs_docker.sh && \
	sh ci/build_libs_docker.sh && \
	dos2unix -n ci/build_examples.py ci/build_examples_docker.py && \
	python ci/build_examples_docker.py"


build_kardio:
	docker run -it --rm -v $(CURDIR)/Kardio:/app daisy:latest \
	/bin/bash -c "cd /app && \
	sh tools/build_libs.sh"

docker_create_image:
	docker build -t daisy:latest .