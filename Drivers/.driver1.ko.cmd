cmd_/home/user/EmbeddedLinux/Drivers/driver1.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000  --build-id  -T ./scripts/module-common.lds -o /home/user/EmbeddedLinux/Drivers/driver1.ko /home/user/EmbeddedLinux/Drivers/driver1.o /home/user/EmbeddedLinux/Drivers/driver1.mod.o;  true
