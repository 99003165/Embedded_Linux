cmd_/home/user/EmbeddedLinux/Modules/hello3_module/Module.symvers := sed 's/ko$$/o/' /home/user/EmbeddedLinux/Modules/hello3_module/modules.order | scripts/mod/modpost  -a   -o /home/user/EmbeddedLinux/Modules/hello3_module/Module.symvers -e -i Module.symvers   -T -
