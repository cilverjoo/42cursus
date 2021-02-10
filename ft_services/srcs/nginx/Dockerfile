FROM alpine:latest

RUN apk update&& \
    apk add nginx openssl openssh --no-cache

# make sshd.conf file
RUN sed 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' -i /etc/ssh/sshd_config
RUN adduser -D ekim && \
    echo 'ekim:password' | chpasswd && \
    mkdir -p /run/nginx && \
    ssh-keygen -f /etc/ssh/ssh_host_rsa_key -N '' -t rsa && \
    ssh-keygen -f /etc/ssh/ssh_host_dsa_key -N '' -t dsa && \
    mkdir -p /run/sshd

#nginx ssl certificate
RUN openssl req -x509 -nodes -days 365 \
	-newkey rsa:2048 -subj  "/C=KR/ST=Seoul/L=Seoul/O=42Seoul/OU=ekim/CN=localhost" \
	-keyout /etc/ssl/private/nginx.key -out /etc/ssl/certs/nginx.crt

COPY ./srcs/ssl_params.conf /etc/nginx/
COPY ./srcs/nginx.conf /etc/nginx/
COPY ./srcs/sshd_config /etc/ssh/
COPY ./srcs/start.sh ./tmp/

RUN echo "daemon off;" >> /etc/nginx/nginx.conf
EXPOSE 80 443 22

ENTRYPOINT ["/bin/sh", "./tmp/start.sh"]