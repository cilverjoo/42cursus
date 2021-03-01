#!/bin/bash

wget https://wordpress.org/latest.tar.gz
tar -xvf latest.tar.gz
mkdir /var/www/wordpress
mv wordpress/*      /var/www/wordpress/
cp wp-config.php  /var/www/wordpress/wp-config.php
adduser -G www-data -D www-data
chown -R www-data:www-data /var/www/wordpress
php-fpm7 -R
telegraf & 
nginx -g 'daemon off;' 
