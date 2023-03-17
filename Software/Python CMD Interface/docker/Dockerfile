FROM raspbian/stretch

LABEL maintainer="Scott Gibb"

RUN apt-get update && \
    apt-get install -y build-essential && \
    apt-get install -y python3-pip

WORKDIR /app

COPY python-requirements.txt .
RUN pip3 install -r python-requirements.txt

COPY src ./src

ENTRYPOINT ["python3"]
CMD ["-u","src/main.py"]