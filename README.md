# IPgen

`IPgen` generate IP adresses from ranges.

It can generate IP based on simple `IP-IP` range notation:

    ipgen 192.168.0.0-192.168.0.10

CIDR notation:

    ipgen 10.0.0.0/8

`ipgen` can also take multiple ranges as input:

    ipgen 192.168.0.0-192.168.1.0,172.16.0.0/12,10.0.0.1

## TODO

- Add file as source for ip ranges ex: `ipgen -f RANGE`.
- Add IPv6 support.
- Remove dependancies for `netinet/in.h` and `arpa/inet.h`.