#!/bin/bash

service mysql start

#allow access
chown -R www-data:www-data var/www/*
chmod -R 755 var/www/*

#create Database "wordpress"
echo "CREATE USER 'root'@'%' identified by '12345';" | mysql -u root --skip-password
echo "CREATE DATABASE wordpress;" | mysql -u root --skip-password
echo "GRANT ALL PRIVILEGES ON wordpress.* TO 'root'@'localhost';" | mysql -u root --skip-password
echo "FLUSH PRIVILEGES;" | mysql -u root --skip-password

service nginx start
service php7.3-fpm start
bash
