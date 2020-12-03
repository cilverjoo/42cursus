#!/bin/bash

wget https://wordpress.org/latest.tar.gz && \
	tar -xvf latest.tar.gz -C /var/www/html/ && \
	rm latest.tar.gz && \
	mv /tmp/wp-config.php /var/www/html/wordpress/
