# Этап 1: Сборка
FROM alpine:latest AS build

RUN apk add --no-cache \
    g++ \
    cmake \
    make

WORKDIR /src
COPY CMakeLists.txt /src/
COPY src /src/src/

WORKDIR /src/build

RUN cmake .. && make

# Этап 2: Запуск
FROM alpine:latest

RUN apk add --no-cache libstdc++

WORKDIR /build

COPY --from=build /src/build /build

ENV IP_ADDRESS=127.0.0.1
ENV PORT=8080

CMD ./IPv4Chat $IP_ADDRESS $PORT