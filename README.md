# IPgen

## About

`IPgen` generate IP adresses from given ranges.

It can generate based on simple IP-IP range notation.
    ipgen 192.168.0.0-192.168.0.10
CIDR notation can also be used.
    ipgen 10.0.0.0/8
`ipgen` can also generate IP addresses based on multiple inputs.
    ipgen 192.168.0.0-192.168.1.0,172.16.0.0/12,10.0.0.1

## TODO

- Add file as source for inputs.
- Add IPv6 support.
- Remove dependancy for `netinet/in.h` and `arpa/inet.h`.

## License

MIT