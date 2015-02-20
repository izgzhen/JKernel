# update iso
cp src/kernel.elf iso/boot/kernel
cp initrd.img iso/fs/initrd.img
mkisofs -R \
        -b boot/grub/stage2_eltorito \
        -no-emul-boot \
        -boot-load-size 4 \
        -A os \
        -input-charset utf8 \
        -boot-info-table \
        -o image.iso \
        -quiet \
        iso
