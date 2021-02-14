#!/bin/sh

if [[ ! -d /run/mysqld ]]; then
	mkdir -p /run/mysqld
	chown -R mysql:mysql /run/mysqld
fi

# Install mysql database(mariadb-install-db is a symlink to mysql_install_db).
mysql_install_db --user=root --datadir=/var/lib/mysql/

#create database for wordpress
mysqld --user=root --execute="FLUSH PREVILEGES; \
CREATE DATABASE wordpress; \
CREATE USER 'ekim'@'%' IDENTIFIED BY 'password'; \
GRANT ALL PREVILEGES ON *.* to 'ekim'@'%' IDENTIFIED BY 'password' WITH GRANT OPTIONS; \
FLUSH PREVILEGES;"

#sever start
mysqld --user=root