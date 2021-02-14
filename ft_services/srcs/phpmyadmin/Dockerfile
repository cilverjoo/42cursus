FROM alpine:latest

#install all necessary packages
RUN apk update upgrade && \
    apk add wget php7 php7-fpm php7-mysqli php7-mbstring php7-json php7-session && \
    rm -rf /var/cache/apk/*

RUN wget https://files.phpmyadmin.net/phpMyAdmin/4.9.2/phpMyAdmin-4.9.2-all-languages.tar.gz && \
    tar -xvf phpMyAdmin-4.9.2-all-languages.tar.gz && \
    rm phpMyAdmin-4.9.2-all-languages.tar.gz && \
    mkdir -p /var/www/phpmyadmin && \
    mv phpMyAdmin-4.9.2-all-languages /var/www/phpmyadmin

EXPOSE 5000


COPY ./srcs/config.inc.php /var/www/phpmyadmin/
COPY ./srcs/start.sh /tmp/

ENTRYPOINT sh /tmp/start.sh