cmd_/home/user/EmbeddedLinux/Drivers/dummy/modules.order := {   echo /home/user/EmbeddedLinux/Drivers/dummy/hello.ko; :; } | awk '!x[$$0]++' - > /home/user/EmbeddedLinux/Drivers/dummy/modules.order
