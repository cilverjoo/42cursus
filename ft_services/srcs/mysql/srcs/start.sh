#!/bin/sh
export TELEGRAF_CONFIG_PATH=/etc/telegraf.conf

if [[ ! -d /run/mysqld ]]; then
	mkdir -p /run/mysqld
fi

# Install mysql database(mariadb-install-db is a symlink to mysql_install_db).
mysql_install_db --user=root --datadir=/var/lib/mysql

#database settings
mysqld --user=root --bootstrap < /tmp/mysql_init
mysqld --user=root --console

#start telegraf
telegraf &