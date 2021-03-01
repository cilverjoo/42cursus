# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/28 21:51:51 by kim-eunju         #+#    #+#              #
#    Updated: 2021/03/01 01:13:57 by kim-eunju        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM alpine:3.12.0

RUN apk update
RUN apk add influxdb
RUN apk add supervisor --no-cache
RUN apk add telegraf --repository http://dl-cdn.alpinelinux.org/alpine/edge/community/ --allow-untrusted --no-cache

COPY ./srcs/supervisord.conf /etc/supervisord.conf
COPY ./srcs/telegraf.conf /etc/telegraf/
COPY ./srcs/start.sh /tmp/

EXPOSE 8086 8088

CMD sh /tmp/start.sh