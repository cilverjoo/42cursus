FROM alpine:latest

#install all necessary packages
RUN apk update && \
    apk upgrade && \
    apk add bash && \
    apk add apk add wget php7 php7-fpm php7-mysqli php7-mbstring php7-json php7-session && \
    apk add telegraf --repository telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache && \
    rm -rf /var/cache/apk/*

RUN wget https://files.phpmyadmin.net/phpMyAdmin/4.9.2/phpMyAdmin-4.9.2-all-languages.tar.gz && \
    tar -xvf phpMyAdmin-4.9.2-all-languages.tar.gz && \
    rm phpMyAdmin-4.9.2-all-languages.tar.gz && \
    mv phpMyAdmin-4.9.2-all-languages /var/www/phpmyadmin

EXPOSE 5000

ENTRYPOINT sh sratr.sh