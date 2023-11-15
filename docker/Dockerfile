FROM nvidia/cuda:12.2.2-devel-ubuntu22.04

ARG CUDA_ARCHITECTURES=native
ENV QT_XCB_GL_INTEGRATION=xcb_egl

# Prevent stop building ubuntu at time zone selection.  
ENV DEBIAN_FRONTEND=noninteractive

# Prepare and empty machine for building.
RUN apt-get update && apt-get install -y \
    git \
    cmake \
    build-essential \
    libboost-program-options-dev \
    libboost-filesystem-dev \
    libboost-graph-dev \
    libboost-system-dev \
    libeigen3-dev \
    libflann-dev \
    libfreeimage-dev \
    libglew-dev \
    qtbase5-dev \
    libqt5opengl5-dev \
    libcgal-dev \
    libceres-dev \
    libgtest-dev \
    libglfw3-dev \
    libomp-dev \ 
    libopenmpi-dev \
    libhdf5-dev \
    graphviz
    # libopencv-dev

# Utilitaires
RUN apt-get install -y \
    wget \
    tar \
    libx11-dev \
    xorg-dev \
    libssl-dev \
    libusb-1.0-0-dev \
    libglu1-mesa-dev \
    libgtk2.0-dev \
    pkg-config
    
# OpenGL
RUN apt-get install -qq --no-install-recommends \
    libglvnd0 \
    libgl1 \
    libglx0 \
    libegl1 \
    libxext6 \
    libx11-6 && \
    rm -rf /var/lib/apt/lists/* 

# Get folder ready
RUN mkdir /app /dpds && \
    cd dpds

# Realsense SDK
RUN wget --no-check-certificate https://github.com/IntelRealSense/librealsense/archive/refs/tags/v2.54.2.tar.gz && \
    tar -xzf v2.54.2.tar.gz && \
    rm v2.54.2.tar.gz && \
    cd librealsense-2.54.2/ && \
    mkdir build && cd build && \
    cmake .. && \
    make && \
    make install

# Opencv 4.5.4 xfeatures2d
RUN cd /dpds/ && \
    wget --no-check-certificate https://github.com/opencv/opencv_contrib/archive/refs/tags/4.5.4.tar.gz && \
    tar -xzf 4.5.4.tar.gz && \
    rm 4.5.4.tar.gz && \
    cd /dpds/ && \
    wget --no-check-certificate https://github.com/opencv/opencv/archive/refs/tags/4.5.4.tar.gz && \
    tar -xzf 4.5.4.tar.gz && \
    rm 4.5.4.tar.gz && \
    cd opencv-4.5.4 && mkdir build && cd build && \
    cmake -DOPENCV_EXTRA_MODULES_PATH=/dpds/opencv_contrib-4.5.4/modules/ -DWITH_GTK=ON -DBUILD_EXAMPLES=ON -DOPENCV_ENABLE_NONFREE=ON ../ && \
    make -j4 && \
    make install

RUN apt update && apt -y install libcanberra-gtk-module libcanberra-gtk3-module

ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES graphics,utility,compute
