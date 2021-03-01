#!/bin/bash

php-fpm7 -R
usr/bin/telegraf & nginx -g "daemon off;"
