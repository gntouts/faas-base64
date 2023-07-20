FROM alpine:3.18.2

RUN apk add --no-cache musl musl-dev git make build-base gcc

WORKDIR /tmp

RUN git clone git://git.musl-libc.org/musl

WORKDIR /tmp/musl
RUN CC="gcc -static" ./configure --prefix=/usr/local/musl --exec-prefix=/usr/local/bin --disable-shared && make
RUN make install

WORKDIR /workspace

CMD ["sh"]
