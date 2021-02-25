FROM alpine:3.12.0

RUN apk update && \
	apk add wget php7 php7-fpm php7-mysqli php7-mbstring php7-json php7-session && \
	apk add telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache && \
	wget https://wordpress.org/wordpress-5.6.tar.gz && \
	tar -xzvf wordpress-5.6.tar.gz && \
	rm wordpress-5.6.tar.gz && \
	rm -rf /var/cache/apk/*

RUN	mkdir -p /var/www && mv /wordpress /var/www/

COPY ./srcs/wp-config.php /var/www/wordpress/
COPY ./srcs/telegraf.conf /etc/
COPY ./srcs/start.sh /tmp/

EXPOSE 5050

ENTRYPOINT sh /tmp/start.sh