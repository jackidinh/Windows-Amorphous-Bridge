<h1 align="center">Linux Pipeline Installation Guide</h1>

#### FastDDS Linux Install From Binaries:

- Download and extract latest Linux .tar.gz file for FastDDS at https://www.eprosima.com/product-download

- Run install.sh script using `sudo ./install.sh`

- Must be linked with library where packages are installed using `echo 'export LD_LIBRARY_PATH=/usr/local/lib/' >> ~/.bashrc`



#### Protoc Linux Install From Sources:

- Install Bazel, git,g++,Abseil using `sudo apt install -y cmake g++ git`

- Get source by using:
  
  - `git clone https://github.com/protocolbuffers/protobuf.git`
  - `cd protobuf`
  - `git checkout v29.5` //optional but for now this is the version being use, installing latest version is totally fine aslong as you use mismatched versions
  - `git submodule update --init --recursive`
  - `cd cmake`
  - `mkdir build`
  - `cd build`

- Build using:
  `cmake .. -DCMAKE_BUILD_TYPE=Release`
  `make -j$(nproc)`
  `sudo make install`
  `sudo ldconfig`

- verify by running protoc --version

#### Protobuf-c Linux Install From Sources:

- `git clone https://github.com/protobuf-c/protobuf-c.git`
- `cd protobuf-c`
- `./autogen.sh`
- `./configure `
- `make`
- `sudo make install`
- `sudo ldconfig `

- verify using `protoc-c --version`
  


