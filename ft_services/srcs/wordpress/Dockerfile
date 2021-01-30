FROM alpine:latest

COPY    ./srcs/* ./tmp/

RUN     apk update && \
        apk add wget php7 php7-fpm php7-mysqli php7-mbstring php7-json php7-session && \
        apk add --allow-untrusted --no-cache --repository http://dl-cdn.alpinelinux.org/alpine/edge/testing/ telegraf && \
        rm -rf /var/cache/apk/*

RUN	wget https://wordpress.org/wordpress-5.6.tar.gz && tar -xzvf wordpress-5.6.tar.gz && rm wordpress-5.6.tar.gz

RUN	mkdir -p /var/www && mv /wordpress /var/www/
RUN     mkdir -p /etc/telegraf

RUN     mv ./tmp/wp-config.php /var/www/wordpress/ && \
        mv ./tmp/telegraf.conf /etc/telegraf/

EXPOSE  5050

ENTRYPOINT ["/bin/bash", "./tmp/start.sh"]