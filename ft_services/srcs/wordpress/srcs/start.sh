#give access right to root folder.
chmod -R 777 /var/www/wordpress
# Start telegraf
/usr/bin/telegraf
# Run PHP specifying port and file location
/usr/bin/php -S 0.0.0.0:5050 -t /var/www/wordpress/