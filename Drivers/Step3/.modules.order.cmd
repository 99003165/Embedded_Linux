cmd_/home/user/EmbeddedLinux/Drivers/Step3/modules.order := {   echo /home/user/EmbeddedLinux/Drivers/Step3/driver3.ko; :; } | awk '!x[$$0]++' - > /home/user/EmbeddedLinux/Drivers/Step3/modules.order
