# Install mysql database(mariadb-install-db is a symlink to mysql_install_db).
mysql_install_db --user=ekim

#create database for wordpress
mysqld --user=ekim --execute="CREATE DATABASE wordpress;"
mysqld --user=ekim --execute="CREATE USER 'ekim'@'%' IDENTIFIED BY 'password';"
mysqld --user=ekim --execute="GRANT ALL PREVILEGES ON *.* to 'ekim'@'%' WITH GRANT OPTIONS;"
mysqld --user=ekim --execute="FLUSH PREVILEGES;"

#sever start
mysqld --user=ekim