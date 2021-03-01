BLUE_GREEN="\033[36m"
echo -n "${BLUE_GREEN}"

# export MINIKUBE_HOME=~/goinfre # @개포동(저장공간 확보!)

minikube delete --all

# 클러스터 생성
minikube start --driver=virtualbox --extra-config=apiserver.service-node-port-range=0-32767

# Metallb 활성화
minikube addons enable metallb

# 클러스터 안에서 이미지를 빌드하도록 환경 설정
eval $(minikube docker-env)

minikube dashboard &

# 이미지 빌드
echo "이미지 빌드를 시작합니다..."
echo "nginx..."
docker build -t nginx_service ./srcs/nginx > /dev/null
echo "mySQL..."
docker build -t mysql_service ./srcs/mysql > /dev/null
echo "phpMyAdmin..."
docker build -t phpmyadmin_service ./srcs/phpmyadmin > /dev/null
echo "wordpress..."
docker build -t wordpress_service ./srcs/wordpress > /dev/null
echo "influxdb..."
docker build -t influxdb_service ./srcs/influxdb > /dev/null
echo "grafana..."
docker build -t grafana_service ./srcs/grafana > /dev/null
echo "ftps..."
docker build -t ftps_service ./srcs/grafana > /dev/null

# 오브젝트 생성
echo "오브젝트를 생성합니다..."
kubectl apply -f ./srcs/yaml/nginx.yml
kubectl apply -f ./srcs/yaml/mySql.yml
kubectl apply -f ./srcs/yaml/phpMyAdmin.yml
kubectl apply -f ./srcs/yaml/wordpress.yml
kubectl apply -f ./srcs/yaml/influxdb.yml
kubectl apply -f ./srcs/yaml/grafana.yml
kubectl apply -f ./srcs/yaml/ftps.yml

# 로드밸런서에 external IP 부여
kubectl apply -f ./srcs/ConfigMap.yml