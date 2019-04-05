# uses the officieal bionic docker image from https://hub.docker.com/_/ubuntu
FROM ubuntu:bionic

# update and install required packages
RUN apt update
RUN apt install make g++ -y

WORKDIR /home/follow_me
