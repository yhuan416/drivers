# chrdev

## 构建

``` sh
./build
```

## 拷贝到开发板

``` sh
scp chrdev.ko root@192.168.124.22:/lib/modules/5.15.24
```

## 加载模块

``` sh
insmod chrdev.ko
mknod /dev/chrdev c 200 0
```

or

``` sh
depmod # 生成modules.dep
modprobe chrdev
```

## 卸载模块

``` sh
rmmod chrdev
```
