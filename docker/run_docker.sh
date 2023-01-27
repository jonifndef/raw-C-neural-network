SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

docker run -it --rm \
    --user user \
    --volume ${SCRIPT_DIR}/../:/home/user/raw-C-neural-network \
    --workdir /home/user/raw-C-neural-network \
    raw-c-neural-network-image:0.0.1 \
    bash
