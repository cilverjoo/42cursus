export TELEGRAF_CONFIG_PATH=/etc/telegraf.conf
chmod -R 777 /var/www/phpmyadmin
# -S option : run with built-in web server. -S <addr>:<port>
# Specify the root of the document for the internal web server
telegraf &
php -S 0.0.0.0:5000 -t /var/www/phpmyadmin