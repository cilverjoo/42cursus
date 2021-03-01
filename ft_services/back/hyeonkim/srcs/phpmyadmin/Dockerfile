FROM alpine:3.12

RUN apk update && \
	apk add nginx && \
	mkdir /run/nginx && \
	touch /var/run/nginx/nginx.pid && \
	apk add php7 php7-fpm php7-opcache php7-gd php7-mysqli \
	php7-zlib php7-curl php7-mbstring php7-json php7-session && \
	wget https://files.phpmyadmin.net/phpMyAdmin/4.9.5/phpMyAdmin-4.9.5-all-languages.tar.gz && \
	tar -xvf /phpMyAdmin-4.9.5-all-languages.tar.gz && \
	rm -f /phpMyAdmin-4.9.5-all-languages.tar.gz && \
	mv /phpMyAdmin-4.9.5-all-languages /etc/phpmyadmin && \
	rm -rf /var/cache/apk/*

RUN wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
	tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
	chmod +x telegraf/telegraf && \
	cp telegraf/telegraf /usr/bin/ && \
	rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && \
	mkdir -p /etc/telegraf

COPY srcs/config.inc.php /etc/phpmyadmin
COPY srcs/nginx.conf /etc/nginx/nginx.conf
COPY srcs/run.sh .
COPY srcs/telegraf.conf /etc/telegraf/

EXPOSE 5000

ENTRYPOINT [ "sh" ]
CMD [ "run.sh" ]
#CMD [ "sh" ]
