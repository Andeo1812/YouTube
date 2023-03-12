FROM nginx

WORKDIR /etc/nginx

COPY /configs/nginx.conf /etc/nginx/nginx.conf
RUN mkdir static/tests
COPY  /tests /etc/nginx/static/tests
