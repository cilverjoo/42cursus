#!/bin/bash

# Colors.
GREEN='\e[0;32m'
BLUE='\e[0;34m'
END='\e[0;0m'

minikube delete

#start minikube with docker.
minikube start --driver=docker

#use docker daemon from minikube.
eval $(minikube docker-env)

#build docker images.
echo "${GREEN}**Docker images build**${END}"
	
docker build -t my_nginx srcs/nginx > /dev/null 2>&1
docker build -t my_wordpress srcs/wordpress > /dev/null 2>&1
docker build -t my_mysql srcs/mysql > /dev/null 2>&1
docker build -t my_phpmyadmin srcs/phpmyadmin > /dev/null 2>&1
docker build -t my_ftps srcs/ftps > /dev/null 2>&1
docker build -t my_grafana srcs/grafana > /dev/null 2>&1
docker build -t my_influxdb srcs/influxdb > /dev/null 2>&1

echo "${BLUE}**Docker build completed**${END}"
