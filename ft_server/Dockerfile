# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekim <ekim@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/02 19:59:41 by ekim              #+#    #+#              #
#    Updated: 2020/12/02 21:32:12 by ekim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM debian:buster

RUN apt-get update \
	&& apt-get upgrade \
	&& apt-get -y install nginx mariadb-server php7.3-fpm php7.3-mysql \
	openssl wget vim

RUN openssl req -newkey rsa:4096 -days 365 -nodes -x509 \
	-subj "/C=KR/ST=Seoul/L=Seoul/O=42Seoul/OU=ekim/CN=localhost" \
	-keyout localhost.dev.key -out localhost.dev.crt
RUN mv localhost.dev.crt etc/ssl/certs/
RUN mv localhost.dev.key etc/ssl/private/

COPY srcs tmp

RUN mv /tmp/default /etc/nginx/sites-available/default

ENTRYPOINT ["/tmp/docker.sh", "/bin/bash"]
