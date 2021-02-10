FROM alpine:latest

COPY    ./srcs/* ./tmp/

RUN     apk update && \
        apk add wget php7 php7-fpm php7-mysqli php7-mbstring php7-json php7-session && \
        wget https://wordpress.org/wordpress-5.6.tar.gz && \
        tar -xzvf wordpress-5.6.tar.gz && \
        rm wordpress-5.6.tar.gz && \
        rm -rf /var/cache/apk/*

RUN	mkdir -p /var/www && mv /wordpress /var/www/
RUN     mkdir -p /etc/telegraf

RUN     mv ./tmp/wp-config.php /var/www/wordpress/

EXPOSE  5050

ENTRYPOINT sh start.sh