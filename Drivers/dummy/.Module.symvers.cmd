cmd_/home/user/EmbeddedLinux/Drivers/dummy/Module.symvers := sed 's/ko$$/o/' /home/user/EmbeddedLinux/Drivers/dummy/modules.order | scripts/mod/modpost  -a   -o /home/user/EmbeddedLinux/Drivers/dummy/Module.symvers -e -i Module.symvers   -T -