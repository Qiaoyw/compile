FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc bianyi.c -o program
RUN chmod +x program
