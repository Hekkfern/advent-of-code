# Docker images

## Ubuntu 22

### Build

```bash
docker build -f ubuntu.Dockerfile -t hekkfern/aoc_cpp:ubuntu .
```

### Push

```bash
docker push hekkfern/aoc_cpp::ubuntu
```

## Fedora 37

### Build

```bash
docker build -f fedora.Dockerfile -t hekkfern/aoc_cpp:fedora .
```

### Push

```bash
docker push hekkfern/aoc_cpp::fedora
```

## Arch Linux

### Build

```bash
docker build -f archlinux.Dockerfile -t hekkfern/aoc_cpp:archlinux .
```

### Push

```bash
docker push hekkfern/aoc_cpp::archlinux
```

### Run manually

```bash
docker run -it hekkfern/aoc_cpp::archlinux
```

## Alpine

### Build

```bash
docker build -f alpine.Dockerfile -t hekkfern/aoc_cpp:alpine .
```

### Push

```bash
docker push hekkfern/aoc_cpp::alpine
```

### Run manually

```bash
docker run -it hekkfern/aoc_cpp::alpine
```
