# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest
FROM gcc:8.2
 
# Update apps on the base image
RUN apt-get -y update && apt-get install -y

