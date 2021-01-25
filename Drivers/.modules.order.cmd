cmd_/home/user/EmbeddedLinux/Drivers/modules.order := {   echo /home/user/EmbeddedLinux/Drivers/driver1.ko; :; } | awk '!x[$$0]++' - > /home/user/EmbeddedLinux/Drivers/modules.order
