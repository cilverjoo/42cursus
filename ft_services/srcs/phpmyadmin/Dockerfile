FROM alpine:3.12.0

#install all necessary packages
RUN apk update update
RUN apk add wget nginx php7 php7-fpm php7-common php7-iconv php7-json php7-gd php7-curl php7-xml php7-mysqli php7-imap php7-cgi fcgi php7-pdo php7-pdo_mysql php7-soap php7-xmlrpc php7-posix php7-mcrypt php7-gettext php7-ldap php7-ctype php7-dom
RUN	apk add telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache

RUN wget https://files.phpmyadmin.net/phpMyAdmin/4.9.2/phpMyAdmin-4.9.2-all-languages.tar.gz && \
    tar -xvf phpMyAdmin-4.9.2-all-languages.tar.gz && \
    rm phpMyAdmin-4.9.2-all-languages.tar.gz && \
	mv phpMyAdmin-4.9.2-all-languages phpmyadmin

RUN apk add supervisor openrc --no-cache && \
	rm -rf /var/cache/apk/*

RUN mkdir -p /run/nginx

COPY ./srcs/config.inc.php /phpmyadmin/

RUN mkdir -p /usr/share/webapps && \
	mv /phpmyadmin /usr/share/webapps/phpmyadmin && \
	chmod -R 777 /usr/share/webapps/ && \
	ln -s /usr/share/webapps/phpmyadmin /var/www/phpmyadmin

COPY ./srcs/telegraf.conf /etc/telegraf/
COPY ./srcs/nginx.conf /etc/nginx/
COPY ./srcs/supervisord.conf /etc/
COPY ./srcs/start.sh /tmp/

EXPOSE 5000

CMD sh /tmp/start.sh