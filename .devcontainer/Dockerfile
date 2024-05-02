# This image contains customizations required for modbus
FROM espressif/idf:release-v5.1

ARG IDF_CLONE_URL
ARG IDF_CLONE_BRANCH_OR_TAG

# avoids user input during docker build
# https://stackoverflow.com/q/61388002
ARG DEBIAN_FRONTEND=noninteractive

# remove pre-installed ESP-IDF
RUN rm -rf /opt/esp/idf

# clone your desired ESP-IDF version
RUN git clone --recursive ${IDF_CLONE_URL} /opt/esp/idf

# checkout defined branch
WORKDIR /opt/esp/idf
RUN git checkout ${IDF_CLONE_BRANCH_OR_TAG}

# install and setup the ESP-IDF as per its instructions
RUN ./install.sh

# USBIP
RUN apt-get update \
  && apt install -y -q \
  cmake \
  git \
  hwdata \
  libglib2.0-0 \
  libnuma1 \
  libpixman-1-0 \
  linux-tools-virtual \
  && rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/local/bin/usbip usbip `ls /usr/lib/linux-tools/*/usbip | tail -n1` 20

# QEMU
ENV QEMU_REL=esp-develop-8.0.0-20230522
ENV QEMU_SHA256=A7E5E779FD593CB15F6D197034DC2FB427ED9165A4743E2FEBC6F6A47DFCC618
ENV QEMU_DIST=esp-qemu-xtensa-softmmu-develop_8.0.0_20230522-x86_64-linux-gnu.tar.bz2 
ENV QEMU_URL=https://github.com/espressif/qemu/releases/download/${QEMU_REL}/${QEMU_DIST}

ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8

RUN wget --no-verbose ${QEMU_URL} \
  && echo "${QEMU_SHA256} *${QEMU_DIST}" | sha256sum --check --strict - \
  && tar -xf $QEMU_DIST -C /opt \
  && rm ${QEMU_DIST}

ENV PATH=/opt/qemu/bin:${PATH}

# ESP-IDF Config
RUN echo "source /opt/esp/idf/export.sh > /dev/null 2>&1" >> ~/.bashrc

ENTRYPOINT [ "/opt/esp/entrypoint.sh" ]

CMD ["/bin/bash"]