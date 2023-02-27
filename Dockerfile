FROM registry.gitlab.steamos.cloud/steamrt/scout/sdk

WORKDIR /game

# We use GCC 9 to support C++17.
ENV CC=/usr/bin/gcc-9
ENV CXX=/usr/bin/g++-9

RUN apt-get install -y \
  g++-9 \
  ninja-build \
  cmake \
  libsdl2-dev

COPY . .

RUN cmake -DCMAKE_BUILD_TYPE=Release -G Ninja -S /game -B /game/build && \
  cmake --build /game/build
