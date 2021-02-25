export TELEGRAF_CONFIG_PATH=/etc/telegraf.conf
#give access right to root folder.
chmod -R 777 /var/www/wordpress
# Start telegraf
telegraf &
# Run PHP specifying port and file location
php -S 0.0.0.0:5050 -t /var/www/wordpress