FROM tp_bd_base:latest

MAINTAINER Artem Ikchurin

# Копируем исходный код в Docker-контейнер
ENV WORK /opt/TP_DB
ADD ./ $WORK/

# Собираем и устанавливаем пакет
RUN mkdir -p $WORK/build
WORKDIR $WORK/build
RUN cmake ../ && make && ldconfig -v
RUN cp ../server-config.json server-config.json

# Объявлем порт сервера
EXPOSE 8080

#
# Запускаем PostgreSQL и сервер
#
CMD service postgresql start && $WORK/build/TP_BD -c server-config.json
