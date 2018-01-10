FROM        ubuntu
MAINTAINER  Peter Bui <pbui@nd.edu>

RUN         apt-get update -y

# Run-time dependencies
RUN         apt-get install -y python3-tornado python3-requests python3-yaml python3-markdown

# Language Support: C, C++, Make, valgrind, cppcheck
RUN         apt-get install -y gcc g++ make valgrind cppcheck
