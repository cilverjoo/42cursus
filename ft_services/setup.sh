#!/bin/bash

minikube delete

#start minikube with docker.
minikube start --driver=docker

minikube addons enable metrics-server
minikube addons enable dashboard
minikube addons enable metallb

kubectl apply -f srcs/metallb/metallb-system.yaml > /dev/null
kubectl apply -f srcs/metallb/metallb.yaml > /dev/null

#use docker daemon from minikube.
eval $(minikube docker-env)

#build docker images.
echo "**********Docker images build**************"
	
docker build -t my_nginx srcs/nginx/ > /dev/null
docker build -t my_mysql srcs/mysql/ > /dev/null
docker build -t my_phpmyadmin srcs/phpmyadmin/ > /dev/null
docker build -t my_wordpress srcs/wordpress/ > /dev/null
docker build -t my_ftps srcs/ftps/ > /dev/null
# docker build -t my_grafana srcs/grafana/
# docker build -t my_influxdb srcs/influxdb/

echo "**********Docker build completed************"

echo "**********Deploy init***********************"

kubectl apply -f srcs/nginx/nginx.yaml
kubectl apply -f srcs/mysql/mysql_service.yaml
kubectl apply -f srcs/mysql/mysql_pvc.yaml
kubectl apply -f srcs/mysql/mysql_deployment.yaml
kubectl apply -f srcs/ftps/ftps.yaml
kubectl apply -f srcs/phpmyadmin/phpmyadmin.yaml
kubectl apply -f srcs/wordpress/wordpress.yaml
# kubectl apply -f srcs/telegraf/telegraf_secret.yaml
# kubectl apply -f srcs/telegraf/telegraf_config.yaml
# kubectl apply -f srcs/telegraf/telegraf_deployment.yaml
# kubectl apply -f srcs/grafana/grafana.yaml
# kubectl apply -f srcs/influxdb/influxdb_secret.yaml
# kubectl apply -f srcs/influxdb/influxdb.yaml

echo "***********Deploy completed******************"
