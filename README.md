# Kernel Tutorial

> Based on JamesM's work

## Configuration
### Bochs
To use bochs, you need to install `x` windows or `sdl` display library. To use `sdl`, you need to specify in the `bochsrc.txt`:

```
display_library: sdl
```

What's more, you may need to check out you own bochs installation position to find a proper `romimage` and `vgaromimage`.

### QEMU
QEMU doesn't need any configution file, all are done in command options.

## Usage

1. `cd` into `src` and `make` the kernel
2. `sh update_image.sh`
3. Bochs: `sh run_bochs.sh`
4. QEMU: `sh run_qemu.sh`

Everytime you recompiled the kernel or other stuff, you need to repeat the above process.

## GDB Stub, with qemu
Just `gdb` after the kernel is launched, the session between debugger and qemu will be configured automatically.

## Usage of `initrd`
Compile the `make_initrd` normally, use it like:

```
make_initrd test1.txt test1.txt test2.txt test2.txt
```

## Usage of serial communication
You have to `mkfifo serial.pipe` under the `JKernel/`, and use `cat < serial.pipe` to listen to the input, use `echo "info" > serial.pipe` to send information to kernel.

I might develop a serial shell oneday.

## About test
Part of the test could be done easily by QEMU's monitor, which is opened by default, plus the power of gdb.

But I am currently  developing some functions to show the kernel's status by serial communication.