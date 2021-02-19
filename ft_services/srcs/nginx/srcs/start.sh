# usr/sbin/sshd : ssh 데몬을 실행시켜 안전하지 않은 네트워크를 통해 
#신뢰할 수 없는 두 호스트간에 암호화된 보안 통신을 제공, ssh로 접속이 가능하다.
# nginx -g 'daemon off' : execute nginx in foreground.
/usr/sbin/sshd && nginx -g 'daemon off;'