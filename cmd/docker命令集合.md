# 创建docker并进入：镜像版本号,port号,映射路径
docker run --gpus all -it -p 2214:22 --ipc=host --name="tensorrt_22.12" --ulimit core=-1 -v /home/qitan:/home/qitan -v /mnt:/mnt -w /home/qitan nvcr.io/nvidia/tensorrt:22.12-py3 /bin/bash

# 修改docker时间为上海时间
mkdir -p /usr/share/zoneinfo/Asia/
scp zbz@192.168.2.79:/usr/share/zoneinfo/Asia/Shanghai /usr/share/zoneinfo/Asia/Shanghai
rm /etc/localtime
ln -s /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
# 测试
date