docker run -it --rm \
    --user 1000:1000 \
    --volume $(pwd):/workspace \
    raw-c-neural-network-image:0.0.1 \
    bash
