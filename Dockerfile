# Этап 1: Сборка
FROM alpine:latest AS build

RUN apk add --no-cache g++

COPY . /src

WORKDIR /src
RUN g++ -o app src/main.cpp

# Этап 2: Запуск
FROM alpine:latest

RUN apk add --no-cache libstdc++

COPY --from=build /src/app /app

ENV IP_ADDRESS=127.0.0.1
ENV PORT=8080

CMD /app $IP_ADDRESS $PORT


# # Этап 1: Сборка
# FROM alpine:latest AS build

# # Установка компилятора g++
# RUN apk add --no-cache g++

# # Копирование исходного кода
# COPY . /src

# # Компиляция исходного кода
# WORKDIR /src
# RUN g++ -o app src/main.cpp && \
#     apk del g++

# # Этап 2: Запуск
# FROM alpine:latest

# # Установка необходимых библиотек
# RUN apk add --no-cache libstdc++

# # Копирование исполняемого файла из этапа сборки
# COPY --from=build /src/app /app

# # Установка переменных окружения
# ENV IP_ADDRESS=127.0.0.1
# ENV PORT=8080

# # Запуск приложения
# CMD /app $IP_ADDRESS $PORT



# # Этап 1: Сборка
# FROM alpine:latest AS build

# RUN apk add --no-cache g++ libstdc++

# # Копирование исходного кода
# COPY . /src

# # Компиляция исходного кода
# WORKDIR /src
# RUN g++ -o app src/main.cpp

# # Этап 2: Запуск
# FROM scratch

# # Копирование исполняемого файла в корень
# COPY --from=build /src/app /app

# # Копирование библиотеки libstdc++
# COPY --from=build /usr/lib/libstdc++.so.6 /usr/lib/

# ENV IP_ADDRESS=127.0.0.1
# ENV PORT=8080

# CMD ["/app", "$IP_ADDRESS", "$PORT"]
