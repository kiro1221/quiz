FROM janvik/oatpp:latest

WORKDIR /
ADD . /seleep
WORKDIR ./seleep

# RUN make testServer
# RUN ./testServer

EXPOSE 9100 9100

RUN make seleepServer
ENTRYPOINT ["./seleepServer"]

# Used to allow for connection to container so can use commandline
#ENTRYPOINT ["sleep", "infinity"]