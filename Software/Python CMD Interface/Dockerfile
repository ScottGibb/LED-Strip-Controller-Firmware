FROM raspbian/stretch

RUN apt-get update -y
RUN apt-get install -y build-essential
RUN apt-get install python3-pip -y

COPY Tester.py /
COPY Types.py /
COPY requirements.txt /

RUN pip3 install -r requirements.txt

ENTRYPOINT ["python3"]
CMD ["-u","Tester.py"]