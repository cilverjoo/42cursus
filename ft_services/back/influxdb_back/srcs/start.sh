# if [ ! -d /etc/influxdb ]; then
# 	mkdir -p /etc/influxdb
# fi

# if [ ! -d /var/lib/influxdb ]; then
# 	mkdir -p /var/lib/influxdb
# fi

supervisord -c /etc/supervisord.conf & tail -f /dev/null

# influx -execute "CREATE DATABASE telegraf"
# influx -execute "CREATE USER ekim WITH PASSWORD 'password' WITH ALL PRIVILEGES"