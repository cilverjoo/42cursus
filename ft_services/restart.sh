# # influxdb
# kubectl delete deployment.apps/influxdb
# kubectl delete $(kubectl get pods | grep influxdb | awk '{print $1}')
# docker rmi $(docker images | grep my_influxdb | awk '{print $3}')
# docker build -t my_influxdb srcs/influxdb/
# kubectl apply -f srcs/influxdb/influxdb.yaml

# #nginx
# kubectl delete deployment.apps/nginx
# kubectl delete service/nginx
# kubectl delete $(kubectl get pods | grep nginx | awk '{print $1}')
# docker rmi $(docker images | grep my_nginx | awk '{print $3}')
# docker build -t my_nginx srcs/nginx/
# kubectl apply -f srcs/nginx/nginx.yaml

# #phpmyadmin
# kubectl delete deployment.apps/phpmyadmin
# kubectl delete $(kubectl get pods | grep phpmyadmin | awk '{print $1}')
# docker rmi $(docker images | grep my_phpmyadmin | awk '{print $3}')
# docker build -t my_phpmyadmin srcs/phpmyadmin/
# kubectl apply -f srcs/phpmyadmin/phpmyadmin.yaml

# # wordpress
# kubectl delete deployment.apps/wordpress
# kubectl delete $(k get pods | grep wordpress | awk '{print $1}')
# docker rmi $(docker images | grep my_wordpress | awk '{print $3}')
# docker build -t my_wordpress srcs/wordpress/
# kubectl apply -f srcs/wordpress/wordpress.yaml

# # grafana
# kubectl delete deployment.apps/grafana
# kubectl delete $(kubectl get pods | grep grafana  | awk '{print $1}')
# docker rmi $(docker images | grep grafana | awk '{print $3}')
# docker build -t my_grafana srcs/grafana/
# kubectl apply -f srcs/grafana/grafana.yaml

#ftps
kubectl delete deployment.apps/ftps
kubectl delete $(kubectl get pods | grep ftps  | awk '{print $1}')
docker rmi $(docker images | grep ftps | awk '{print $3}')
docker build -t my_ftps srcs/ftps/
kubectl apply -f srcs/ftps/ftps.yaml

#curl ftp://192.168.99.105:21 --ssl -k --user ekim -T setup.log

# #mysql
# kubectl delete deployment.apps/mysql
# kubectl delete $(kubectl get pods | grep mysql | awk '{print $1}')
# docker rmi $(docker images | grep mysql | awk '{print $3}')
# docker build -t my_mysql srcs/mysql/
# kubectl apply -f srcs/mysql/mysql.yaml

