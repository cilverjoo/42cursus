# adduser -G www-data -D www-data
# chown -R www-data:www-data /var/www/phpmyadmin
# chmod -R 755 /var/www/phpmyadmin

# chmod 755 /var/www/phpmyadmin
# chmod 644 /var/www/phpmyadmin/*

# mkdir -p /run/openrc
# touch /run/openrc/softlevel

supervisord -c /etc/supervisord.conf	& tail -f /dev/null