FROM python:3.9

LABEL maintainer="Scott Gibb"

RUN apt-get update && \
    apt-get install -y build-essential && \
    apt-get install -y python3-pip

WORKDIR /app

COPY src ./src
COPY python-requirements.txt ./python-requirements.txt
RUN pip3 install -r python-requirements.txt

ENTRYPOINT ["python3"]
CMD ["-u","src/main.py"]