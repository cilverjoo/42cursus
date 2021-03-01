openrc
rc-service mariadb restart
echo "FLUSH PRIVILEGES;" | mysql -u root
/usr/bin/mysqld_safe --datadir="/var/lib/mysql"