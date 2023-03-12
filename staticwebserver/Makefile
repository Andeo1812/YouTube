IMAGE = static-web-server
CONTAINER = http-highload
PORT = 8080
NGINX = 8888

# main
build:
	make clear
	mkdir build && cd build && cmake .. && $(MAKE)

build-docker:
	docker build -f ./docker/Dockerfile --tag $(IMAGE) .

docker-run:
	docker run --memory 2G -p $(PORT):$(PORT) --name $(CONTAINER) -t $(IMAGE)

docker-stop:
	docker stop $(CONTAINER)

docker-rm:
	docker rm -vf $(CONTAINER) || true

# Nginx
build-docker-nginx:
	docker build --no-cache -t nginx -f ./docker/nginx.Dockerfile .

docker-run-nginx:
	docker run --memory 2G -p $(NGINX):$(NGINX) --name nginx -t nginx

docker-stop-nginx:
	docker stop nginx

docker-rm-nginx:
	docker rm -vf nginx || true

# Tests
func-test:
	./functest.py

bench-static-web-server:
	wrk -t12 -c400 -d30s 'http://127.0.0.1:$(PORT)/tests/splash.css'

bench-nginx:
	wrk -t12 -c400 -d30s 'http://127.0.0.1:$(NGINX)/tests/splash.css'

# Utils
clear:
	rm -Rf build
