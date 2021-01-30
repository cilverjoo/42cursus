FROM alpine:latest

#install all necessary packages
RUN apk update && \
    apk upgrade && \
    apk add bash && \
    apk add curl php7 php7-fpm php7-opcache php7-gd php7-mysqli php7-zlib php7-curl php7-mbstring php7-json php7-session && \
    apk add telegraf --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ --allow-untrusted --no-cache && \
    rm -rf /var/cache/apk/*


RUN wget http://files.directadmin.com/services/all/phpMyAdmin/phpMyAdmin-5.0.2-all-languages.tar.gz && \
    tar -xvf phpMyAdmin-5.0.2-all-languages.tar.gz && \
    rm phpMyAdmin-5.0.2-all-languages.tar.gz && \
    mv phpMyAdmin-5.0.2-all-languages phpmyadmin

RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.15.2_linux_amd64.tar.gz && \
    tar -zxf telegraf-1.15.2_linux_amd64.tar.gz && \
    rm telegraf-1.15.2_linux_amd64.tar.gz && \
    mv mv telegraf-1.15.2 telegraf