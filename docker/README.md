# Docker images

## Table of contents

- [Docker images](#docker-images)
  - [Table of contents](#table-of-contents)
  - [Ubuntu 22](#ubuntu-22)
    - [Build](#build)
    - [Push](#push)
    - [Run manually](#run-manually)
  - [Fedora 37](#fedora-37)
    - [Build](#build-1)
    - [Push](#push-1)
    - [Run manually](#run-manually-1)
  - [Arch Linux](#arch-linux)
    - [Build](#build-2)
    - [Push](#push-2)
    - [Run manually](#run-manually-2)
  - [Alpine](#alpine)
    - [Build](#build-3)
    - [Push](#push-3)
    - [Run manually](#run-manually-3)


## Ubuntu 22

### Build

```bash
docker build -f ubuntu.Dockerfile -t hekkfern/aoc_cpp:ubuntu .
```

### Push

```bash
docker push hekkfern/aoc_cpp:ubuntu
```

### Run manually

To create a new container:

```bash
docker run -it --name aoc_cpp_ubuntu hekkfern/aoc_cpp:ubuntu
```

or, if it already exists:

```bash
docker start -i aoc_cpp_ubuntu
```

## Fedora 37

### Build

```bash
docker build -f fedora.Dockerfile -t hekkfern/aoc_cpp:fedora .
```

### Push

```bash
docker push hekkfern/aoc_cpp:fedora
```

### Run manually

```bash
docker run -it hekkfern/aoc_cpp:fedora
```

## Arch Linux

### Build

```bash
docker build -f archlinux.Dockerfile -t hekkfern/aoc_cpp:archlinux .
```

### Push

```bash
docker push hekkfern/aoc_cpp:archlinux
```

### Run manually

```bash
docker run -it hekkfern/aoc_cpp:archlinux
```

## Alpine

### Build

```bash
docker build -f alpine.Dockerfile -t hekkfern/aoc_cpp:alpine .
```

### Push

```bash
docker push hekkfern/aoc_cpp:alpine
```

### Run manually

```bash
docker run -it hekkfern/aoc_cpp:alpine
```
