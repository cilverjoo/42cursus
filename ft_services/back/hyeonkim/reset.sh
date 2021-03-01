kubectl delete -f ./srcs/yaml/ftps.yml
eval $(minikube docker-env)
docker rmi ftps_service

docker build ./srcs/ftps/ -t ftps_service
kubectl apply -f ./srcs/yaml/ftps.yml