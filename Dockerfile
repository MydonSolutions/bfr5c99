# syntax=docker/dockerfile:1
## Primary builds
FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get install -y \
# BLADE
    gcc-10 \
# GENERAL
    git \
    linux-tools-generic \
# MESON
    python3-pip \
# HDF5
    libhdf5-dev

# setup meson build-flow tools (BLADE, UVH5)
RUN python3 -m pip install meson ninja 
# Install dependencies
WORKDIR /work