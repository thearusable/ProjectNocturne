# STAGE 1 - get ubuntu
FROM ubuntu:18.04

# Update apps on the base image
RUN apt-get -y update && apt-get install -y

# STAGE 2 - get gcc
FROM gcc:8.2

