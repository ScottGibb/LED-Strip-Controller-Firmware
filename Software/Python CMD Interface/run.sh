docker build . -t cmdline-controller:v1
docker run -it -d \
    --name led-cmdline-controller \
    --privileged \

